> # GAMES101 计算机图形学
> * B站：av90798049
> * 主讲人：闫令琪
> * PDF课件：http://www.cs.ucsb.edu/~lingqi/teaching/games101.html
> * 作业提交：http://www.smartchair.org/GAMES2020Course-YLQ

# Lecture 01 Overview of Computer Graphics
## What is Computer Graphics

## Why study Computer Graphics
* 游戏
  * 《只腕之狼》
  * 《无主之地》
* `好的画面`判断标准之一：是否足够亮。（`全局光照`的好坏）
* 电影（特效）
  * 《The Matrix》（《黑客帝国》） 1999.
  * 《Avatar》（《阿凡达》） 2009.
* 动画Animation
  * 《Zootopia》（《疯狂动物城》） 2016.
  * 《Frozen 2》（《冰雪奇缘 2》） 2019.
* 设计Design
  * Computer Aided Design
  * 室内设计渲染（酷家乐）
* 可视化Visualization
  * 将物理信息->生成为视觉信息
* 虚拟现实Virtual Reality
  * VR：全电脑生成
  * 增强现实AR：现实+生成
* 数码插画Digital Illustration
* 模拟Simulation
  * 特效、仿真、动画、物理模拟
* 图形用户界面Graphical User Interfaces
* 字体Typography
  * The Quick Brown Fox Jumps Over The Lazy Dog（含所有26个字母）
### 小结
* 输入：理解真实世界
* 和真实世界的交互
* 处理：研究新的计算方法
* 输出：研究新的显示方法

## Course Topics
### Four Topics
* 光栅化Rasterization
  * 实时：一秒30帧（30frames per second）
* 曲线曲面Curves and Meshes
  * 如何表示
  * 如何变化
* 光线追踪Ray Tracing
  * 动画和电影主要使用，质量高
  * trade off以A换B
  * 目前的实时光线追踪
* 动画模拟Animation/Simulation

### Out of the Course
* API：OpenGL/DirectX/Vulcan
* 3D Model：Maya/3DS MAX/Blender
* Engine：Unity/Unreal Engine
* Computer Vision：理解视觉信息
  * CG与CV  
    1. Model：几何形体，材质，光照等
    2. Image：图片
    3. CG's Rendering：Model->Image
    4. Computer Vision：Image->Model（从图片中进行理解，如三维重建）
    5. CG Model->Model：材质如何更好地建模等
    6. Image Processing Image->Image

## Course Logistics
* PDF课件：http://www.cs.ucsb.edu/~lingqi/teaching/games101.html
* 作业提交：http://www.smartchair.org/GAMES2020Course-YLQ
* 大作业：Do what you like:)


# Lecture 02 Review of Linear Algebra
## Graphics' Denpendencies
* Basic mathematics
  * Linear algebra, calculus, statistics
* Basic physics
  * Optics光学, Mechanics力学
* Misc
  * Signal processing信号处理
  * Numerical analysis数值分析
* a bit of aesthetics美学

## Vectors向量/矢量
* 在图形学领域，默认向量为列向量

## Dot product点积
* 注意多维点积：直接对应相乘之和
* `图形学中主要应用`
  * `求向量夹角`：$\cos\theta = \frac{\overrightarrow{a} \cdot \overrightarrow{b}}{ |\overrightarrow{a}| \cdot |\overrightarrow{b}| }$
  * `求向量`$\overrightarrow{b}$在$\overrightarrow{a}$方向的`投影`：  
    $\overrightarrow{b_投} = \overrightarrow{a_{unit}}（方向） \cdot |\overrightarrow{b_投}|（长度）$  
  * `Decompose a vector分解向量到两个方向`
  * `Measure how close two directions are计算两个向量的距离（接近/远离）`：点积越接近1越近，垂直0，越远越接近反向-1。eg. 金属物体高光，在物体附近有高光区，可以看到这种高光。所以需要判断向量之间的距离。
  * `Determine forward/backward给出向量前与后的信息`：以某向量为基准，判断大致方向（根据点乘的正负零）

## Cross product叉积
* `图形学中主要应用`
  * `判定左/右`
    * 常规二维坐标系，$\overrightarrow{a} \times \overrightarrow{b}$为正则$\overrightarrow{b}$在$\overrightarrow{a}$在逆时针方向
  * `判断内/外`
    * $A、B、C$ 逆时针三点，判断 $P$ 是否在三角形内
    * ① $\overrightarrow{AB} \times \overrightarrow{AP}$为正，$P$ 在 $\overrightarrow{AB}$ 的左侧  
      ② $\overrightarrow{BC} \times \overrightarrow{BP}$为正，$P$ 在 $\overrightarrow{BC}$ 的左侧  
      ③ $\overrightarrow{CA} \times \overrightarrow{CP}$为正，$P$ 在 $\overrightarrow{CA}$ 的左侧
    * 若点为乱序，则判断点统一在三条边的左侧或右侧。
    * `corner case`边界情况：叉乘为0，穿边，自己决定在内在外即可。
  * Orthonormal Bases/Coordinate Frames建立三维坐标系（注：OpenGL是左手系）
    * 叉乘建立三维坐标系，向量分解到三维投影。

## Matrix矩阵
* Matrix-Vector Multiplication矩阵和向量的乘积
  * `默认列向量，向量在右侧`
* 通过dual matrix可以将向量乘积写成矩阵形式

# Lecture 03 Transformation
## Why study transformation
* Modeling模型变换：相机的移动、人物部位旋转、动画由各种变换组成
* Viewing视图变换：3D to 2D projection投影变换

## 2D Transforms二维变换
* Scale缩放、Shear切变/错切、Rotate旋转（默认绕原点、逆时针）
* Linear Transforms = Matrices (of the same dimension)
  * 缩放、切变、旋转都可以写作线性形式
    $$ \left\{ \begin{aligned} x' & = & ax + by \\ y' & = & cx + dy  \end{aligned} \right. $$
  * 用矩阵来表示则是
    $$ \left( \begin{matrix} x' \\ y' \end{matrix} \right)
        = \left( \begin{matrix} a & b \\ c & d  \end{matrix} \right)
        \cdot \left( \begin{matrix} x \\ y \end{matrix} \right) = M \cdot \left( \begin{matrix} x \\ y \end{matrix} \right) , M为变换矩阵 $$

## Homogeneous Coordinates齐次坐标
* 引入齐次坐标的原因：平移变换
    $$ \left\{ \begin{aligned} x' & = & x + t_x \\ y' & = & y + t_y  \end{aligned} \right. $$
  * 用上述的表示，还需加上一列常数列向量，该平移变换不属于线性变换，为`仿射变换Affine Transformations`
  * 所以为了将平移变换统一，增加一维
* Add a third coordinate ($\overrightarrow{w} coordinate$)
  * 2D point = （$x, y,$ `1`$）^T$
  * 2D vector = （$x, y,$ `0`$）^T$
  * 于是平移可以表示为
    $$ \left( \begin{matrix} x' \\ y' \end{matrix} \right) = \left( \begin{matrix} 1 & 0 & t_x \\ 0 & 1 & t_y \\ 0 & 0 & 1 \end{matrix} \right) \cdot \left( \begin{matrix} x \\ y \\ 1 \end{matrix} \right) = \left( \begin{matrix} x+t_x \\ y+t_y \\ 1 \end{matrix} \right) $$
* 区分点、向量的原因：  
  * ① 向量具有平移不变性，增加的一维为0时平移前后相同  
  * ② 从几何意义来看，$point=1$，$vector=0$  
  &nbsp;&nbsp;&nbsp;&nbsp; $vector(0) + vector(0) = vector(0)$  
  &nbsp;&nbsp;&nbsp;&nbsp; $point(1) - point(1) = vector(0)$  
  &nbsp;&nbsp;&nbsp;&nbsp; $point(1) + vector(0) = point(1)$  
  &nbsp;&nbsp;&nbsp;&nbsp; $point(1) + point(1) = ？$  
  * 在齐次坐标下，对 $\overrightarrow{w} > 1$ 进行定义
    $$
        \left( \begin{matrix} x \\ y \\ w \end{matrix} \right)
        \ is \ \ the \ \ 2D \ \ point \ 
        \left( \begin{matrix} x/w \\ y/w \\ 1 \end{matrix} \right) \ , \ w \neq 0
    $$
  * `所以几何意义中的` $point + point = 中点$
* 因此将仿射变换 $Affine map = linear map + translation$
    $$
        \left( \begin{matrix} x' \\ y' \end{matrix} \right)
        = \left( \begin{matrix} a & b \\ c & d \end{matrix} \right)
        \cdot \left( \begin{matrix} x \\ y \end{matrix} \right)
        + \left( \begin{matrix} t_x \\ t_y \end{matrix} \right)
    $$
    统一转为线性变换
    $$
        \left( \begin{matrix} x' \\ y' \\ 1 \end{matrix} \right)
        = \left( \begin{matrix} a & b & tx \\ c & d & ty \\ 0 & 0 & 1 \end{matrix} \right)
        \cdot \left( \begin{matrix} x \\ y \\ 1 \end{matrix} \right)
    $$
* 二维变换的齐次形式
  * Scale缩放
    $$ S(S_x, S_y) = \left( \begin{matrix} S_x & 0 & 0 \\ 0 & S_y & 0 \\ 0 & 0 & 1 \end{matrix} \right) $$
  * Rotation旋转
    $$ R(\alpha) = \left( \begin{matrix} \cos\alpha & -\sin\alpha & 0 \\ \sin\alpha & \cos\alpha & 0 \\ 0 & 0 & 1\end{matrix} \right) $$
  * Translation平移
    $$ T(t_x, t_y) = \left( \begin{matrix}
        1 & 0 & t_x \\ 0 & 1 & t_y \\ 0 & 0 & 1
    \end{matrix} \right)$$
* 齐次形式的代价：扩充维度
* 注意：当表示二维情况下的仿射变换时，最后一行才都是 $(0, 0, 1)$

## Inverse Transform逆变换

## Composite Transform复合变换
* 复合变换可由简单变换组成
* 变换顺序与矩阵乘法一样不可交换
* 计算：`对原始列向量，从右到左乘上各变换矩阵`
  * 使用结合律将各变换矩阵先相乘，则从 $A_n \cdot A_{n-1} \cdot ... \cdot A_1 = M_{3\times3}$ 最终得到一个 $3\times3$ 的变换矩阵
* 变换分解
  * 若绕任意点 $C$ 进行旋转，步骤：① 整体平移回原点 ② 旋转 ③ $C$ 点平移回原处
  * 即（从右到左叠加）
    $$ T(c) \cdot R(\alpha) \cdot T(-c) $$

## 3D Transforms三维变换 I
* 基本的部分简单从二维扩充即可
* 注意：齐次形式的变换矩阵，因为是由仿射变换而来，所以一定是先线性（左上角）再平移（右上角），这种顺序的二者可以直接写在一起。

# Lecture 04 Transformation Cont.
## 3D Transforms三维变换 II
* 3D Rotation
  * 绕 $y$ 轴比较特殊
  * $x, y, z, x, y, z ...$ 循环不变性。
* 三维空间中的任意旋转
  * 可分解为绕三个轴的三次旋转
    $$ R_{xyz}(\alpha, \beta, \gamma) = R_x(\alpha) \cdot R_y(\beta) \cdot R_z(\gamma) $$
  * 其中，$\alpha、\beta、\gamma$ 被称为`欧拉角`
  * `Rodrigues' Rotation Formula罗德里格斯旋转公式`：定义了默认旋转轴（过原点），扩展到绕任意轴则叠加两次平移即可。
* 四元数：处理旋转与旋转之间的插值。如2D情况下旋转25度、旋转15度，不能简单相加取均值（20度）得到中间情况。

## Viewing Transformation
* 以拍照过程作为例子
  拍照阶段 | 对应变换
  :------:|:-------:
  要拍的事物定好位置|Model Transformation
  调整相机位置、角度|View Transformation
  拍摄|Projection Transformation
  * 三种变换简称MVP变换。（Not Most valuable player XD）

### View/Camera Transformation视图变换
* Step
  * 定义相机的`位置Position` $\overrightarrow{e}$。
  * 定义相机的`朝向Loot-at/gaze direction` $\hat{g}$。
  * 定义相机的`头顶Up direction` $\hat{t}$。
* 约定标准状态：相机总在原点 $(0, 0, 0)$ ，头顶沿 $\overrightarrow{Y}$ 轴正向，并看向 $-\overrightarrow{Z}$ 轴。
* 将定义的三个量，通过变换 $M_{view}$ 转化到标准状态。
  * 首先将 $\overrightarrow{e}$ 平移到原点
    $$ T_{view} = \left( \begin{matrix} 1 & 0 & 0 & -x_e \\ 0 & 1 & 0 & -y_e \\ 0 & 0 & 1 & -z_e \\ 0 & 0 & 0 & 1 \end{matrix} \right) $$
  * 然后将 $\hat{g}、\hat{t}、(\hat{g}\times\hat{t})$ 分别旋转对应到 $-\overrightarrow{Z}、\overrightarrow{Y}、\overrightarrow{X}$ 。
  * 由于统一写在一个变换矩阵中时，是先做线性变换再做平移变换的，而此处显然要先平移，因此可得：
    $$ M_{view} = R_{view} \cdot T_{view} $$
  * 求解 $R_{view}$ 时，将任意轴旋转到 $\overrightarrow{X}、\overrightarrow{Y}、\overrightarrow{Z}$ 不方便处理。而旋转矩阵是正交的，其转置就是它的逆，所以可以反向考虑：将 $-\overrightarrow{Z}、\overrightarrow{Y}、\overrightarrow{X}$ 分别旋转到 $\hat{g}、\hat{t}、(\hat{g}\times\hat{t})$ 。
    $$ R_{view}^{-1} = \left( \begin{matrix}
        x_{\hat{g}\times\hat{t}} & x_t & x_{-g} & 0 \\
        y_{\hat{g}\times\hat{t}} & y_t & y_{-g} & 0 \\
        z_{\hat{g}\times\hat{t}} & z_t & z_{-g} & 0 \\
        0 & 0 & 0 & 1\end{matrix} \right) $$
  * 转置得到 $R_{view}$
    $$ R_{view} = \left( \begin{matrix}
        x_{\hat{g}\times\hat{t}} & y_{\hat{g}\times\hat{t}} & z_{\hat{g}\times\hat{t}} & 0 \\
        x_t & y_t & z_t & 0 \\
        x_{-g} & y_{-g} & z_{-g} & 0 \\
        0 & 0 & 0 & 1 \end{matrix} \right) $$
* 相机根据 $M_{view}$ 变换后，根据相对运动，其它物体也统一作一次该变换。【？这样看到的东西不就一直不变了吗orz?】
  * MV变换都应用到物体，经常放在一起，称模型视图变换。

### Projection Transformation投影变换
* Orthographic projection正交投影
  * 常用于工程制图，可看作是透视投影的相机处于无限远。
  * 简单理解：  
    ① 相机变换成标准态。  
    ② Drop $\overrightarrow{Z} coordinate$ 。  
    ③ 将所得的平面图像平移并缩放（translate and scale）到 $[-1,1]^2$ 矩形范围，便于后续处理。
  * 实际操作；  
    ① 定义物体在三个坐标方向上的坐标范围 $[l,r]\times[b,t]\times[f,n]$ （左右/下上/远近）。（由于默认看向 $-\overrightarrow{Z}$ 方向，因此 $f<n$。OpenGL使用的左手系坐标则相反）  
    ② 物体中心平移到原点。  
    即将每个方向的中点移动到坐标轴上，以 $\overrightarrow{X}$ 轴为例，有：  
    $$ P_{\overrightarrow{X}方向中点} =  \frac{r+l}{2}$$  
    移动到坐标轴上即 $t_x = -\frac{r+l}{2}$  。  
    ③ 三个方向上的宽度都缩放到 $2$ ，即 $[-1,1]^3$ 的cuboid长方体范围。  
    考虑缩放前后，以 $\overrightarrow{X}$ 轴为例，有：  
    $$ L_x^{'} = k_x \cdot L_x $$  
    其中， $L_x^{'} = 2$ ， $L_x = r-l$ 。  
    所以 $k_x = \frac{2}{r-l}$ 。  
    结合三个方向上的平移和缩放，得到`正交投影的变换矩阵`：  
    $$ M_{ortho} = \left( \begin{matrix} \frac{2}{r-l} & 0 & 0 & 0 \\ 0 & \frac{2}{t-b} & 0 & 0 \\ 0 & 0 & \frac{2}{n-f} & 0 \\ 0 & 0 & 0 & 1 \end{matrix} \right) \cdot \left( \begin{matrix} 1 & 0 & 0 & -\frac{r+l}{2} \\ 0 & 1 & 0 & -\frac{t+b}{2} \\ 0 & 0 & 1 & -\frac{n+f}{2} \\ 0 & 0 & 0 & 1 \end{matrix} \right) $$  
    `注：`暂未考虑旋转。此时物体经过拉伸变形，但之后还会进行视口变换，再次拉伸。
* Perspective projection透视投影
  * 平行线会相交，近大远小的视觉效果。人眼的成像是透视投影，以眼睛（或相机）为点，连出一个四棱锥，从四棱锥的一个深度到另一深度称为frostum。透视投影就是将frostum这块区域的所有东西显示出来，投影到相机近处的平面上。
  * 操作分解：  
    ① $frustum \stackrel{squish}{\Longrightarrow} cuboid$。先把四棱锥“挤压”成长方体（压进近平面的视野范围）。显然，近平面上所有点固定不动，远平面上所有点 $z$ 值不变，且棱锥的轴心线上所有点固定不动。
    1. 考虑棱锥侧面投影的上半部分是一个三角形，在近平面处分割得到一个小三角形。易得两个三角形相似。设近平面最高点 $(x',y',z'=n)$ ，需挤压的面最高点 $(x,y,z)$ 。  </br> &nbsp;  ![](/note&#32;-&#32;image/GAMES101/img1-persp.png)  &nbsp;</br> 可得 $y'=\frac{n}{z}y$，同理观察棱锥俯视图可得 $x'=\frac{n}{z}x$。  
    2. 用齐次坐标表示：  
        $$ \left( \begin{matrix}x \\ y \\ z \\ 1\end{matrix} \right) \stackrel{squish}{\Longrightarrow} \left( \begin{matrix} \frac{n}{z}x \\ \frac{n}{z}y \\ unknown \\ 1 \end{matrix} \right) \stackrel{\times z}{\longrightarrow} \left( \begin{matrix} nx \\ ny \\ unknown2 \\ z \end{matrix} \right) $$
    3. 此时整理即有  
        $$ M_{presp->ortho}^{(4\times4)} \cdot \left( \begin{matrix} x \\ y \\ z \\ 1 \end{matrix} \right) = \left( \begin{matrix} nx \\ ny \\ unknown2 \\ z \end{matrix} \right) $$
    4. 逆推一下易得
        $$ M_{persp->ortho} = \left( \begin{matrix}n&0&0&0\\0&n&0&0\\?&?&?&?\\0&0&1&0\end{matrix} \right) $$
    5. 回到初始设定：近平面与远平面上点 $z$ 值不变。
    6. 取近平面上点以齐次形式表示并 $\times z=n$ 向上述整理后等式右部形式靠拢。
       $$ \left( \begin{matrix} x\\y\\n\\1 \end{matrix} \right)\stackrel{\times z=n}{\longrightarrow}\left( \begin{matrix} nx\\ny\\n^2\\n \end{matrix} \right)，说明\ (?\ ?\ ?\ ?)\cdot \left(\begin{matrix}x\\y\\n\\1\end{matrix}\right)=n^2 $$
       此时，显然可知第三行至少应为 $(0\ 0\ A\ B)$ 。  
       得到 $An+B=n^2$。  
       同理取远平面上点，可得 $Af+B=f^2$。  
       两式联立，解二元一次方程组得
       $$ \left\{ \begin{aligned}
           A & = n+f \\ B & = -nf \end{aligned}\right. $$
    7. 最后得到透视投影转化为正交投影的变换矩阵
       $$ M_{persp->ortho} = \left( \begin{matrix}n&0&0&0\\0&n&0&0\\0&0&n+f&-nf\\0&0&1&0\end{matrix} \right) $$
    ② 转化成长方体后，就转化为正交投影问题，因此透视投影变换矩阵
    $$ M_{persp}=M_{ortho}\cdot M_{persp->ortho} $$
  * 问题：除了近平面与远平面，中间的平面被挤压后 $z$ 值趋向近平面还是趋向远平面？
    * 盲猜趋向远平面！
    * 

# Lecture 05 Rasterization 1 (Triangles)
## 定义视锥frostum
* Step
  * 定义`近平面的宽高比` $Aspect\ Ratio = \frac{width}{height}$。
  * 定义`垂直可视角度` $Vertical\ Field\ of\ View（fovY）$：视点到近平面上下沿的两条连线夹角。
  * 回到棱锥侧面图  
    
    &nbsp;![](note&#32;-&#32;image/GAMES101/img2-fov.png)
    
  * 看图说话即有
    $$ \tan\frac{fovY}{2}=\frac{t}{|n|} $$
  * 近平面的中心即视角中心，根据定义即有
    $$ aspect=\frac{r}{t} $$
  * 所以定义宽高比和垂直可视角就能推及 $r、t、n$ 三个坐标方向。

## Canonical Cube to Screen
* after MVP（Model/View/Projection），把变换所得 $[-1,1]^3$ 呈现到画面。
* 定义屏幕Screen
  * 图形学中定义：元素是像素的二维数组
  * raster：德语中的screen，rasterize：画到屏幕上
  * pixel（"picture element"的缩写）：暂时抽象为纯色小方块，RGB三值表示。
* 定义屏幕空间  

  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![](note&#32;-&#32;image/GAMES101/img3-screen.png)
  * 像素以 $(x, y)$ 表示， $x, y$ 均为整数
  * 像素表示范围 $(0, 0)$ 到 $(width-1, height-1)$
  * 像素 $(x, y)$ 的中心为 $(x+0.5, y+0.5)$
  * 屏幕覆盖范围 $(0, 0)$（左下角） 到 $(width, height)$（右上角）
* 把 $xy$ 面的 $[-1,1]\times[-1,1]$ 变换到 $[0, width]\times[0, height]$
  * 暂时忽略 $z$ 坐标
  * 作视口变换 $M_{viewport}$ ：把 $2$ 分别拉伸到 $width、height$ 。
    $$ M_{vireport}=\left(\begin{matrix}\frac{width}{2} & 0&0&\frac{width}{2}\\0&\frac{height}{2}&0&\frac{height}{2}\\0&0&1&0\\0&0&0&1\end{matrix}\right) $$
    注意左下角之前在 $[-1, 1]$ ，拉伸后在 $[-\frac{width}{2}, \frac{height}{2}]$ ，所以还要把左下角平移到原点。
* 至此，变换完成，得到点在屏幕空间下的坐标。

## 光栅化
* 接下来将模型等拆成像素显示到屏幕，即光栅化过程。
* 光栅显示设备
  * 示波器
  * 阴极射线管CRT：控制电子击中位置。隔行扫描法，一帧画奇数行，下一帧画偶数行，视觉滞留效应。但对高速运动画面会有撕裂现象。
  * 当代显示器：将显存中的一块区域，映射到屏幕上。
  * 视网膜屏幕：分辨率超过人眼视网膜的分辨率。
  * 液晶显示器Liquid Crystal Display（LCD）：利用液晶的原理控制显示器的显示内容。它会通过自己的排布影响光的极化。光通过光栅，会筛选掉与光栅震动方向不同的那部分光的能量。液晶可以通过自己本身的震动来影响光的波动。
  * 发光二极管Light Emitting Diode（LED）
  * 墨水屏：刷新慢

## **Drawing to Raster Displays**
* 三角形Triangles - Fundamental Shape Primitives
  * 三角形为最基础的多边形，任何其它不同的多边形都可以拆成三角形。
  * 任意给定三点连成`三角形`，`一定是平面`图形。
  * 三角形的`内部外部定义明确`。
  * 定义三角形的三个顶点的不同属性，可以在三角形内部做插值渐变。
* 问题：三角形的边穿过像素格子时，部分被覆盖。因此要判定像素是否在三角形内。
* 简单做法：Sampling采样
  * 对一个连续函数，取点求值，离散化。
  * 此处采样：利用像素中心对屏幕空间进行采样。（看定义在屏幕空间上的函数，在不同的像素中心，其值为多少。）
* Sample if each pixel center is inside triangle
  * 定义函数 `inside(t, x, y)`：给出三角形和屏幕上点坐标（可以非整数），判断点是否在三角形内。
    $$ inside(t,\ x,\ y) = \left\{ \begin{array}{rcl}
      1 &  & point (x, y)\ in\ triangle\ t \\
      0 &  & otherwise
    \end{array} \right.$$
  * 再遍历屏幕空间，check每个像素是否inside。
  * 判断方法：按顺序与三顶点形成的向量作叉积，三正三负在其内。
    * `corner case`：本课程当“像素中点”在三角形边上时，看自己心情。
  * 优化：画一个三角形时不用遍历整个屏幕空间，遍历包围盒内的像素。
    * AABB包围盒：取各坐标方向上最小值到最大值之间的所有像素点。
* 真实的LCD屏幕像素  
  &nbsp;&nbsp;![](note&#32;-&#32;image/GAMES101/img4-realpix.png)
  
  * 三星屏幕的像素RGB形成的图案：bayer pattern，这种分布方法能使RGB均匀分布在屏幕上。绿色的数量最多，因为人眼对绿色敏感度最高。相机中的感光元件也有这样的应用。
  * 彩色打印机上的RGB分布更迷幻。减色系统：加的颜色越多，越黑。
* 以像素中心采样，会产生锯齿Jaggies，造成走样Aliasing现象。

# Lecture 06 Rasterization 2 (Antialiasing and Z-Buffering)
## Antialiasing
### **采样理论Sample theory**
* Sampling is ubiquitous in CG. 采样在CG中无处不在
  * 动画是对时间的采样
  * 采样产生的问题也是无处不在的
* Sampling Artifacts (Errors/Mistakes/Inaccuracies) in CG.
  * 锯齿Jaggies、摩尔纹Moire Patterns（去掉奇数行奇数列的情况）、Wagon Wheel Illusion(False Motion)逆转的轮子（人眼在时间上的采样跟不上轮子运动的速度）……
  * 产生问题的原因：Signals are changing too fast (high frequency), but sampled too slowly. 信号/函数的变化太快，采样速度跟不上。
* Antialiasing Idea: Blurring (Pre-Filtering) Before Sampling
  * 在采样前，先做模糊/滤波。
  * 如上述三角形，对像素中心采样之前，先把原来的三角形变“模糊”：边缘处变成略淡的颜色。这样采样采到边界的点颜色冲突就不那么明显。
  * 先采样再模糊：Blurred Aliasing。把走样模糊了，但是达不到反走样的效果。

### **原理分析**
* 频率和周期：如$cos(2f\pi)$，$T = \frac{1}{f}$
  * 傅立叶级数展开Fourier Transform：任何一个周期函数，都可以把它分解成不同的频率（写成一系列正弦和余弦函数的线性组合），以及一个常数项。（通过上下平移、叠加不同频率的正余弦函数，逼近周期函数）
  * 傅立叶变换：将一个函数可逆变换成另一个。 </br> &nbsp;![](note&#32;-&#32;image/GAMES101/img5-fourier.png) &nbsp;
  * 用相同的速度采样周期函数，频率越高，采样结果偏差越大。 </br> &nbsp;![](note&#32;-&#32;image/GAMES101/img6-sampling.png) &nbsp;
  * 用相同的速度采样两个截然不同的函数，可能得到完全相同的结果。 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img7-aliasing.png) &nbsp;
    $\uparrow$ 走样的定义。
* 滤波Filtering：过滤掉某些频率，看信号的变化。
  * 傅立叶变换的作用：把函数从时域（时空域？横轴时间纵轴信号值）变到频域（横轴频率纵轴振幅）。展现信号在不同的频率的表现。
    * 将一张图从时域变换到频域。 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img8-domain.png) &nbsp; 
    * 所得频域图中央为低频信号，外围为高频信号。
    * 中间的信号比较密集：大部分自然图片都是低频信息比较多。
    * 水平竖直的两条穿图线：分析信号时，会认为它是周期性重复的。而图片本身不具有这样的性质，因此会作重复平铺后处理。而图片的左右、上下边界相差很大，平铺到一起时会发生剧烈的信号变化，产生极高的高频信号。所以出现这两条线。
  * 用滤波把频域中显示出的大部分低频信号过滤掉，对过滤掉以后的信号作逆傅立叶变换，可以看出高频信号在原图上的意义。 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img9-high.png) &nbsp;
    如图，高频信号在原图上即图片内容的边界。  
    此为高通滤波High-pass filter：只有高频信号可以通过。
  * 再尝试过滤高频信号，低通滤波Low-pass filter。 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img10-low.png) &nbsp;
    此时图像的边界处都模糊了。  
    对比原图手上拿的卷子（？）可以发现，除了边界模糊以外，还出现了一些奇怪纹路。是因为这种低通滤波不完美，有缺陷，此处先忽略。
  * 选取高低频率中间的某一段频率，又可以提取非边界的隐约轮廓等。
* 滤波Filter = 卷积Convolution (= 均值Averaging)
  * 图形学上简化的卷积Convolution定义：对某种信号，用滤波器窗口，对应作点积（实质为取周围值的均值），生成新的信号。 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img10-low.png) &nbsp;
  * 卷积定理Convolution Theorem：时域卷积 $=$ 频域乘积，时域乘积 $=$ 频域卷积。
    * 所以要将一张图卷积某滤波器，只要先傅立叶变换到频域图，作乘积，再对结果作逆傅立叶变换。
  * Box Filter </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img12-box.png) &nbsp;
    卷积盒越大，产生的图片越模糊（各处颜色都接近），频域图越小。  
    卷积盒越小，越接近于原图（比如小于像素就相当于没有卷积）。
* 从频率的角度看采样
  * 采样可以看成：用冲激函数与一段连续函数（信号）相乘，将其离散化成点。
    * 冲激函数：在时域上看，只在特定处有无穷大能量。
    * 冲激函数的筛选性质：若信号 $x(t)$ 是在 $t=t_0$ 处连续的普通函数。则该信号与冲激函数相乘，筛选出连续时间信号 $x(t)$ 在 $t=t_0$ 时的函数值 $x(t_0)$ 。可以理解为冲激函数在该时刻对函数 $x(t)$ 的一瞬间作用，值为冲激函数和 $x(t_0)$ 乘积，瞬间趋向无穷大。
    * 冲激函数的取样性质：一个连续时间信号 $x(t)$ 与冲激函数相乘，并在时间域 $(-\infin,+\infin)$ 上积分，其结果为信号 $x(t)$ 在 $t=t_0$ 时的函数值 $x(t_0)$ 。可以理解为冲激函数作用于 $x(t)$ ，结果瞬间趋向无穷大，又趋于稳态时最终作用的结果是 $x(t_0)$ 。
  * 冲激函数傅立叶变换到频域上变成另一种冲激函数。
  * 根据卷积定理，时域相乘，在频域上就是卷积。而信号与冲激函数在频域上的卷积结果是：信号的频谱在频域上被“复制粘贴”。 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img13-sampling.png) &nbsp;
  * 并且，在时域上的采样速度越慢（采样点距离越大），对应到频域上，信号的频谱被“复制粘贴”的间隔就越小。 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img14-fmixed.png) &nbsp;  
    可以看出，造成信号频谱发生重叠，导致走样。
* 如何降低走样问题
  * 增加采样率：终极法2333。但受到屏幕的物理限制，分辨率不是你想加想加就能加qvq。
  * 反走样：先模糊再采样。即先用低通滤波消除高频信号，让频谱边界的混叠情况好转。 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img15.png) &nbsp;
  * 【？】那么，为什么先采样再模糊就不行呢：频域上频谱重叠后再去掉部分频率，重叠部分仍然重叠。
* 如何模糊
  * 取一个像素的低通滤波器。
  * 将函数与该滤波器卷积（求均值），再对像素中心采样。
    * 任意一个像素，对其内部被覆盖的区域求平均。
    * 但这样做比较困难。
  * 所以使用一种近似方法：MultiSampling Antialiasing（MSAA）
    * 在一个像素内部再多加采样点，比如把一个像素看成它内部有 $4\times4$ 个采样点，采样完对和做均值。
    * 这个方法近似的是模糊过程，当然由于求出均值，所以采样也直接使用了这个值。
    * 显然，MSAA增加了计算量。不过在工业界，为提升效率，会通过复用采样点等方法使计算量不像理论上那么膨胀。
    * 其它的抗锯齿方法：Fast Approximate AA（FXAA，在图像层面：先得出锯齿图，找到边界，换成没有锯齿的图）、Temporal AA（TAA，复用上一帧的采样点，不同时间帧时，对同一像素内的采样点位置不同。即将MSAA多加的采样点分布到不同时间帧上。）
* 超分辨率Super resolution
  * 将 $512\times512$ 的图拉伸到 $1k\times1k$ 而产生锯齿。
  * 与走样类似，都是要解决样本不足的问题。
  * 方法：DLSS（Deep Learning Super Sampling）深度学习。

## 可见性Visibility/遮挡occlusion（in Lecture 07）
* 当有多个物体重叠在一起时，要显示较近的物体。
* 画家算法Painter's Algorithm（指油画家）
  * 从远到近层层覆盖。
  * 定义观测点到物体的距离，即深度。但深度的定义有时比较困难。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img16.png)  &nbsp;</br></br>
  * 复杂度分析：时间复杂度 $O(nlogn)$ ，主要为排序时间。
* Z-Buffer
  * 对物体远近排序比较困难，所以针对像素解决。
  * 思想
    * 记录像素离视点的最近距离
    * 同时生成：  
      ① frame buffer stores color values 最终渲染结果图  
      ② depth buffer (z-buffer) stores depth 任意像素对应深度图（该深度在渲染过程中，不断更新为覆盖到这个像素的物体，在这个像素点上离视点的距离，最近的那个）
  * 注意
    * 此处为了便于理解，认为 $z$ 为正。（实际上视点仍在观测 $-\overrightarrow{Z}$）
    * 对单个像素内进行多次采样的时候，对采样点做深度缓存。
    * 深度相同时的处理本课程不讨论。
    * 无法处理透明物体。
  * 深度图 </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img17.png) &nbsp;</br>
    离视点越近的像素深度越小，反应到色值上颜色越黑。
  * 复杂度分析： $O(n)$

# Lecture 07 Shading 1 (Illumination, Shading and Graphics Pipeline)
## 着色Shading

### **概念**
* 着色：对不同的物体应用不同材质的过程。
* 高光specular highlights、漫反射Diffuse reflection、间接（环境）光照Ambient lighting
* 定义着色点 $Shading\ point\ p$（极小范围认为是平面，存在法向 $\overrightarrow{n}$ ）、观察方向 $Viewer\ direction\ \overrightarrow{v}$ 、光照方向 $Light\ direction\ \overrightarrow{l} = p_光 - p$ 、物体表面参数 $Surface\ parameters（color、shininess...）$ </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img18.png) &nbsp;</br>
  * 都指单位向量。
* Shading is local. 只关注局部，不考虑其它物体的存在。即如果有物体遮挡了光，应该产生阴影，暂时先不考虑。

### **A Simple Shading Model - Blinn-Phong Reflectance Model**
* 漫反射Diffuse Reflection：光线击中物体表面某点时，均匀反射到各个不同方向。
  * 相同的表面，当入射光的入射角度不同时，产生不同的明暗效果。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img19.png) &nbsp;</br>  
    由图可知，设平行光，关注单个shading point时，只考虑它附近单位面积的表面，显然表面倾斜时接收到的光就少。  
    从能量的角度，通过明暗可以感知光的能量的多少。  
    而类似地球的四季变化，可知接受到的能量与入射光和该点法向的夹角有关。
  * 朗伯余弦定律 $Lambert's\ cosine\ law$ ：接收到的能量，和光线方向及法向夹角的余弦 $cos\theta = \overrightarrow{l} \cdot \overrightarrow{n}$ 成正比。  </br>&nbsp;![](img) &nbsp;</br>  
  * 光能来源
    * 假设一个点光源，认为它时刻在往周围的球壳发光。再假设真空中传播没有能量损失，考虑能量守恒，随着时间的推移，某时刻所发的光向外扩散，能量总量不变，辐射面积变大。
    * 此处暂时先定义到光源单位距离的球壳上光强 $I$ ，传播到距离为 $r$ 的球壳上。  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img21.png) &nbsp;</br>
      总能量应为 $I \cdot \pi \cdot 1^2 = I_r \cdot \pi \cdot r^2$  
      所以 $I_r = \frac{I}{r^2}$  
      说明：考虑单位面积所能接收到的能量，与光线传播的距离的平方成反比。
  * Lambertian Diffuse Shading
    * $L_d = k_d \cdot (\frac{I}{r^2} \cdot max（0, \overrightarrow{n}\cdot\overrightarrow{l}）$
    * 其中，  
      ① $L_d$ ：漫反射光强  
      ② $k_d$ diffuse coefficient：漫反射的出射能量占入射能量的比例。人看到某点的颜色，是因为该点会吸收一部分光，从而产生颜色。当完全吸收时就是黑色，按常识理解即可。所以将该系数定义为三通道的RGB值，分别为 $[0,1]$ ，就能产生一种颜色。比如说映射到 $[0,255]$ 。  
      ③ $\frac{I}{r^2}$ ：到达着色点处的能量  
      ④ $max（0, \overrightarrow{n}\cdot\overrightarrow{l}）$ ：着色点处接收到的能量。点积与 $0$ 取大是因为点乘为负时是从背面来的光，对结果没有贡献。
    * 即 $漫反射的出射能量=漫反射的出射能量占入射能量比例\times入射能量=比例\times到达的能量\times接收的能量$
    * 由于漫反射均匀反射到各方向，因此漫反射的结果与观察方向无关。
    * 概念辨析  
      查Diffuse Coefficient的时候注意到的一点。  
      ① $Albedo$ ：光的出射能量占入射能量的比例。  
      ② $Diffuse Coefficient$ ：光的漫反射的出射能量占入射能量的比例。  
      光击中物体的时候还会有折射光等，这里只涉及漫反射。
* 高光项Specular Term：理想光滑平面上是镜面反射，而比较光滑但又不接近理想的光滑平面，反射光的方向应在镜面反射光的附近。当观察方向接近这些反射光的时候，能观察到高光。  （in Lecture 08）
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img22.png) &nbsp;</br>

  * 定义入射光与观察方向的半程向量 
    $$h\ =\ bisector（\overrightarrow{v}, \overrightarrow{l}） = \frac{\overrightarrow{v}+\overrightarrow{l}}{|\overrightarrow{v}+\overrightarrow{l}|}$$
    而入射光与反射光的半程向量是法向 $\overrightarrow{n}$ ，所以反射光与观察方向的邻近可以近似用它们与入射光的半程向量的邻近替换。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img23.png) &nbsp;</br>  
    类似漫反射，得到高光反射光
    $$\begin{aligned}
       L_s &=& k_s \cdot \frac{I}{r^2} \cdot max（0,\ cos\alpha）^p \\
           &=& k_s \cdot \frac{I}{r^2} \cdot max（0, \overrightarrow{n}\cdot \overrightarrow{h}）^p
    \end{aligned}$$
      * 与漫反射相比，增加了观察方向的影响。【？为什么用 $\cos\alpha$ ：陷入茫然-1s，但是想想：一与夹角相关，二随夹角增大而减小，又方便好算的可不就是余弦么=。=】
      * 指数 $p$ ：单纯的余弦函数变化趋势对高光来说还是过于平缓，所以要加快它的变化趋势。乘上系数的话还是很慢，就用指数。一般在Blinn-Phong模型下用 $p = 100-200$ 。</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img24.png) &nbsp;</br> 随着指数的变化，看到的高光范围变小。  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img25.png) &nbsp;</br>
      * 此处不考虑吸收的能量是在该模型下被简化了。
      * 不使用半程向量作近似，直接考虑理想镜面反射光与观察方向的夹角，就是 Phong模型，与这种近似相比，计算量较大。
* 环境光照项Ambient Term
  * 大胆假设！所有点接收到的环境光都相同，强度为 $I_a$。
  * 大胆近似！得到环境光 $L_a=k_a \cdot I_a$
    * 与直接光照、观察方向、法线方向都无关。
    * 具体表现就是点本身的颜色。
    * 环境光的作用：保证没有地方全黑。
  * 小心求真：参见全局光照技术。
* Blinn-Phong Reflection Model = Diffuse + Specular + Ambient
  $$ \begin{aligned} L &= L_d + L_s + L_a \\ &= k_d \cdot \frac{I}{r^2} \cdot max（0,\ \overrightarrow{n} \cdot \overrightarrow{l}）+\ k_x \cdot \frac{I}{r^2} \cdot max（0, \ \overrightarrow{n} \cdot \overrightarrow{h}）^p \ +\ k_a \cdot I_a \end{aligned} $$
* 巨巨们的Q Time
  * Q：为什么不考虑观察点到着色点的距离对能量损耗的影响？
    * A：实际上计算得出的东西不再是光的能量，而是Radiance。而它具有和距离无关的特性。现实中离得远觉得暗是其它原因造成的。

# Lecture 08 Shading 2 (Shading, Pipeline and Texture Mapping)
## 着色Shading

### **着色频率Shading Frequencies**
* 对四边形着色 $\rightarrow$ 对四边形的顶点也着色 $+$ 插值 $\rightarrow$ 对每个像素着色</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img26.png) &nbsp;</br>
* 不同的着色频率
  * 逐三角形Shade each triangle （平面着色flat shading）：三角形为平面，两条边作叉积可得单一法向，然后根据光照等进行计算。  
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img27.png) &nbsp;</br>  

  * 逐顶点Shade each vertex （双线性光强插值法Gourand shading）：求顶点法向，对顶点着色，三个顶点构成的三角形内部通过插值生成颜色。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img28.png) &nbsp;</br>
  * 逐像素Shade each pixel （Phong Shading）：三角形的三个顶点求出各自的法线，在三角形内部每个像素上插值出其自己的法向，再对每个像素进行着色。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img29.png) &nbsp;</br>
  * 一般情况下 Phong Shading 的表现较好。</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img30.png) &nbsp;</br>
    * 具体的效果和效率要看定义的几何体上三角形、顶点、像素个数为多少。  
    * 当几何体本身定义复杂，表面上三角形个数极多，平面着色的效果也不错。
    * 如果表面三角形个数比像素数量还多，平面着色的效率也可能比 Phong Shading 低。
    * 求解顶点法向：对顶点所关联的面的法向作加权（面积）平均。
    * 求解像素法向：重心插值（参见下文）。

## 图形管线Graphics （Real-time Rendering） Pipeline 
![](note&#32;-&#32;image/GAMES101/img31.png)
* 实时渲染管线：输入三维空间中的顶点，经过变换（MVPV）投影到屏幕空间，这些顶点在屏幕上形成三角形，通过光栅化（采样、深度测试）把三角形离散化成像素点，结合光照、材质和观察方向等进行着色，输出。
  * 该流程已固化入GPU，有些设定允许其中一部分为可编程。
  * 决定顶点和像素如何处理的代码即Shader。
* Shader Programs
  * Shader只需考虑如何处理单个着色点。
  * Shader类别：顶点着色器Vertex Shader（对顶点的操作）、片段/像素着色器Fragment/Pixel Shader（对像素的操作）
  * 若对像素操作，主要求出最后的颜色，并输出。
  * GLSL，OpenGL的一种语言。
  * `Shadertoy`：http://shadertoy.com/view/ld3Gz2

## 现代图形学发展
* Geometry Shader几何着色器：可以定义几何的操作。
* Compute Shader：可以做任何形式的通用计算，General Purpose GPU。

## 纹理映射Texture Mapping
* 纹理：用以定义着色点的属性。
  * 三维物体的表面是二维的，即可以映射到一张图。
  * 着色点和纹理点的对应：把模型展开贴到纹理的对应位置（美工的开发任务），在展开时保证大小不扭曲、不产生间隙（几何研究 parameterization参数化）
* 定义纹理上的坐标系 $(u,v)$
  * 约定： $u,\ v \in [0,1]$
* Tilable纹理：应用到瓷砖上可以平铺时自然衔接的纹理。
  * 这种纹理的设计需要各种算法，如“Wang Tile”。


# Lecture 09 Shading 3 (Texture Mapping Cont.)
## Interpolation Across Triangles: 重心坐标Barycentric Coordinates
* 三角形的三个顶点各自拥有不同的属性，插值可以在三角形内部对每个点平滑地生成过渡属性。
  * 插值内容：定义在顶点上的任意属性。颜色、法线等。
* 重心坐标：定义在一个特定三角形上的坐标系统 $(\alpha,\ \beta,\ \gamma)$。
  * 三角形所形成的平面内任意一点，都可以用三个顶点坐标的线性组合表示。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img32.png) &nbsp;</br>
    $$ (x,y) = \alpha A + \beta B + \gamma C ,\\ \alpha+\beta+\gamma=1$$
  * 注意三者相加为1表示“平面内任意一点”，三者都非负即 $\alpha,\ \beta,\ \gamma \geqslant 0$表示“三角形内的点”。
  * 可以用顶点对面的三角形面积与总面积之比求出 $\alpha、\beta、\gamma$ 。
  * 重心的重心坐标 $(\frac{1}{3},\ ,\frac{1}{3},\ \frac{1}{3})$ 。
  * 任意点的重心坐标计算（但没有必要记哟[doge]）
    $$ \alpha = \frac{-(x-x_B)(y_c-y_B)+(t-t_B)(x_C-x_B)}{-(x_A-x_B)(y_C-y_B)+(y_A-y_B)(x_C-x_B)} \\ \beta = \frac{-(x-x_C)(y_A-y_C)+(y-y_C)(x_A-x_C)}{-(x_B-x_C)(y_A-y_C)+(y_B-y_C)(x_A-x_C)} \\ \gamma = 1-\alpha-\beta $$
  * 参考重心坐标，三角形内任意一点的属性也可以通过三个顶点的属性线性表示。
    $$ V=\alpha V_A+\beta V_B +\gamma V_C $$
  * 注意经过投影后重心坐标会改变，因此比如光栅化深度做插值时，要使用三维状态下的信息（逆变换回去）。

## 纹理的应用Applying Texture 1
### **基本使用**
* Simple Texture Mapping - Diffuse Color：算出屏幕上采样点的位置，所对应的插值出的 $(u,v)$ ，对应到纹理坐标上的某个颜色，来作为采样点的漫反射系数 $k_D$ 。

### **纹理放大Texture Magnification - Easy Case**
* 问题：纹理很小，映射后被拉大。即像素pixel对应到的纹理元素texel坐标非整数。
* 简单处理
  * 四舍五入取整。
  * 但附近相邻的一块都会取到相同的属性，变成一格一格的。
* 双线性插值Bilinear Interpolation
  * 取邻近四个点中两对平行方向的点分别线性插值出结果，对两个插值结果再作垂直向的线性插值。
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img33.png) &nbsp;</br>
    黑点为纹素，红点为采样点对应到的纹素坐标表示的点。
  * 通过这两个方向的线性插值，可以得到比较平滑的结果。
* Bicubic插值：取邻近的十六个，每次用四个点作立方插值。

### **纹理放大Texture Magnification - Hard Case**
* 问题直观感受图：  
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img35.png) &nbsp;</br>  
  纹理太大时，近处屏幕像素和远处屏幕像素在纹理坐标上所占区域大小不同。
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img34.png) &nbsp;</br>
  此时认为采样点代表一大块区域显然不合理。
* 简单处理
  * 类似抗锯齿时的方法，在像素点内使用超采样。  
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img36.png) &nbsp;</br>  
  一个像素内采样 $512$ 个点的结果。
  * 效果不错，但效率太低。
* 分析问题
  * 回忆走样问题的原因：采样速度跟不上信号变化的频率。在上图已经体现。所以超采样的方法可以起效。
  * 所以走样其实是由采样引起的，就可以考虑不采样，看能不能直接得到那一块区域的属性均值（范围查询问题）。
* 点查询问题和范围查询问题 Point Query vs. (Avg.) Range Query
  * 点查询问题：如线性插值。
  * 范围查询问题：如此处所需范围均值，或范围最大最小值等。（脑内弹幕爆炸刷屏：？？？线段树？？？是你吗线段树？？？）

### **Hard Case的处理1 - Mipmap**
* 作用：做快速、近似、正方形的范围查询。
* 思想
  * 预处理从纹理原图 $Level\ 0\ (a \times a)$ 生成 $Level\ 1\ (\frac{a}{2} \times \frac{a}{2})$ 的新一层次图。
  * 直到生成 $Level\ log_a\ (1 \times 1)$ 。
* 复杂度分析
  * 空间损耗为 $1+\frac{1}{4}+\frac{1}{16}+\frac{1}{64}+... = \frac{4}{3}$ ，仅为原图的 $\frac{1}{3}$ 。
* 获取屏幕像素映射到纹理坐标后，覆盖区域范围的近似
  * 取采样点周围两个像素映射到纹理坐标并与采样点映射位置相连，以两线段中最长的长度作边长 $L=max(\sqrt{(\frac{du}{dx})^2+\frac{dv}{dx}},\ \sqrt{(\frac{du}{dy})^2+(\frac{dv}{dy})^2})$ 的正方形，近似认为是采样点的覆盖范围。
  * 如果边长为 $1 \times 1$，即在Mipmap的原图上取该像素；$4 \times 4$则在第二层上取该像素。也就是在 $D = log_2 L$上取对应位置像素。
  * 当对应到非整数层时，作三线性插值Trilinear Interpolation：先在上下两层分别作双线性插值（对应非整数层时必然在这两层都不能直接取到某个纹理元素），再对两层的双线性插值结果作线性插值。
* 局限性  
  * 远处的细节过于模糊overblur。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img37.png) &nbsp;</br>  
    因为Mipmap只能近似查询正方形范围，并且三线性插值又做了多次近似。  
    而且Mipmap在缩图过程中，取得的图长宽比一直是固定的，但有些情况下可能只压缩了水平或垂直方向，而Mipmap不能获得不均匀的压缩结果。
* 对overblur的优化
  * 屏幕空间实际对应到纹理空间后，一个屏幕像素覆盖的范围可能是长条形的，此时用正方形近似取到的范围比实际要大很多。
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img38.png) &nbsp;</br>  
  * 解决方法
    * 各向异性过滤Anisotropic Filtering（也叫Ripmap）可以取到矩形范围，但对斜向的长条也没用。空间损耗为原来的三倍。
    * EWA Filtering：将任意不规则形状，分解为多个不同的圆形，多次查询。

## 纹理的应用Applying Texture 2 (in Lecture 10)
### 概述
* In modern GPUs, texture = memory + range query (filtering)
* Environment Map环境光照/环境贴图
  * 经典模型：犹他茶壶，斯坦福兔子与龙，Cornell's Box
* 记录环境光
  * Spherical Environment Map 将环境光记录在球上，展开
    * 问题：在球面上会扭曲，纬度高的部分看起来小，导致展开后不均匀
  * Cube Map 环境光记录在球的包围盒上
* 凹凸贴图Bump/法线贴图Normal mapping：用贴图在物体表面定义相对高度，高度的不同导致法线不同，着色结果会有明暗变化，体现凹凸感。
  * 不改变几何形体，对法线作扰动。
  * 如何扰动（flatland case）
    * 原来的法线 $\overrightarrow{n_p} = (0,\ 1)$
    * 扰动后的法线  
      </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img39.png) &nbsp;</br>  
      ① 某点处高度函数的切线（导数，近似） 
      $$ dp = c \cdot [h(p+1) - h(p)] （令\Delta x = 1）$$  
      其中 $c$ 为引入的常数：表示凹凸贴图的影响，作简单的缩放。
      ② 用向量将切线表示为 $(1,\ dp)$  
      ③ 再将切线逆时针旋转九十度 $(x,\ y) \rightarrow (-y,\ x)$ 。  
      ④ 最后单位化得新的法线
      $$ \overrightarrow{n_p} = (-dp,\ 1).normalized() $$
  * 如何扰动（3D case）
    * 原来的法线 $\overrightarrow{n_p} = (0,\ 0,\ 1)$
    * 扰动后的法线  
      ① 分别求某点在纹理坐标 $(u,\ v)$ 的水平方向（ $\overrightarrow{u}$ 方向）的切线，以及在 $\overrightarrow{v}$ 方向的切线
      $$ \begin{aligned} \frac{dp}{du} = c_1 \cdot [h(u+1) - h(u)] \\ \\ \frac{dp}{dv} = c_2 \cdot [h(v+1) - h(v)] \end{aligned} $$
      ② 类比推导可得新法线
      $$ \overrightarrow{n_p} = (-\frac{dp}{du},\ -\frac{dp}{dv},\ 1).normalized() $$
  * 上述原法线坐标为设定局部坐标系后的默认值，实际应用时要加入与世界坐标的转换。
  * 问题：虽然产生了凹凸的感觉，但是没有“某点的凸起会给其它部分带来的阴影”。
* 位移贴图Displacement mapping
  * 改变了几何形体上的顶点。
  * 相比凹凸/法线效果更好，但要求几何形体本身三角形够“精细”（三角形的顶点间隔比纹理定义的频率高），否则顶点三角形内部无法改变，也就得不到更好的效果。
  * DirectX的方法：动态曲面细分Dynamic Tessellation，先定义粗糙的模型，应用位移贴图的过程中检测是否需要更精细的模型，在过程中再细分。
* 3D Procedural Noise + Solid Modeling
  * 三维噪声纹理：用三维空间中的噪声函数定义空间中每个点的值。
  * 作二值化或其它变化等。
  * 如Perlin Noise。
* 记录信息
  * 如Ambient Occlusion环境光遮蔽，可以预计算后写进纹理。将着色结果乘上预计算的信息得到最后结果。
* 体渲染

# Lecture 10 Geometry 1 (Introduction)
## 几何形体
* 例子
  * 布料：纤维fiber $\rightarrow$ 股线ply $\rightarrow$ 棉毛丝线thread
  * 水滴入水溅起的涟漪
  * 城市远景：树、草地、建筑等。如何存储，如何渲染。
  * 动物毛发
  * 细胞内部
* 在图形学中的分类
  * Implicit Geometry隐式几何
  * Explicit Geometry显式几何
* Implicit Geometry隐式几何
  * 不给出实际的点，把点作归类，给出关系式。如球体： $x^2+y^2+z^2=1$ ，更一般的 $f(x,\ y,\ z)=0$
  * 缺点：难以知道“面上有哪些点”，不直观。
  * 优点：容易判断点是否在面上，容易与光线求交，容易严格描述物体。
* Explicit Geometry显式几何
  * 直接给出点坐标，或通过参数映射方法定义。  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img40.png) &nbsp;</br>  
  * 优点：对于映射方法的定义，遍历 $u、v$ 即可得到所有点。
  * 缺点：难以判断点是否在面上。
## More Implicit Geometry
* 代数方法
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img41.png) &nbsp;</br>
* CSG （Constructive Solid Geometry构造实体几何）：通过基本几何的布尔运算，定义新的几何，并写成布尔表达式。（目前使用非常广泛）
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img42.png) &nbsp;</br>
* Distance Functions 距离函数：不描述几何的表面，描述空间上任意一点到几何表面的最近距离。
  * 应用例子：Lecture 10 63:30（用距离函数作混合）
  * 恢复成表面：找距离函数为0处即表面。
* Level Set Methods 水平集：将距离函数写在二维格子/三维空间上。（无脑OS：距离函数的离散形式？）  
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img43.png) &nbsp;</br>  
  
* Fractals 分形：如雪花、Romenasco（西兰花的一种）。
  * 分形几何容易引起严重走样。

# Lecture 11 Curves and Surfaces
## Explicit Representations Geometry
* 点云Point Cloud：表面上足够密集的点。
* 多边形网格Polygon Mesh
* The wavefront Object File (.obj) Format
  * 给出空间中的点、法线、纹理坐标和连接关系
    ```
    # 顶点数据（Geometric vertices）
    v x y z
    # 纹理/贴图坐标点（Texture vertices）
    vt x y
    # 顶点法线（Vertex normals）
    vn x y z
    # 表面face（连接关系，哪三个点会形成三角形）
    f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
    ```
  * 自动生成时可能产生一些冗余行

## Curves: **贝塞尔曲线Bézier Curves**
* 用一系列控制点，定义曲线，即曲线满足的一些性质。
  * 控制点不一定在曲线上。
* de Casteljau Algorithm的直观解释
  * 给定三个点：二次贝塞尔曲线quadratic Bézier Curve
  * Step
    * 假设曲线生成的方向（以下标表示）和时间（从 $t \in [0,\ 1]$ ），求任意时刻 $t$ 的点位置。
    * 考虑时刻 $t$ 与总时间 $1$ 的比例，在三个点形成的两条线段上找符合该比例的位置，相连形成的新线段上再取符合比例的位置，最新生成的点数唯一，即 $t$ 时刻贝塞尔曲线所在位置。  
      </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img44.png) &nbsp;</br>

    * 贝塞尔曲线通过参数 $t$ 表示，所以是显式表示。
  * 给定四个点：三次贝塞尔曲线Cubic Bézier Curve，同理递归寻找唯一点。
* Bézier Curve的代数公式
  * 上述在线段上取点，可以看成线性插值，即
    $$ \left\{\begin{aligned}
      b_0^1(t) = (1-t)b_0 + tb_1 \\
      b_1^1(t) = (1-t)b_1 + tb_2
    \end{aligned}\right. $$
  * 然后对新得到的点再作线性插值，有
    $$ b_0^2(t) = (1-t)b_0^1 + tb_1^1 $$
  * 将第一层线性插值代入第二层，得到
    $$ b_0^2(t) = (1-t)^2b_0+2t(1-t)b_1+t^2b_2 $$
  * 观察系数可以发现，系数是由 $(1-t+t)^2$ 展开得到的
  * 而三次贝塞尔曲线整合后得到的系数由 $(1-t+t)^3$ 展开得到
  * 推导可得：给出n+1个控制点，可以得到n阶贝塞尔曲线，其在任意时刻 $t$ 都是给定的控制点的线性组合，系数为与时间相关的伯恩斯坦多项式Bernstein Polynomial（一个描述二项分布的多项式，$(1-t+t)^n$ 的展开）
    $$ b^n(t) = b_0^n(t) = \mathop{\Sigma}\limits_{j=0}^n B_j^n(t) \cdot b_j \\ B_i^n(t) = \left( \begin{matrix} n \\ i\end{matrix} \right)t^i(1-t)^{n-i}$$
  * 当控制点变为三维，不影响系数，所以仍然可以使用同样的代数表示。
  * 由 $(1-t+t)^n$ ，伯恩斯坦多项式为对 $1$ 的展开，因此同阶的所有项之和为 $1$ 。
* 贝塞尔曲线的性质
  * 规定过起点与终点： $t=0$ 必在起点， $t=1$ 必在终点。
  * 三次贝塞尔曲线（四个控制点）特性：起始、结束位置的切线为三倍。
    $$ b'(0) = 3(b_1-b_0) $$ 
    $$ b'(1) = 3(b_3-b_2) $$
  * 仿射变化性质Affine transformation property：在`仿射变化`下，可以直接对不同的控制点做变化，变化后的控制点生成的曲线与原曲线作相应变化相同。（仅限于仿射变化，其它变化如投影变化则不行。）
  * 凸包性质Convex hull property：贝塞尔曲线必然在控制点形成的凸包内。
* 逐段贝塞尔曲线Piecewise Bézier Curve
  * 有时由较多的控制点得到的贝塞尔曲线不太符合预期  
  </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img45.png) &nbsp;</br>  

  * 可以每次由很少的控制点逐段定义多个贝塞尔曲线，并相连。
    * 通常用三次四点。
    * 连续性：保证段之间的连接处光滑，即连接处切线（导数）相同，即方向、大小都相等。（切线意义的连续）
  * 连续性
    * 几何意义的连续： $C^0$ 连续 $C^0 continuity$ ，段之间相接。
      $$ a_n = b_0 $$
    * 切线意义的连续： $C^1$ 连续 $C^1 continuity$ ，两段邻接相接处的控制点到相接处距离相同，方向相反。
      $$ a_n = b_0 = \frac{1}{2}(a_{n-1} + b_1) $$
    * 更高阶的连续：如曲率连续。 $c^n$ 连续看 $n$ 阶导。
* 其它曲线（Spline 样条）
  * Spline 样条：由一些控制点定义的可控曲线，在任意处满足一定的连续性。
  * B-Splines（基函数样条Basis Splines）：用伯恩斯坦多项式，在时间t的几个不同的项，对不同的控制点做加权平均。或理解为用控制点的位置，对伯恩斯坦多项式进行加权求和。伯恩斯坦多项式即为基函数。相当于由不同的函数通过不同方式组合起来形成另一个函数。
    * 对贝塞尔曲线的一个扩展。
    * 调整控制点时，可以把曲线的变化控制在一定范围内。（比逐段更优秀的做法）
  * 非均匀有理B样条（NURBS）

## Surfaces
### **贝塞尔曲面**
* 由曲线扩展到曲面：类似双线性插值，在一个方向插值得曲线，由所得曲线再做插值扫描出曲面。
  * 另要考虑曲面之间的连接等，本课程略。
* 具体实现
  * 在两个方向上分别需要参数 $u、v$ 。
  * 更多的参考胡事民老师课程w。
### **网格操作：几何处理**
* 网格细分Mesh subdivision：三角网格更密集，使物体表面更光滑。
* 网格简化Mesh simplification：用更少的三角网格描述，节省存储。（细分的逆过程）
* 网格正规化Mesh regularization：使三角形趋向于正三角形，避免尖细三角形，会有较好的性质。

# Lecture 12 
## Surfaces
### 

# Lecture 13
# Lecture 14
# Lecture 15
# Lecture 16
# Lecture 17
# Lecture 18
# Lecture 19
# Lecture 20

# More
* B样条 www.bilibili.com/video/av66548502

# 备用

$$ \mathop{\Join}\limits_{i\ \theta\ j} $$


</br>&nbsp;![] &nbsp;</br>

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
一个题注[^1]

[^1]:cannotaddspace失败的题注示例

* 为了自动生成的目录格式，设置EOL的换行符号改成了\n，原auto
  * 不同系统换行符制定不同

    系统 | 换行符
    :---:|:---:
    Windows|\n\r
    Unix|\n
    Mac|\r

* Lecture 4罗德里格斯闫老师的推导还没看，记得去看一下