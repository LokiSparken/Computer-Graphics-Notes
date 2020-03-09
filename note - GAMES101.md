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
    $$
        \left(
        \begin{matrix}
            x' \\
            y'
        \end{matrix}
        \right)
        =
        \left(
        \begin{matrix}
            1 & 0 & t_x \\
            0 & 1 & t_y \\
            0 & 0 & 1
        \end{matrix}
        \right)
        \cdot
        \left(
        \begin{matrix}
            x \\
            y \\
            1
        \end{matrix}
        \right)
        =
        \left(
        \begin{matrix}
            x+t_x \\
            y+t_y \\
            1
        \end{matrix}
        \right)
    $$
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
* Sampling is ubiquitous in CG 采样在CG中无处不在
  * 动画是对时间的采样
  * 采样产生的问题也是无处不在的
* Sampling Artifacts (Errors/Mistakes/Inaccuracies) in CG
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
## 可见性Visibility/遮挡occlusion（in Lecture 7）
* 

# Lecture 07 Shading 1 (Illumination, Shading and Graphics Pipeline)

# Lecture 08 Shading 2 (Shading, Pipeline and Texture Mapping)

# Lecture 09

# Lecture 10

# Lecture 11

# Lecture 12

# Lecture 13

# Lecture 14

# Lecture 15

# Lecture 16

# Lecture 17

# Lecture 18

# Lecture 19

# Lecture 20


# 备用
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