
# Lecture 13 Ray Tracing 1（Whitted-Style）
* 光栅化的局限
  * 对全局效果表示比较困难，如软阴影Soft shadows、光泽反射Glossy reflection（类似古代铜镜）、间接光照Indirect illumination
  * 速度很快，但效果只是一些近似，质量比较低
## 定义光线（图形学中）
* 光线沿直线传播。（忽略波动性）
* 光线不发生碰撞。（忽略相向传播发生的干涉现象）
* 光线从光源出发，到达人眼。
  * 利用光路的可逆性reciprocity，进行光线追踪。
## 几种类型
* 光线投射Ray Casting
  * Step
    * 相机到场景点：向成像屏幕的每个像素投射光线。
    * 场景点到光源：判断像素是否被光线照亮/被其它物体遮挡。
  * 发生反射和折射，但不递归跟踪。
* Recursive (Whitted-Style) Ray Tracing
  * `"An improved illumination model for shaded display" T.Whitted, CACM 1980`
  * 光线传播过程中，每个弹射点都向光源连线检查是否被照亮并加和到像素值。所以最终得到的像素颜色，结合了所有“经过这个像素后，所有能到达光源的情况”，逆向来说也就是考虑了“光源往各个方向发射的光线，经弹射后，能到达相机的所有情况”。
  * 光线归类
    * 刚从相机出发的光线：`eye ray/primary ray`
    * 经过一次弹射之后的光线：`secondary rays`
    * 连向光源判定可见性的连线：`shadow rays`
## 光与物体表面交点Ray-Surface Intersection
### **与隐式表面求交**
* 定义光线（数学中）
  * 光源 $O$ ，方向 $d$
  * 光射线方程 $r(t) = O + td, 0 \leqslant t < \infty$
* 定义球体（隐函数形式）
  * 点 $P$ 在球上方程 $(X_P-X_C)^2+(Y_P-Y_C)^2+(Z_P-Z_C)^2-R^2=0$
  * 其中三项平方部分可以写成 $\overrightarrow{P-C}\cdot \overrightarrow{P-C}$ 的形式
* 两物体交点：同时在两物体上
  * 将光的表示形式代入球体方程 $\overrightarrow{r(t)-C}\cdot \overrightarrow{r(t)-C}-R^2=0$
  * 完全展开后为关于参数 $t$ 的一元二次方程
  * 注意点
    * 为满足光射线的物理意义，求出的 $t$ 结果只能取非负，也必须是实数，即判别式非负
    * 取最近交点，较小的根
* 与一般的隐式表示形式的表面求交都类似，解得参数 $t$ 即可。
### **与显式表面求交**
* 光线与三角网格求交（简化方法）
  * 将问题分解为
    * 光线和平面求交
    * 判定交点是否在三角形内
  * **光线和平面求交**
    * 定义平面：一个法线 $\overrightarrow{N}$ 和平面上的一个点 $P'$
    * 点 $P$ 在平面上方程 $\overrightarrow{P-P'}\cdot \overrightarrow{N} = 0$
    * 设参数代入展开后可整理得一般平面方程 $ax+by+cz+d=0$ 
    * 将点 $P$ 用光线的参数形式代入
      $$ (\overrightarrow{O}+t\cdot \overrightarrow{d}-\overrightarrow{P'})\cdot \overrightarrow{N} = 0 $$
      $$ \overrightarrow{O}\cdot \overrightarrow{N} +t\overrightarrow{d}\cdot \overrightarrow{N}-\overrightarrow{P'}\cdot \overrightarrow{N}=0 $$
      $$ t = \frac{\overrightarrow{P'}\cdot \overrightarrow{N}-\overrightarrow{O}\cdot \overrightarrow{N}}{\overrightarrow{d}\cdot \overrightarrow{N}} $$
      最后同样注意 $t$ 的取值。
* 光线与三角网格求交（直接求法）
  * Möller Trumbore Algorithm（MT算法）
    * 用三角形重心坐标表示平面上的点
      $$ \overrightarrow{O}+t\overrightarrow{d}=(1-b_1-b_2)\overrightarrow{P_0}+b_1\overrightarrow{P_1}+b_2\overrightarrow{P_2} $$
    * 有三个未知数 $t、b_1、b_2$，而方程中为三维向量，可列出 $x、y、z$ 三个维度上的三个方程组，即可得一个线性方程组。
    * 解线性方程组：`Cramer's Rule`克拉默法则
      $$ \left[\begin{matrix} t \\ b_1 \\ b_2 \end{matrix}\right] = \frac{1}{\overrightarrow{S_1}\cdot \overrightarrow{E_1}}\left[\begin{matrix} \overrightarrow{S_2}\cdot \overrightarrow{E_2} \\ \overrightarrow{S_1}\cdot\overrightarrow{S} \\ \overrightarrow{S_2} \cdot \overrightarrow{D} \end{matrix}\right] $$
      其中，$\overrightarrow{E_1} = \overrightarrow{P_1}-\overrightarrow{P_0}$，$\overrightarrow{E_2} = \overrightarrow{P_2}-\overrightarrow{P_0}$，$\overrightarrow{S}=\overrightarrow{O}-\overrightarrow{P_0}$，$\overrightarrow{S_1}=\overrightarrow{d}\times\overrightarrow{E_2}$，$\overrightarrow{S_2}=\overrightarrow{S}\times\overrightarrow{E_1}$
    * 判断解的合理性：重心坐标的三个参数非负。
### **光线与三角网格求交的优化**
* 包围盒Bounding Box思想
  * 用简单的形体把场景中的物体完全包围住
  * 如果光线与包围盒不相交，那么一定也不会与物体相交
* Axis-Aligned Bounding Box（AABB，轴对齐包围盒）
  * 长方体包围盒，所有轴都与坐标轴对齐
* 光线与Axis-Aligned Box求交
  * 考虑二维 $xy$ 平面下，光线穿过构成矩形的四条直线，可以看成光线分别和 $x=x_0、x=x_1、y=y_0、y=y_1$ 有四个交点。并且根据所得参数 $t$ 的大小，与平行 $x$ 轴和平行 $y$ 轴的直线，如图可得两组 $t_{min}、t_{max}$  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img54.png) &nbsp;</br>
    注意：此时 $t$ 可能存在负值（光线在包围盒内）
  * 转化到三维，即将构成矩形的四条直线，看作空间中的平面板。
  * 判断“光线进入包围盒”，由于AAB的轴都与坐标轴对齐，那么光点在包围盒内时应有其投影在矩形六个面内，也因为与坐标轴对齐，六个面可分为三组。所以对每组都在面内时，光线就在包围盒内。
  * 从数值上看，即取 $t_{enter} = max(t_{xmin}, t_{ymin}, t_{zmin})、t_{exit} = min(t_{xmax}, t_{ymax}, t_{zmax})$ 之间的时间，为光线在包围盒内的参数范围。
    * 当 $t_{exit} < 0$ ，未击中包围盒，不相交
    * 当 $t_{exit} \geqslant 0$ 且 $t_{enter}<0$ 时，光线在包围盒中，必然相交
    * 因此，iff当且仅当 $t_{enter}<t_{exit}$ 且 $t_{exit}\geqslant0$ 时

# Lecture 14 Ray Tracing 2（Acceleration & Radiometry）
## 包围盒的利用
### 预处理包围盒网格
* Step
  * 对包围盒`均匀划分`网格
  * 标记网格中是否有物体
  * 光线追踪时，先求与包围盒网格交点，网格标记有物体再与该物体求交
* 注意点
  * 包围盒网格的划分疏密程度要取平衡
  * 这并不是个实际被应用的方法（x
  * 对于场景中某些部分物体多、某些部分很空的情况下比较不理想
### 空间划分Spatial Partitions
* 几种空间划分结构
  * 八叉树Oct-Tree：把包围整个三维场景的包围盒，在空间中三刀切八份。（二维两刀四叉树，一维二叉树）递归划分，直到块内无物体或者比较少
  * KD-Tree：与维度无关，每次只按一个轴向作一次划分，所以每层是二叉树。可以每层按方向循环切，或者设定一种比较平衡的划分方式。
  * BSP-Tree：每次选一个方向切，与KD-Tree不同，可以歪着切。在维度高的时候比较难以计算。
* **KD-Tree**
  * 预处理时进行构造
  * 数据结构（每个结点维护的信息）
    * split axis：当前结点的子树按照 $x、y、z$ 哪个轴进行划分
    * split position：在轴的哪个位置进行划分
    * children：指向子结点的指针
    * list of objects：实际包围的物体，只存储在叶子结点，分支结点中不含该信息
  * 遍历查询
    * 从根结点开始，判定是否与根结点相交
    * 与根结点相交，递归与两个子结点求 $t_{min}、t_{max}$
    * 直到叶子结点，与其中所有物体求交
  * 问题
    * 三角形与AABB是否有交集，判断比较困难
    * 一个物体会出现在多个叶子结点
### 物体划分Object Partitions & Bounding Volume Hierarchy（BVH）
* 思想
  * 把场景中所有物体按某个方向划分成两部分
  * 性质
    * 一个物体只出现在一个划分中，避免了KD-Tree的问题。
* 构造
  * 对每个结点，选择一个维度进行切分
    * Heuristic 1：总是选择最长的维度
    * Heuristic 2：某个维度上，选择按维度排序的第 $\frac{n}{2}$ 个物体划分  
      可以用三角形重心来排序，或者不排序，直接用“在乱序数中 $O(n)$ 查第x大的数”`快速选择算法`。
    * 总之，尽量保证树的平衡性能
  * 终止标准termination criteria
    * 结点包含的物体数少到某个值以下
  * 问题
    * 运动场景：重新求BVH
* 数据结构
  * 分支结点维护信息：包围盒、子结点指针
  * 叶子结点维护信息：包围盒、包围的物体列表
## 辐射度量学Basic radiometry
### **Motivation**
* 问题
  * 回顾Blinn-Phong光照模型中暂述的光强 $I$ ，但“光强”的称呼在物理上是不正确的，它有实际的更准确的物理意义
  * 之前的一些效果其实是incorrect results，而在radiometry中会精确地定义光，描述光与物体表面如何作用，光源、材质、传播方法等。同时也是路径追踪path tracing的基础。
* Radiometry
  * Measurement system and units for illumination
  * 精确度量了光在空间上的属性the spatial properties of light
    * 仍然基于几何光学，即直线传播、无波动性
    * 定义的属性：Radiant flux、intensity、irradiance、radiance
  * perform lighting calculations in a physically correct manner
### **Radiant Energy and Flux（Power）**
* 定义：`Radiant energy` is the energy of electromagnetic radiation. 电磁辐射的能量。 It is measured in units of joules, and denoted by the symbol 
  $$ Q\ [J=Joule] $$
  * 中文名可能叫辐射能量。
* 定义：`Radiant flux/power` is the energy emitted, reflected, transmitted or received, per unit time. 单位时间的能量，即功率。
  $$ \Phi \equiv \frac{dQ}{dt} \ [W=Watt]\ [lm=lumen]* $$
  * 中文名可能叫辐射通量、光通量。
  * $\equiv$：恒等号。
  * lumen流明：光通量单位。
  * 直观理解：人眼感受到的亮度。
### **Important Light Measurements of Interest**
#### 辐射/发光强度 Radiant/Luminous Intensity
* 定义：The radiant (luminous) intensity is `the power per unit solid angle` emitted by a point light source. 每单位立体角的能量。
  $$ I(\omega) \equiv \frac{d\Phi}{d\omega} $$
  $$ [\frac{W}{sr}][\frac{lm}{sr}=cd=candela] $$
  * 坎德拉candela是国际标准单位。
* 立体角Solid Angle
  * 二维圆的弧度Angle：由圆心拉出两根半径所得扇形，总是对应一段圆弧，整个圆有 $2\pi$ 弧度。
    $$ \theta=\frac{l}{r} $$
  * 三维球的立体角Solid Angle：由球心作一圆锥，总是对应一块球面积，整个球的立体角 $4\pi$ 。
    $$ \Omega=\frac{A}{r^2} $$
  * 微分立体角Differential Solid Angles：
    * 在三维坐标系下，设与 $z$ 轴夹角 $\theta \in [0, \pi]$ ，再绕 $z$ 轴旋转 $\phi \in [0, 2\pi]$ ，可以确定一个球面方向。
    * 当方向分别夹 $z$ 轴改变 $d\theta$，绕 $z$ 轴改变 $d\phi$ 时，会在球面上划出两道，以它们为邻边作平行四边形，由于极小，近似看作矩形，其面积表示为
      $$ dA = (r\ d\theta)\cdot(r\ sin\theta\ d \phi) = r^2\ sin\theta\ d\theta\ d\phi$$
    * 根据立体角定义，可得`单位立体角`
      $$ d\omega = \frac{dA}{r^2} = sin\theta\ d\theta\ d\phi $$
      由此可以看出，球面上近极点处和近纬线处，相同的 $\theta$ 变化量引起的立体角变化量是不同的，不是均匀变化。
    * 对于整个球而言，对所有单位立体角进行积分
      $$\begin{aligned}
       \Omega &= \int_{S^2}d\omega \\ &= \int_{0}^{2\pi} \int_{0}^{\pi} sin\theta\ d\theta\ d\phi \\ &= 4\pi\end{aligned}$$
       此处插播积分的复习
       $$ 三角函数积分公式 \int sin\theta\ d\theta = -cos\theta+C $$
       $$ 定积分不需要+C，代入公式，上界减下界 $$
       $$ \int_{0}^{\pi}\ sin\theta = -cos\pi - (-cos0) = 2 $$
       $$ 2\cdot \int_{0}^{2\pi}d\phi = 2\cdot (2\pi-0)=4\pi $$
* 回到对辐射/发光强度 Radiant/Luminous Intensity定义的理解
  * 之前定义了光本身的总能量Radiant Flux/Power $\Omega$
  * 所以其在某个方向上的能量，看作一块极小区域的能量，为 $d\Phi$
  * 又有极小区域的面积，即单位立体角 $d\omega$
  * 因此，该物理量表示“在某个方向上的光的能量”，即单位立体角的能量。
  * 显然，所有方向上的能量积分起来可以得到总能量
    $$ \begin{aligned} \Phi &= \int_{S^2}I\ d\omega \\ &= 4\pi I \end{aligned} $$
    所以，当光源往各个方向均匀放出能量时，任意方向上应有 
    $$ I=\frac{\Phi}{4\pi} $$

# Lecture 15 Ray Tracing 3（Light Transport & Global Illumination）
#### 辐照度/辐射通量密度 Irradiance
* 定义：The irradiance is the `power per` (perpendicular/projected) `unit area` incident on a surface point.单位面积上的能量。
  $$ E(x) \equiv \frac{d\Phi(x)}{dA} $$
  $$ [\frac{W}{m^2}]\ [\frac{lm}{m^2}=lux] $$
  * 与入射光线相垂直的单位面积接收到的能量，如果不垂直，则计算投影到垂直面上的部分接收到的能量值（即 $*cos\theta$ ）。（在Lambert's Cosine Law中有体现）
* 修正之前对点光源传播的相关概念的理解
  * 之前说光传播过程中 $I \rightarrow \frac{I}{r^2}$
  * 其实，对于Intensity来讲，作为“单位立体角上的能量”，无论远近，其上的能量是不变的，只是在近处，立体角对应的面积块比较小，远处对应的面积块比较大。
  * 而我们对“包围点光源的球壳”考虑的是“单位面积上的能量”，也即Irradiance $E$ 。
  * 那么在单位球壳上，由于均匀发射能量，应有
    $$ E=\frac{\Phi}{4\pi r^2}=\frac{\Phi}{4\pi} $$
  * 在较远处距离球心点光源 $r$ 处的单位面积能量则为
    $$ E'=\frac{\Phi}{4\pi r^2}=\frac{E}{r^2} $$
  * 因此单位面积上的能量，是按 $r^2$ 衰减的。
#### 辐亮度 Radiance
* 定义：The radiance (luminance) is the `power` emitted, reflected, transmitted or reveived by a surface, `per unit solid angle, per projected unit area`.单位立体角且单位面积上的能量。
  $$ L(p,\ \omega) \equiv \frac{d^2\Phi(p,\ \omega)}{d\omega\ dA\ cos\theta} $$
  $$ [\frac{W}{sr\ m^2}]\ [\frac{cd}{m^2}=\frac{lm}{sr\ m^2}]=nit $$
  * [自己的理解] $p$ 是指`per projected unit area`的`projected`投影面积
  * 用来描述“光线”的属性，渲染总是在计算“Radiance”。
  * 两个单位：分别在立体角和投影面积上做两次微分。
  * 物理理解：某单位面积上的能量，往某个方向（立体角）辐射的那部分能量。而光线也是从某个微小表面，往各个方向辐射出去的，再具体到一个特定方向，就能考虑到单束光线。
  * 也可以从上述已有概念延伸，考虑为Irradiance per solid angle或Intensity per projected unit area。
  * Incident Radiance：Incident radiance is the `irradiance per unit solid angle` arriving at the surface.
    $$ L(p,\ \omega)=\frac{dE(p,\ \omega)}{d\omega\ cos\theta} $$
    * 到达某单位面积上的能量中，从某方向辐射来，接收到的那部分能量。
  * Exiting Radiance：Exiting surface radiance is the `intensity per unit projected area` leaving the surface.
    $$ L(p,\ \omega)=\frac{dI(p,\ \omega)}{dA\ cos\theta} $$
    * 从某单位面积辐射出去的能量中，具体往某方向去的那部分能量。
#### 辐照度Irradiance vs. 辐亮度Radiance
Irradiance：total power received by area $dA$  
Radiance：power received by area $dA$ from "direction" $d\omega$  
&nbsp;![](note&#32;-&#32;image/GAMES101/img55.png) &nbsp;</br>
用式子来表示，可以从Radiance对立体角进行积分（即对各方向的能量求和）来回到Irradiance小块面积的总能量。
$$ \begin{aligned}
      dE(p,\ \omega) &= L_i(p,\ \omega)\ cos\theta\ d\omega \\
        E(p) &= \int_{H^2}L_i(p,\ \omega)\ cos\theta\ d\omega
  \end{aligned}$$
其中， $H^2$ 为Unit Hemisphere。因为小块面积与在单位半球范围内的方向，垂直向投影面积在 $[0, area]$ 之间变化，可以接收到能量，对这小块面积的总能量有贡献。

## 双向反射分布函数Bidirectional Reflectance Distribution Function（BRDF）
### **用辐射度量学解释反射** Reflection at a Point
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![](note&#32;-&#32;image/GAMES101/img56.png) &nbsp;</br>
* Radiance from direction $\omega_i$ turns into the power $E$ that $dA$ receives. 从某方向 $\omega_i$ 辐射进来的能量被一微表面 $dA$ 吸收为这微表面的Irradiance $E$。
  $$ dE(\omega_i)=L(\omega_i)\ cos\theta_i\ d\omega_i $$
* Then power $E$ will become the radiance to any other direction $\omega_o$. 然后能量再从微表面 $dA$ 往某方向 $\omega_o$ 辐射出去，变成每个方向上的 radiance $L$。
  $$ dL_r(\omega_r) $$
* 问题：从 $\omega_i$ 来的能量，经过微表面反射后辐射出去的每个方向 $\omega_o$ 上有多少能量？或者说微表面接收到能量后，往各个方向辐射出能量，那么这些能量在各个方向上是如何分配的？
* BRDF：The Bidirectional Reflectance Distribution Function (BRDF) represents how much light is reflected into each outgoing direction $\omega_r$ from each incoming direction. 定义了微表面 $dA$ 从一方向 $\omega_i$ 接收到的 irradiance ，会如何反射到另一个方向 $\omega_r$ 。

  $$ f_r(\omega_i\rightarrow\omega_r) = \frac{dL_r(\omega_r)}{dE_i(\omega_i)}=\frac{dL_r(\omega_r)}{L_i(\omega_i)\ cos\theta_i\ d\omega_i} [\frac{1}{sr}] $$

  [自己的理解] 也就是描述了反射到出射方向 $\omega_r$ 上的能量与微表面从入射方向 $\omega_i$ 接收到的能量之比。  
  所以BRDF其实就是描述光线和物体是如何作用的，通过BRDF定义了物体的材质。
* **反射方程 The Reflection Equation**
  $$ L_r(p,\omega_r) = \int_{H^2}f_r(p,\ \omega_i\rightarrow\omega_r)\ L_i(p,\ \omega_i)\ cos\theta_i\ d\omega_i $$
  * 任何一个着色点在不同光照环境下，任意入射方向对某出射方向的能量贡献。
  * 式子理解：$经过微表面反射到某出射方向的能量 = BRDF\times 微表面从各入射方向接收到的能量之和\int_{H^2}L_i(p,\ \omega_i)\ cos\theta_i\ d\omega_i$
  * 注意反射方程的入射项也包含其它物体的出射能量，不止光源。有递归性。

## **渲染方程 The Rendering Equation**
$$ L_o(p,\ \omega_o)=L_e(p,\ \omega_o) + \int_{\Omega^+}L_i(p,\ \omega_i)\ f_r(p,\ \omega_i,\ \omega_o)\ (n\cdot \omega_i)\ d\omega_i $$
* 考虑会发光物体，加上物体本身能够发出的能量 $L_e(p,\ \omega_o)$ 。
* $\Omega^+$ 与 $H^2$ 相同，也表示半球。当然另半球没有贡献不考虑。
* 为了便利，虽然 $\omega_i$ 是入射方向，但也作向外方向来考虑。
* 显然，单位向量的情况下，$cos\theta_i = n\cdot \omega_i$。
* 所有物体表面的光线传播满足该方程。
* 渲染方程的发表paper："The Rendering Equation."
### 解渲染方程
* 方程右部的 $L_i(p,\ \omega_i)$ 含有从经过其它物体弹射来的出射能量时，为未知项。
* 先将其它已知项，用算子/操作符operator形式，在数学上简写为
  $$ L=E+KL $$
  * 其中 $K$ 为反射操作符。
* 用这样的形式来解得递归定义的 $L$。
  $$ L=E+KL $$
  $$ IL-KL=E $$
  $$ L=(I-K)^{-1}E $$
* 【？？？】经过算子 $K$ 的某种性质，可以展开为
  $$ L=(I+K+K^2+K^3+...)\cdot E $$
  $$ L=E+KE+K^2E+K^3E+... $$
  * $E$ 表示光源直射，$K^nE$ 表示光经过 $n$ 次反射
  * 即将光线根据弹射次数进行了分解
  * 对弹射一次的 $KE$ 称`直接光照Direct Illumination`，弹射两次的 $K^2E$ 称`间接光照Indirect Illumination`。而 $KE+K^2E+K^3E+...$ 的总和，即为`全局光照Global Illumination`。
  * 在光栅化过程中，将物体投影到屏幕空间后进行着色，比较容易实现的是光源的直射以及弹射一次的直接光照。但是对于多次弹射的光线就比较难处理，因此在这方面光线追踪具有优越性。
  * 弹射多次后画面效果会收敛，亮度几乎感觉不到变化。因为能量守恒，不会无限增加。而相机快门的曝光是由于快门持续打开，能量会积累起来，最终导致曝光。而渲染中关注的则是“单位时间”的能量。
## 概率论Probability
### 随机变量
* $x$ ：随机变量 Random Variable. Represents a distribution of potential values.
* $p(x)$ ：概率 Probability. 随机变量取 $x$ 值的可能性大小。
  * $p \geqslant 0$
  * $\mathop{\Sigma}\limits_{i=1}^np_i=1$
* $X \sim p(x)$ ：概率密度函数 Probability density function(PDF). Describes relative probability of a random process choosing value $x$. 
### 期望
* $E$ ：期望 Excepted value of a Random Variable. The average value that one obtains if repeatedly drawing samples from the random distribution. 不断取随机变量，得到的均值。
  $$ E[X]= \mathop{\Sigma}\limits_{i=1}^nx_ip_i $$
### 连续型随机变量的概率密度函数Probability Density Function
* 概率密度函数 Probability density function(PDF). 该函数曲线图中， $x$ 轴为随机变量取值，取微元 $dx$ 的邻域往函数曲线作垂线，所得近似梯形区域的面积即为随机变量取邻域范围内值的概率。
  * $\int p(x)\ dx=1$，面积即积分，随机事件概率和为 $1$。
  * $E[X]=\int x\ p(x)\ dx$，离散的求和扩展到连续的积分。
  * 题外：概率密度函数为分布函数的导函数。因此概率密度函数上的一点为概率在该点的变化率（导数）。
### 随机变量函数Function of a random variable
* 若随机变量 $Y=f(X)$ 本身是一个关于随机变量 $X \sim p(x)$ 的函数
* 那么它的期望为
  $$ E[Y]=E[f(X)]=\int f(x)\ p(x)\ dx $$

# Lecture 16 Ray Tracing 4（）
## 蒙特卡洛积分Monte Carlo Integration
* 问题：求某函数 $f(x)$ 在 $[a,\ b]$ 间的定积分，但函数 $f(x)$ 的形式比较复杂，难以写出解析式。
* 黎曼积分：将 $[a,\ b]$ 拆分为微小区间的多份，每份可认为是小长方形，再求和。
* 蒙特卡洛积分：在积分域内随机点 $x_i$ ，每次随机点的值 $f(x_i)$ 作参考，求长为 $[a,\ b]$ ，高为 $f(x_i)$ 的长方形面积，多次随机并求均值作为积分值。
  * 定义：定积分 $\int_a^bf(x)dx$ ，随机变量遵循 $X_i \sim p(x)$ ，其值可以近似为 Monte Carlo Estimator 
    $$ F_N=\frac{1}{N}\mathop{\Sigma}\limits_{i=1}^{N}\frac{f(X_i)}{p(X_i)} $$
* 均匀分布采样 Uniform Monte Carlo Estimator ： $X_i \sim p(x)=C(constant)$
  * 则有 $\int_a^bp(x)\ dx=1$ ，代入得 $\int_a^bC\ dx=1$ ，因此 $C=\frac{1}{b-a}$
  * 代入 Monte Carlo estimator 有 $F_N=\frac{b-a}{N}\mathop{\Sigma}\limits_{i=1}^Nf(X_i)$，就是在域内采样，求和，并求平均
* 结论：以一种 $PDF$ 进行采样，知道采样点的函数值 $f(X_i)$ 及对应概率密度 $p(X_i)$ ，然后相除求和取平均即可。
  * 显然，采样越多，越接近真实值。
  * 积分域在 $PDF$ 中体现，因此蒙特卡洛本身不需要考虑积分域。
  * 积分域定义在什么值，就只能对什么值采样。

## 路径追踪Path Tracing
### Motivation
* Whitted-style ray tracing
  * Always perform specular reflections / refractions  
    光遇到光滑物体，作反射及折射
  * Stop bouncing at diffuse surfaces  
    遇到漫反射物体停止弹射
* Whitted-style的一些问题
  * 完全镜面反射的材质：(pure) specular，略带镜面高光又有点糊：glossy。对于glossy材质，反射光仍然沿镜面反射方向，这是不正确的
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img57.png) &nbsp;</br>
    模型：The Utah teapot
  * 遇到漫反射物体就直接进行着色，不考虑漫反射光线的继续弹射，因此漫反射物体之间的光线交互都没了。
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img58.png) &nbsp;</br>
    模型：The Cornell box，真实存在的模型。被广泛用来测试全局光照效果，因为没有全局光照效果天花板就是黑的，并且全是漫反射物体。  
    The Cornell box中墙体颜色染到盒子上的现象称为 Color Bleeding 。
* 考虑物理正确的渲染方程 $L_o(p,\omega_o)=L_e(p,\omega_o)+\int_{\Omega^+}L_i(p,\omega_i)\ f_r(p,\omega_i,\omega_o)\ (n\cdot \omega_i)\ d\omega_i$ 的两个问题
  * 需要用到半球上所有方向的radiance，解积分
  * 每个半球的积分都需要递归使用到其它半球的积分结果

### **A Simple Monte Carlo Solution（直接光照）**
* 考虑简单场景中一个点（自身不发光）的直接光照：场景中含面光源，一些其它物体（可能挡住光）
  * 那么需要求解的方程为
    $$ L_o(p,\omega_o)=\int_{\Omega^+}L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(n\cdot \omega_i)\ d\omega_i $$
  * 且暂时只考虑直接光照，即仅从光源来的光，那么就可以使用蒙特卡洛积分直接求解。
* compute the radiance at p towards the camera
  * $f(x) = L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(n\cdot \omega_i)$
  * 如何对半球采样：均匀采样 $p(\omega_i)=\frac{1}{2\pi}$
  * 因此近似为 
    $$ L_o(p,\omega_o) \approx \frac{1}{N}\mathop{\Sigma}\limits_{i=1}^N \frac{L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(n\cdot\omega_i)}{p(\omega_i)} $$
```cpp
// 伪代码
shade(p, wo)
  Randomly choose N directions wi~pdf // 根据PDF随机采样N个方向
  Lo = 0.0  // 初始化出射radiance
  for each wi
    trace a ray r(p, wi)  // 对每个方向生成一束光线
    if ray r hit the light  // 光线击中光源，说明光源有直接光照沿该方向照射到该点
      Lo += (1/N) * L_i * f_r * cosine / pdf(wi)  // 按蒙特卡洛积分求解
  return Lo
```

### **Global Illumination（引入间接光照）**
* 考虑一层递归：光源直接光照 Q 点，经弹射后间接照射 P 点。
  * Q 点沿 $\omega_i$ 弹射到 P 点的 radiance 也看作一种对 P 点而言的光源 radiance 。
  * 而 Q 点弹射出的 radiance ，即求 Q 点的出射到 $\omega_i$ 方向的直接光照渲染结果，由于设方向都朝外，因此为 shade(q, -wi)。
```cpp
// 伪代码
shade(p, wo)
  Randomly choose N directions wi~pdf // 根据PDF随机采样N个方向
  Lo = 0.0  // 初始化出射radiance
  for each wi
    trace a ray r(p, wi)  // 对每个方向生成一束光线
    if ray r hit the light  // 光线击中光源，说明光源有直接光照沿该方向照射到该点
      Lo += (1/N) * L_i * f_r * cosine / pdf(wi)  // 按蒙特卡洛积分求解
    /* 增加一个分支 */
    else if ray r hit an object at q
      Lo += (1/N) * shade(q, -wi) * f_r * cosine / pdf(wi) // 入射radiance L_i为q点弹射来的radiance shade(q, -wi)
  return Lo
```

### 问题
* `问题一：光线数量太多`
  * 指数级增长。$rays=N^{bounces}$
  * 仅当 $N=1$ 时不会炸，因此只采样一个方向。
```cpp
shade(p, wo)
  Randomly choose ONE directions wi~pdf // 根据PDF采样一个方向
  trace a ray r(p, wi)  // 对该方向生成一束光线
  if ray r hit the light  // 光线击中光源，说明光源有直接光照沿该方向照射到该点
    return L_i * f_r * cosine / pdf(wi)  // 按蒙特卡洛积分求解
  else if ray r hit an object at q
    return shade(q, -wi) * f_r * cosine / pdf(wi) // 入射radiance L_i为q点弹射来的radiance shade(q, -wi)
```
* $N=1$ 时，为路径追踪 Path Tracing。 $N!=1$ 时，为分布式光线追踪 Distributed Ray Tracing。
* 该方法产生一条从光源到视点的完整路径，而经过同一像素可能有多个路径，最后对多个路径求均值，也就相当于做了蒙特卡洛积分。
```cpp
ray_generation(camPos, pixel)
  Uniformly choose N sample positions within the pixel
  pixel_radiance = 0.0
  for each sample in the pixel
    shoot a ray r(camPos, cam_to_sample)
    if ray r hit the scene at p
      pixel_radiance += 1/N * shade(p, sample_to_cam) // 在这里取平均
  return pixel_radiance
```
* `问题二：递归边界`
  * 理论上自然界的光当然是不停地在弹射的
  * 但是作为计算机中的算法显然不能没有终止条件
* Solution: 俄罗斯轮盘赌Russian Roulette (RR)
  * 六个弹匣放 $P \leqslant 6$ 颗子弹。
  * 生存概率 $1-P$ ，死亡概率 $P$。
* 参考俄罗斯轮盘赌，以一定的概率决定是否继续弹射。
  * 设以一定的概率 $P$ 向某方向发射光线，最后得到的着色结果除以 $P$ ，即 $\frac{L_o}{P}$
  * 相对地，以 $1-P$ 的概率停止弹射，那么结果为 $0$ 。
  * 此时我们仍然可以得到着色结果的期望值
    $$ E=P*(\frac{L_o}{P}) + (1-P) * 0 = L_o $$
    是一个简单的二值离散型随机变量。
  * 所以虽然结果可能会有噪声，但是理论上是正确的。
  * 每次弹射 $P$ 的概率生存，那么期望弹射次数为
  $$ ？ $$
```cpp
shade(p, wo)
  Manually specify a probability P_RR
  Randomly select ksi in a uniform dist. in [0, 1]
  if (ksi > P_RR) return 0.0;   // 认为停止弹射

  Randomly choose ONE direction wi-pdf(w)
  trace a ray r(p, wi)
  if ray r hit the light
    return L_i * f_r * cosine / pdf(wi) / P_RR
  else if ray r hit an object at q
    return shade(q, -wi) * f_r * cosine / pdf(wi) / P_RR
```
* 至此，得到了正确的路径追踪算法，但效率不高。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img59.png) &nbsp;</br>
  Samples Per Pixel (SPP)：每个像素的路径数。 

### 在 Low SPP 的情况下提高渲染质量
* 涉及到从着色点选取的光线方向，能遇到光源的概率。均匀采样时，很多方向是浪费的，碰不到光源。所以要使用更好的 $PDF$ 进行采样。
* 从光源入手，直接将采样方向都定位到光源上。
* 设在某面积为 $A$ 的面光源上采样
  * $pdf = \frac{1}{A} (\int pdf\ dA = 1)$
  * 渲染方程是定义在立体角上的 $L_o = \int L_i\ f_r\ cos\ d\omega$
  * 而蒙特卡洛定义在什么值上，就要对什么值采样
  * 所以要将渲染方程写成在光源上的积分
</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img60.png) &nbsp;</br>

* 求 $d\omega$ 和 $dA$ 的关系
  * $dA$ 往着色点发射的光在单位半球上形成的投影面积就是 $d\omega$
  * 取 $dA$ 朝着色点方向的投影面积 $dA\ cos\theta'$ ，按立体角定义除以距离的平方即为 $d\omega$
    $$ d\omega = \frac{dA\ cos\theta'}{|x'-x|^2} $$
    注意 $\theta'$ 是面光源上一点与着色点连线和面光源自身法向量的夹角。
  * 代入渲染方程，改变积分域
    $$ L_o(p, \omega_o)=\int_A L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)\frac{cos\theta\ cos\theta'}{|x'-x|^2}\ dA $$
    此时，积分定义在光源上，同时对光源进行采样
    $$ f(x) = L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)\frac{cos\theta\ cos\theta'}{|x'-x|^2} $$
    $$ pdf = \frac{1}{A} $$
* 将直接光照与间接弹射做拆分，直接光照对光源作积分，其它部分用原来的方法均匀采样并赌博
  * case: 光源和着色点之间有遮挡物。从着色点往光源发射一条光线，测试中间是否有遮挡物。
```cpp
shade(p, wo)
  // contribution from the light source.
  L_dir = 0.0
  UNIFORMLY sample the light at a' (pdf_light = 1/A)
  Shoot a ray from p to x'
  if the ray is not blocked in the middle // 测试光源是否被挡住
    L_dir = L_i * f_r * cos_theta * cos_theta' / (|x'-p|^2) / pdf_light

  // contribution from other reflectors.
  L_indir = 0.0
  Test Russian Roulette with probability P_RR
  UNIFORMLY sample the hemisphere toward wi (pdf_hemi = 1/(2pi))
  trace a ray r(p, wi)
  if ray r hit a non-emitting object at q
    L_indir = shade(q, -wi) * f_r * cos_theta /pdf_hemi / P_RR
  
  return L_dir + L_indir
```
* 注：点光源难处理。

### Side Notes
* Path tracing
  * with physics, probability, calculus, coding
  * 目前工业界在用中
  * 路径追踪的正确性：http://www.graphics.cornell.edu/online/box/compare.html
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img61.png) &nbsp;</br>
* Ray tracing: previous vs. modern concepts
  * 以前的 ray tracing 指 Whitted-style ray tracing
  * 现在通常指按照光线传播方法渲染的思想
    * 单向/双向路径追踪 (Unidirectional & bidirectional) path tracing
    * 光子映射 Photon mapping
    * Metropolis light transport
    * VCM / UPBP...
* Things haven't covered
  * 如何在半球上均匀采样，如何对任意函数进行采样
  * 蒙特卡洛允许以任意 $pdf$ 采样，最佳选择：`重要性采样 Importance Sampling`
  * 随机数的质量：距离控制较好的随机数 Low discrepancy sequences 低差异序列
  * 把在半球和光源上的采样相结合： `Multiple Importance Sampling（MIS）`
  * 为什么对像素的各路径上 radiance 取均值，就是像素的 radiance ？要不要加权？像素代表什么？：`Pixel reconstruction filter`
  * 求出像素的 radiance 后，如何得到它实际的颜色：`Gamma校正 Gamma correction，curves，High-Dynamic Range（HDR图），color space`

# Lecture 17 Materials and Apperances
* 图形学中的材质 $Material = BRDF$
## 材质
### **漫反射 Diffuse / Lambertian Material** 
* 漫反射系数
  * 之前在 Blinn-Phong 模型处引入了漫反射系数，此处更严谨地进行定义。
  * 假设能量守恒。若点不发光，也不吸收光。那么微表面上接收多少光 $irradiance_i$ ，就反射多少光 $irradiance_o$ 。
  * 又设 diffuse 材质， radiance 均匀（uniform），入射出射的 irradiance 相同。则入射出射的 radiance 也相同。
  * 根据假设，将入射 radiance 与 BRDF 视作常量提到积分外。
    $$ \begin{aligned} L_o(\omega_o) &= \int_{H^2}f_rL_i(\omega_i)\ cos\theta_i\ d\omega_i \\ &= f_rL_i\int_{H^2}cos\theta_i\ d\omega_i \\ &= \pi\ f_r\ L_i \end{aligned} $$
    $$ 由 L_i = L_o $$
    $$ f_r = \frac{1}{\pi} $$
    此时为完全不吸收能量的 BRDF 。
  * 定义反射率 $albedo\ \rho \in [0,1]$ ：可以是数值、RGB三通道、光图。
    $$ f_r = \frac{\rho}{\pi} $$

### **镜面反射 Specular Reflection**
* Glossy material（BRDF）：有点镜面反射，又比完全的镜面粗糙。如抛光的金属。
* Ideal reflective / refractive material（BSDF双向散射分布函数)：水、玻璃球，有反射、折射，部分吸收。
* Perfect specular reflection
  * 反射向量求解
    * 几何推导见之前笔记w
    * 把角度投影到局部坐标系：以法向量为基准，定义平面上的方向与法向量夹角为仰角 $\theta$ ，平面 $\omega_i\ \overrightarrow{n}\ \omega_o$ 绕法向量 $\overrightarrow{n}$ 旋转所得方位角 $\phi$ 。（与立体角中对球上方向的表示方法相同）  
      观察入射方向与反射方向的俯视图，两者方位角相反。  
      </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img62.png) &nbsp;</br>  
      又反射，因此仰角必然也相同。两角确定反射方向。
* BRDF 能描述所有的反射，那么镜面反射的 BRDF 值为？ 
  * `Delta 函数。`
  * 此处认为出射方向只分布在镜面方向。

### **折射 Refraction**
* caustics现象：焦散，但现象成因是由于聚焦，而非散射。光线打到不平整的水面，往不同的方向折射，导致水下某些地方接收到了许多方向的光，形成亮条。对渲染领域是个难题，路径追踪不适合做这样的效果。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img63.png) &nbsp;</br>
* Snell's law 斯涅尔定律/折射定律
  * 钻石的折射率非常高，所以闪。
  * 折射向量求解，几何推导见之前笔记w
  * 求折射角余弦时，当根号下的值为负，折射不发生
    $$ cos\theta_t = \sqrt{1-(\frac{\eta_i}{\eta_t})^2\cdot (1-cos^2\theta_i)} $$
    由于 $1-cos^2\theta_i$ 必小于 $1$  
    式子无意义只能是 $\frac{\eta_i}{\eta_t} > 1$ 造成的  
    即入射介质折射率大于折射介质的折射率（密介质到疏介质），就产生全反射现象，不产生折射。
  * 所以在水下往上看，只能看到锥形区域。更外的范围都作全反射。
* 折射对应 BTDF （transmittance）。
  * BRDF、BTDF结合统称BSDF，双向散射分布函数。
* Fresnel Reflection / Term 菲涅耳项
  * 入射光与平面法线的角度决定了有多少光被反射、多少光发生折射。
  * 越接近垂直折射越多（穿过面），越与面平行反射越多（像镜子）。
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img64.png) &nbsp;</br>
    绝缘体 Dielectric $\eta=1.5$（玻璃） 的菲涅耳项。其中 S、P 为光的极化现象，光在两个不同方向的震动。（目前渲染基本不考虑）
  * 导体 Conductor （金属）在任何情况下的反射率都很高。（折射率是负数。）
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img65.png) &nbsp;</br>
  * 准确地求菲涅耳项（描述多少光被反射的量 $\in [0,1]$）：考虑不极化的光，对 S、P 两个方向上的反射率求值，再作平均。式子非常复杂。
  * Schlick's approximation：认为菲涅耳项从夹角为零度时的值 $R_0$ ，随夹角增大而不断上升，直到值为 $1$ 。（是拟合出来的近似曲线）
    $$ R(\theta)=R_0+(1-R_0)(1-cos\theta)^5 $$
    $$ R0=(\frac{n_1-n_2}{n_1+n_2})^2 $$

### **微表面材质/模型 Microfacet Material**
#### **Motivation**
* 从太空中远处往地球看会有高光，看不到地球表面的细节。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img66.png) &nbsp;</br>
#### **Microfacet Theory**
* 设物体表面粗糙。
  * Macroscale：flat & rough
  * Microscale：bumpy & specular，每个微表面看作镜面
  * 从远处看材质，近处看几何。
* Microfacet BRDF
  * 考虑微表面的法线分布，越光滑，法线分布越集中。反之法线分布越分散。
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img67.png) &nbsp;</br>
  * 因此微表面的粗糙程度可以用法线分布来描述。
    $$ f(i,o)=\frac{F(i,h)\ G(i,o,h)\ D(h)}{4\ (n,i)\ (n,o)} $$
    其中，$F(i,h)$为菲涅耳项 Feresel term，$G(i,o,h)$为几何项 shadowing-masking term ，$D(h)$为法线分布 distribution of normals（half-vector）。
  * $D(h)$ ：只有法线方向与 $\omega_i$ 和 $\omega_o$ 的 half-vector 方向一致时，能将该 $\omega_i$ 反射到 $\omega_o$ 的方向上去。所以 $D(h)$ 即法线向该 half-vector 方向上分布的那部分微表面。[决定项]
  * $G(i,o,h)$ ：考虑表面上的微表面之间会互相遮挡一部分光线。对表面本身而言就是自遮挡。（当光近乎平行于表面照射时易发生，这样的角度称为 Grazing Angle 掠射角。）该项就是用于修正这样的现象，如圆的边缘太亮就是因为掠射。

## 材质的分类
### **各向同性Isotropic / 各向异性Anisotropic Materials (BRDFs)**
* Isotropic材质：微表面的方向性很弱，法线分布比较均匀。
</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img68.png) &nbsp;</br>
* Anisotropic材质：如被磨过的金属，法线分布有明确的方向性。
</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img69.png) &nbsp;</br>

### **Anisotropic BRDFs**
* 如果 BRDF 描述的入射出射方向 $f_r(\theta_i,\phi_i;\theta_r,\phi_r)$ ，在方位角上旋转，不能得到相同的 BRDF ，即 $!=f_r(\theta_i,\theta_r,\phi_r-\phi_i)$ ，就是各向异性材质。（与绝对方位角、相对方位角都有关）
* 被打磨过的金属，会形成不同形状的高光区域。
</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img70.png) &nbsp;</br>
* 各向异性材质
  * 尼龙 Nylon ：比较接近各向同性。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img71.png) &nbsp;</br>
  * 天鹅绒 Velvet：一根一根的纤维，形成“体”，但看作表面，可以手动拨纤维。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img72.png) &nbsp;</br>

## BRDF的性质 Properties of BRDFs
* 非负性 Non-negativity 
  $$ f_r(\omega_i \rightarrow \omega_r) \geqslant 0 $$
* 线性性 Linearity
  $$ L_r(p,\omega_r) = \int_{H^2}f_r(p,\omega_i \rightarrow \omega_r)\ L_i(p,\omega_i)\ cos\theta_i\ d\omega_i $$
  * 如 Blinn-Phong 模型中将其分为 Diffuse、Specular、Ambient ，最后可以加和。
* 可逆性 Reciprocity principle
  $$ f_r(\omega_r \rightarrow \omega_i) = f_r(\omega_i \rightarrow \omega_r) $$
* 能量守恒 Energy conservation
  $$ \forall \omega_r\ \int_{H^2}f_r(\omega_i \rightarrow \omega_r)\ cos\theta_i\ d\omega_i \leqslant 1 $$
  * $L_i = 1$
  * 完全不吸收时取等，否则能量只会减少不会变多。
  * 是 Path Tracing 光线多次弹射后达到收敛的原因。
* 各向同性与各向异性 Isotropic vs. anisotropic
  * 各向同性 Isotropic：$f_r(\theta_i,\phi_i;\theta_r,\phi_r)=f_r(\theta_i,\theta_r,\phi_r-\phi_i)$，可以降维
  * 对所有 BRDFs ，根据可逆性 reciprocity：
    $$ f_r(\theta_i,\theta_r,\phi_r-\phi_i) = f_r(\theta_r,\theta_i,\phi_i-\phi_r) = f_r(\theta_i, \theta_r, |\phi_r-\phi_i|) $$

## BRDF的测量 Measuring BRDFs
### Motivation
* 实际通过测量的手段测得的量，如菲涅耳项等，与物理上使用的近似拟合曲线相差很大。
* 如果能靠测量得到，就可以直接用测量值。

### Image-Based BRDF Measurement
* 理想理论：以所有仰角、方位角方向往物体打光，拍摄，并到所有出射方向拍摄。
  * Gonioreflectometer仪器
* 四维的测量，非常复杂，所以若各向同性就能降维，按可逆性求方位角之差降维。

### BRDF测量结果的表示 Representing Measured BRDFs
* 测量完后的表示与存储
* BRDF库：MERL BRDF Database（MERL三菱电子实验室）
  * 很多各向同性材质，对降维后的 $(\theta_i,\theta_o,|\phi_i-\phi_o|$ 做 $90*90*180$ 次测量。结果存入三维数组，并做了压缩。

# Lecture 18 Advanced Topics in Rendering
## 高级光线传播 Advanced Light Transport
* 目前业界方法：Path Tracing。因为可靠性高。
### Biased vs. Unbiased Monte Carlo Estimators
* 无偏 unbiased：取任意样本数，得出的期望都是真实值（需要求的积分值）。
* 有偏 biased：其它情况。
  * 一致 consistent：虽然有偏，但是样本数趋向无穷时能收敛。

### 无偏光线传播方法 Unbiased light transport methods
* Path Tracing 也是无偏方法。
#### **双向路径追踪 Bidirectional path tracing (BDPT)**
* 回忆：路径追踪，光线从相机射出，弹射到光源。
* 双向
  * 分别从相机和光源射出半路径。
  * 连接半路径。
* 在光线来源集中在某一部分，环境中漫反射材质较多时（导致路径追踪中很多采样是无效的，无法遇到光源），效果很好。
</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img73.png) &nbsp;</br>
* 缺点：但相同分辨率和采样率下，BDPT要更慢一些。

#### **Metropolis light transport (MLT)**
* A Markov Chain （马尔可夫链） Monte Carlo (MCMC) appication
  * 马尔可夫链：根据当前的样本，生成附近的下一个样本。给定足够的时间，可以“以任意函数形状为PDF”生成样本。
  * 采样一个函数、使得方差variance最小的PDF：与积分函数形状一致的PDF。
  * 而马尔可夫链，能对任意未知函数，生成样本，使样本分布与被积函数形状一致。
  * 所以可以使用这样的方法，对一条路径，在附近生成与之相似的其它路径。在局部范围内有很好的效果。
* 思想
  * 对路径上弹射点作微小扰动，得到新的路径。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img74.png) &nbsp;</br>
* 在复杂场景下效果很好：光源密集，其它物体间接照亮。caustics现象（泳池下的聚焦），假设水底diffuse，则光线要经过specular-diffuse-specular三层（SDS路径），同样由于漫反射，有效采样很小，而MLT可以根据有效采样在附近生成。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img75.png) &nbsp;</br>
* 缺点
  * 难以分析收敛速度。（而MC中可以分析提高一倍sample能否降低一倍variance）
  * 所有操作都是局部的，因此不同像素点附近的收敛程度不同，导致结果"dirty"
  * 因此也不能用在动画。

### 有偏 Biased
#### **光子映射 Photon mapping**
* 有偏、一致 & 两步法
* 适合SDS路径和渲染caustics
* 实现方法（的一种）
  * 从光源发射光子，遇到diffuse停止，得到物体上的光子分布
  * 从相机射出光线，遇到diffuse停止
  * 计算：local density estimation
    * 思想：区域中停留光子越多的部分越亮
    * 对每个着色点，取附近最近的 $n$ 个光子（范围查询算法），求出这些光子所占的面积，然后求这块区域的光子密度
* 有偏的原因
  * 计算Local Density Estimation的时候取的是近似值
    $$ \frac{dN}{dA} != \frac{\delta N}{\delta A} $$
  * 但当物体上的光子密度很大时，相同光子个数覆盖的面积越小，误差也就越小，趋向无穷时会收敛。
* 为什么不取邻近的固定区域：这样虽然光子数能增大，但是面积固定不变小，无法收敛，永远是有偏且不一致的。

#### **Vertex connection and merging (VCM)**
* 结合光子映射和双向路径追踪。
* 思想：
  * BDPT中，如果两个子路径走到同一个面，就不能用相连（连接需要弹射）
  * 利用这种情况，在面上做光子映射
* 在电影中有应用

### 实时辐射度算法 Instant radiosity (VPL / many light methods)
* 思想：将被照亮的面都认为是光源。
* 做法：
  * 从光源射出子路径sub-paths，经过弹射，把停住的地方认为是新的光源Virtual Point Light(VPL)
  * 生成VPL后，用这些新光源进行渲染
* 缺点
  * 一些地方奇怪地发光了，涉及计算时使用的距离平方项 $\frac{1}{r^2}$ ，当距离极近时会很大。
  * VPL不能做glossy材质

## 高级外观建模 Advanced Apperance Modeling
* Apperance：外观即材质，BRDF
### 非表面模型 Non-surface models
#### **散射介质 Participating media**
* fog、cloud等，定义在空间中而不是表面上
* 光在行进过程中，遇到散射介质，发生
  * 介质本身发光
  * 被介质吸收
  * 被介质散射：介质中的小晶体随机地将光线分散到各个方向，以及接收到其它晶体散射出的光线
* 如何进行散射：类似BRDF定义了物体如何反射光线，`Phase Function`相位函数定义了介质内的晶体如何对光线进行散射。
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img76.png) &nbsp;</br>
* 渲染方法
  * 选一方向前进 Randomly choose a direction to bounce
  * 选择前进距离 Randomly choose a distance to go straight
    * 能走多远由介质的吸收能力决定
  * 计算最终到达人眼的路径（对视觉整体效果？）的贡献
* 注意散射介质的计算不考虑渲染方程，由其它方程定义。

#### **Hair / fur / fiber (BCSDF)**
##### **头发 Human Hair**
* 头发会一根一根飘，所以要考虑光线和曲线如何作用。
* 头发上的两种高光：有色与无色
* 简单模型 Kajiya-Kay Model（SIGGRAPH 1989 “*Rendering fur with three dimensinal textures.*”）
  * 假设头发的模型是根圆柱
  * 考虑光线命中圆柱，散射出一个圆锥，同时又有一些散射到四周（类似diffuse+specular）
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img77.png) &nbsp;</br>
* Marschner Model（SIGGRAPH 2003 “*Light Scattering from Human Hair Fibers.*”）
  * 考虑光线命中圆柱发生的三种作用：  
    ① 反射的部分，记作 $R$ 。   
    ② 穿进头发丝内部，发生折射记作 $T$ ，而光线要穿过一根头发，穿进再穿出，会发生 $TT$ 传播。  
    ③ 折射进头发丝后，在内壁发生一次折射，然后再穿出的 $TRT$ 传播。
  * 把头发 treat as Glass-like cylinder 玻璃圆柱：包含外层的表皮cuticle，内层的皮质cortex(absorbs)
    * 认为头发内部有色素，会吸收光
  * 对每根头发考虑三种情况的作用，然后开始渲染，跑到世界的尽头（x
##### **毛发 Animal Fur**
* 动物毛发与人的头发在生物学上的对比
  * 人和动物毛发的共同点是三层结构：外表皮Cuticle、内部的皮质Cortex（absorbs light）、最内层的髓质Medulla（scatter light）  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img78.png) &nbsp;</br>

  * 区别：人的髓质很细，动物的髓质非常大，所以光线更容易发生散射。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img79.png) &nbsp;</br>

    加入对髓质的模拟之后的模型效果：
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img80.png) &nbsp;
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img81.png) &nbsp;</br>
* Double Cylinder Model
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img82.png) &nbsp;</br>
  * 在 Marschner Model 的三种情况基础上再加两种情况：  
    ④ $TT^s$ ：在穿进毛发、经过髓质的时候被发散到各个方向  
    ⑤ $TRT^s$ ：同样考虑穿进毛发时与髓质的交互  
    即只要进入毛发内就考虑可能被髓质散射。
  * 在猩球崛起、狮子王HD中应用拿到最佳视觉效果奖提名（很遗憾最终没有获得（x
  * YanLingQi Model hhh

#### **Granular material**
* 颗粒材质模型
* 还没有比较好的解决办法。

### 表面模型 Surface models

#### **Translucent material (BSSRDF)**
* translucent 半透明材质：玉石、水母
  * 光线射入后，在内部发生散射，从另一个地方射出
* 这种物理现象称为次表面散射 Subsurface Scattering
  * 对 BRDF 的延伸
  * BRDF：从某点进，某点出
  * BSSRDF：从某点进，另一点出（SS即Subsurface Scattering）
* BSSRDF：generalization of BRDF; exitant radiance at one point due to incident differential irradiance at another point.
    $$ S(x_i, \omega_i, x_o, \omega_o) $$
  * Generalization of rendering equation: integrating over all points on the surface and all directions. 考虑某个点时，要加入从其它点入射，从该点出射的情况，考虑其贡献，即对次表面面积再做积分。
    $$ L(x_o, \omega_o)=\int_A \int_{H^2} S(x_i,\omega_i,x_o,\omega_o)\ L_i(x_i,\omega_i)\ cos\theta_i\ d\omega_i\ dA $$
  * Dipole Approximation ：假设材质表面的内外各有一光源，模拟类似次表面散射的效果。

#### **Cloth**
* 布料：一系列缠绕的纤维构成的。
  * 肉眼可见的一根毛，算一种“纤维” Fiber。
  * 不同的纤维缠绕成一“股” Ply。
  * 不同的股再缠绕形成“线” Yarn。
* 渲染方法
  * 近似看成表面。
  * 把空间中的性质按空间分割成微小的块，考虑每块里纤维的朝向等性质，然后转化成光的散射等，类似渲染云这类的体积。
  * 知道纤维的缠绕方法，就按纤维一根一根渲，当头发渲。
  * 以上三种方法，目前都有使用。

#### **Detailed material (non-statistical BRDF)**
* Motivation
  * 很多情况下渲染出的结果过于完美，但实际上的物体表面不会那么光滑。
* YLQ Model再现！贡献统计：
  * 细节渲染：有划痕的水壶，各向异性高光的水壶
  * 毛发模型
  * Real-Time Ray Tracing
* 微表面模型的细节
  * 如果使用的法线分布是光滑的曲线，那么必然遗失很多细节，所以要用很凹凸不平的法线分布
  * 而单纯使用路径追踪会很慢，因为确定法线分布以后，认为微表面是镜面反射的话，会产生很多无效的采样，从相机发出的光反射不到光源，从光源出发的光反射不到相机。
  * 而相机看到的一个像素其实是覆盖很多微表面的，因此先算出对应区域的微表面块法线分布，就能在对该像素渲染时，以这个法线分布，替换掉镜面反射的光滑分布曲线。
  * 但引入细节后，几何光学就不足以解决问题：当物体小到与光的波长相当的时候，就不能假设光是直线传播的，会产生衍射和干涉等问题。
  * 此处省略波动光学相关内容（在复数域上做积分等）。
  * 波动光学得出的BRDF与几何光学的BRDF有相似处，但又有特点：是不连续的。

### Procedural apperance
* 噪声函数：定义在空间中，对任意 $(x,y,z)$ 可给出相应值。
* 常用噪声函数：Perlin Noise等
  * 可以用于生成地形、水面、木头纹理（auto desk）
  * 可以将物理上的性质与噪声结合到一起
* Houdini：专做程序化材质，先生成程序化

# Lecture 19 Cameras, Lenses and Light Fields
* 图形学的两种合成（synthesis）成像方式：光栅化、光线追踪。
* 捕捉（capture）成像方式：把物理世界中存在的东西变成图像（相机拍照片）。
* Image = synthesis + capture
* 目前成像技术的研究
  * 在微小时间内能看到的光的传播，研究光在空间中传播的过程：`Transient Imaging`
  * `Imaging` 本身在计算摄影学 Computational Photography 中研究得更多。
## 相机 Cameras
### **小孔成像**
* 原因：光沿直线传播，假设小孔在物体中心，物体上部的光向下通过小孔，下部的光向上通过小孔，因此在成像平面中产生倒影。
* 针孔摄像机 Pinhole camera
### 快门 shutter：控制光能否进入相机内，且在多少时间内可以进入。
### 传感器 sensor：其上一点记录 irradiance 。
* 所以它不能过滤特定方向上的光，也就没办法直接用传感器来拍摄。（不过现在有巨巨正在研究，说不定以后就可以了（
### 针孔相机成像过程 Pinhole Image Formation
* 用针孔相机原理做光线追踪，没有景深、虚化的效果。
### **视场 Field Of View (FOV)**：相机能看到的视野范围
* $\Join$ 相似三角形：高度 h 、到对顶点焦距 f 、对顶点角度 FOV
  $$ FOV = 2\ arctan\ (\frac{h}{2f}) $$
* 不同的视场决定了不同的视野，和传感器大小、焦距都有关。
* 通常以 $35mm-format\ film（36\times24mm）$ 的传感器大小作为基准，再取各种长短的焦距，来定义相机的视野大小。
  * 如 $17mm$ ，同传感器大小标准下，焦距短，FOV大（104°），因此是广角镜头。
  * $50mm$ 普通，47°。
  * $200mm$ telephoto lens 长焦/远摄镜头，12°。
  * 对于手机而言，一般 $28mm$ 焦距，但手机中实际传感器大小很小，只是给出了等效到 $35mm$ 标准的焦距以供参考。
### **曝光 Exposure（H）**
$$ Exposure = Time \times Irradiance $$
$$ H = T + E $$
* $Time（T）：$即 Exposure Time，由快门 shutter 控制。
* $Irradiance（E）：$传感器上单位面积接收到的光的能量，由透镜光圈大小 lens aperture 和焦距 focal lenth 决定。
* 因此相机与渲染不同，关注的不是单位时间的能量，而是曝光时间中所接收到的所有能量总和。
* Exposure controls in photography
  * Aperture size：光圈是仿生设计，类似人的瞳孔。在相机中光圈大小可以通过 f-stop 控制，最大与镜头大小相同。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img83.png) &nbsp;</br>
  如图以 F 数控制。  
  F-number（F-stop），记作FN或F/N。非正式理解：光圈直径的逆（倒数）。
  * Shutter speed：快门开放的时间长短。快门速度越快，曝光时间越短。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img84.png) &nbsp;</br>
  如第一张图，千分之一秒。  
  快门首先起到调节曝光度的作用。另外，由于快门的开启和关闭必然有一过程，其会造成`运动模糊Motion Blur`。即快门开启过程中，物体运动了一段距离，传感器取均值后产生的模糊效果。  
  运动模糊能给人眼体现速度，用于呈现更逼真的视觉效果。还可以起到一定反走样的效果。  
  当物体的运动速度和快门速度接近时，产生 `Rolling Shutter` 问题，结果图像上物体扭曲，因为物体不同时间处于不同位置并分别被记录下来。
  * ISO gain（感光度）：在这里可以暂时简单地认为，对接收到的光能量以某比例放大。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img85.png) &nbsp;</br>
  比如将一幅很暗的图乘上ISO值，提升曝光度，使其变亮。在这过程中，不仅光能量信号被放大了，其中影响噪声的量也被放大了。所以通常不应调整该值。
  * 综合：增大几倍F数，即光圈直径减小，就可以相应增大几倍快门暴露时间提高曝光度，但形成的结果不是完全相同，因为两者分别会影响景深DOF和运动模糊。  
* 应用
  * 高速摄影：用很短的快门时间，很大的光圈拍。如子弹穿物。
  * 延迟摄影（拉丝）：用很小的光圈，很长的快门时间。如拍远处的飞机起飞或着陆。

## 透镜 Lenses
* 科普时间
  * 现在的相机一般都是用多层透镜组构成。
  * 实际的透镜可能一面凸一面平，无法把光聚集到一点。
* CG中研究的透镜：理想薄透镜Ideal Thin Lens，不考虑透镜厚度。
  * 平行光射入，产生焦点。
  * 同理，经过焦点的光必被透镜散射成平行光形成图像。
  * CG中的假设：薄的棱镜可以任意改变焦距。（现在的相机中通过不同透镜的组合来做到这一点。）
### **透镜相关物理规律**
* 平行光聚到焦点，过焦点的光变成平行光出射。
* 对称性：穿过透镜中心的光不发生改变。
* The Thin Lens Equation 
  * 定义物距 $z_o$ 、像距 $z_i$ 、焦距 $f$。
  * 则有
  $$ \frac{1}{f} = \frac{1}{z_i} + \frac{1}{z_o} $$
  * 推导过程（高斯透镜理论）
  </br>&nbsp;![](note%20-%20image/GAMES101/img86.png) &nbsp;</br>
  ① 列出两对相似三角形的相似比
  $$     \left\{
    \begin{aligned}
        \frac{h_o}{z_o-f} = \frac{h_i}{f} \\
      \frac{h_o}{f} = \frac{h_i}{z_i-f}
    \end{aligned}
    \right. $$
  ② 变换易得
  $$ \frac{h_o}{h_i} = \frac{z_o-f}{f} = \frac{f}{z_i-f} $$
  ③ 展开消去即可得等式。（该等式也称为 Gauss Thin Lens Equation）
### **Defocus Blur**
* Circle of Confusion（CoC，弥散圆）
  </br>&nbsp;![](note%20-%20image/GAMES101/img87.png) &nbsp;</br>
  * 物体在实际成像面（感光面）上投影出的圆形范围
  * 这个范围中得到的内容不止有通过透镜而来的光，还有在同侧前方的光，也投影到相应位置。
  * CoC的计算：同样使用相似三角形
  $$ \frac{C}{A} = \frac{d'}{z_i} = \frac{|z_s-z_i|}{z_i} $$
* 光圈越大，期望效果越模糊。
* F-Number 正式定义
  * The f-number of a lens is defined as the focal length divided by the diameter of the aperture. 即 
    $$FN = \frac{f}{d_{lens}}$$
* 因此计算CoC时的光圈大小 $A$ 可用 $\frac{f}{N}$ 来计算。
### **光线追踪景深效果的一种设定方案**
![](note%20-%20image/GAMES101/img88.png)
* 确定成像面大小Sensor、透镜焦距、光圈大小。
* 确定物体面Subject plane离光圈的物距 $z_o$
  * 根据薄透镜公式求出成像面Sensor到光圈的像距 $z_i$
* `渲染过程`
  * $x'$ 为遍历到的成像面上一个像素
  * 由于光线穿过透镜中心不会改变方向，因此将 $x'$ 与透镜中心相连，求出在物体面上的聚焦点 $x'''$，那么从出发像素点 $x'$ 往透镜上任意一点 $x''$ 发射的光线，都会聚焦到 $x'''$处。
  * 因此要渲染的像素 radiance 就是各个 $x''$ 到 $x'''$ 方向的光线作出的贡献。
### **景深Depth of Filed**
* 光圈大小会使部分画面内容模糊，但在focal plane上总是清晰的。因此光圈大小其实是影响模糊的范围。
* 景深：场景中一定深度范围的内容，在成像面附近形成一段区域，这块区域的 CoC 认为足够小，可以不被人眼察觉它是模糊的。即场景中成像清晰的一段范围。
* 用景深的最近、最远处，分别发射光线穿过透镜的上下边缘作计算。（ppt p61）

## 光场 Light Field / Lumigraph（in Lecture 20）


# Lecture 20 Color and Perception


# Lecture 21 Animation

# Lecture 22 Animation Cont.


# Experiment
## 环境配置
* Windows10 + vscode + wsl(ubuntu 18.04LTS)
* 主机和WSL数据交换
  * `cp -a /mnt/f/balabala /home/balabala`
* opencv在windows下解压再塞进去会报错，保险起见放进去再解压
* 作业压缩包解压出来文件夹带中文会乱码
  * 删除乱码名文件夹
    * `ls -i`获取文件夹数字ID
    * `find . -inum <numid> -exec rm {} -rf \;` 或 `find ./ -inum <numid> -print -exec rm {} -rf \;`
  * 直接Windows摸到`C:\Users\<username>\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu18.04onWindows_79rhkp1fndgsc\LocalState\rootfs\home\balabala`去解压hhhhh然鹅发现WSL里并不改变（……怕了怕了把状态还原回去了
  * Windows下生成的zip文件中编码GBK/GB2312等，在Linux下默认解压用UTF-8所以会乱码。可以`unzip -O CP936 xxx.zip`。但是会生成很XX的文件夹名。
  * ……作业还是在windows里解压好把文件夹拉进去安全
* 编译
  * 在main.cpp目录下
  * `mkdir build`
  * `cd build`
  * `cmake ..`
  * `make`编译
  * `./Transformation`可执行文件名，在CMakeLists.txt中可修改
## HW1
* 框架里main函数里的两个输入给出的zNear, zFar是正，由于看向-z轴所以应该改为负数。
* 绕任意轴旋转敲罗德里格斯的时候注意对偶矩阵
## HW2
* `std::transform(l, r, res, op)`
  * 将`(l, r)`范围内的每个元素作为`op`的第一参数调用`op`，结果存入`res`开头的范围内
  * `op`：函数指针、函数对象或lambda表达式
* MSAA
  * 维护四倍大小的sample_frame_buf和sample_depth_buf
  * 四个采样点采样完根据四个采样色值resolve该像素点的颜色
## HW5
* primary ray生成
  * https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
  * 主要是根据设定的像素平面比例，确定视线看向的点在实际成像面上是什么
    * 遍历像素 `x: [0, width-1], y: [0, height-1]`
    * 取到像素中心 `+0.5`
    * 转化到 `[0, 1]`，分别除以 `width` 和 `height`
    * 考虑视线 `(0, 0)` 看向成像面中心，所以 `*2-1` 转化到 `[-1, 1]`
    * 然后分别 `*scale` 、 `*scale*AspectRatio` 拉伸
  * 注意点
    * 图片原点(0, 0)于左上角，成像空间原点在图片中心，y值取负
* 射线与三角网格相交
  * 虽然学的时候感觉分解成与平面相交，再判交点是否在三角形内感觉很友好
  * 事实证明写代码的时候不用推导，数学就是代码简化之光啊（……

## FAQ
### HW3
* bump mapping 部分的 h(u,v)=texture_color(u,v).norm, 其中 u,v 是 tex_coords, w,h 是 texture 的宽度与高度  
* rasterizer.cpp 中 v = t.toVector4()  
* get_projection_matrix 中的 eye_fov 应该被转化为弧度制  
* bump 与 displacement 中修改后的 normal 仍需要 normalize  
* 可能用到的 eigen 方法：norm(), normalized(), cwiseProduct()  
* 实现 h(u+1/w,v) 的时候要写成 h(u+1.0/w,v)  
* 正规的凹凸纹理应该是只有一维参量的灰度图，而本课程为了框架使用的简便性而使用了一张 RGB 图作为凹凸纹理的贴图，因此需要指定一种规则将彩色投影到灰度，而我只是「恰好」选择了 norm 而已。为了确保你们的结果与我一致，我才要求你们都使用 norm 作为计算方法。
* bump mapping & displacement mapping 的计算的推导日后将会在光线追踪部分详细介绍，目前请按照注释实现。

# More
* B样条 www.bilibili.com/video/av66548502
* GTC GPU Technology Conference Nvidia 
  * DLSS 2.0：无损精度和消耗放大图片 知乎文刀秋二
  * RTXGI 全局光照 https://developer.nvidia.com/rtxgi
* YLQ's way of learning things
  * WHY, WHAT, then HOW
  * 为什么学、这啥玩意、如何运作
* 十个渲染最真实的人物模型
  * https://cgelves.com/10-most-realistic-human-3d-models-that-will-wow-you/
## 相关论文
* 头发材质Kajiya-Kay Model：SIGGRAPH 1989 *Rendering fur with three dimensinal textures.*
* 头发材质Marschner Model：SIGGRAPH 2003 *Light Scattering from Human Hair Fibers.*

</br></br>
> # The End
</br></br>

# 备用

</br>&nbsp;![] &nbsp;</br>

$\leqslant \geqslant \forall$

$$ \mathop{\Join}\limits_{i\ \theta\ j} $$

$$\begin{aligned} L_s &=  \\ &=  \end{aligned}$$


$$
    \left\{
    \begin{aligned}
        x' & = x + t_x \\
        y' & = y + t_y 
    \end{aligned}
    \right.
$$

$$
    
    \left(
    \begin{matrix}
        x' \\
        y'
    \end{matrix}
    \right)
$$

<!-- 图片示例 -->
![][<tag>]
[<tag>]:<BASE64STR>

<!-- 题注 -->
一个题注[1]$^{[1]}$

[1]:cannotaddspace失败的题注示例

* 为了自动生成的目录格式，设置EOL的换行符号改成了\n，原auto
  * 不同系统换行符制定不同

    系统 | 换行符
    :---:|:---:
    Windows|\n\r
    Unix|\n
    Mac|\r

光线与长方体求交
* 考虑三维光线与二维平面矩形求交点  
  设在 $xOy$ 平面上作平面矩形，令其 $z=k$ ， $x \in [x_0, x_1]$ ， $y \in [y_0, y_1]$  
  由光线（空间直线）参数形式可知
  $$ \overrightarrow{P(t)} = \overrightarrow{a} + t\cdot \overrightarrow{b}$$
  拆分到三维
  $$ \left\{\begin{aligned} x_t &=& x_a+t\cdot x_b \\ y_t &=& y_a+t\cdot y_b \\ z_t &=& z_a+t\cdot z_b \end{aligned}\right.$$
  其中已令 $z_t = k$ ，可得参数 $t=\frac{k-z_a}{z_b}$  
  将 $t$ 代入上两式求得 $x_t、y_t$  
  最后检验是否分别在 $[x_0,x_1]、[y_0,y_1]$ 范围内

三角函数积分公式  
∫sin x dx = -cos x + C  
∫ cos x dx = sin x + C  
∫tan x dx = ln |sec x | + C  
∫cot x dx = ln |sin x | + C  
∫sec x dx = ln |sec x + tan x | + C  
∫csc x dx = ln |csc x – cot x | + C  
∫sin ²x dx =1/2x -1/4 sin 2x + C  
∫ cos ²x dx = 1/2+1/4 sin 2x + C  
∫ tan²x dx =tanx -x+ C  
∫ cot ²x dx =-cot x-x+ C  
∫ sec ²x dx =tanx + C  
∫ csc ²x dx =-cot x+ C  
∫arcsin x dx = xarcsin x+√（1-x²）+C  
∫arccosx dx = xarccos x-√（1-x²）+C  
∫arctan x dx = xarctan x-1/2ln（1+x²）+C  
∫arc cot x dx =xarccot x+1/2ln（1+x²）+C  
∫arcsec xdx =xarcsec x-ln│x+√（x²-1）│+C  
∫arccsc x dx =xarccsc x+ln│x+√（x²-1）│+C  