> # GAMES101 计算机图形学
> * B站：av90798049
> * 主讲人：闫令琪
> * PDF课件：http://www.cs.ucsb.edu/~lingqi/teaching/games101.html
> * 作业提交：http://www.smartchair.org/GAMES2020Course-YLQ

<!-- TOC -->

* [Lecture 01 Overview of Computer Graphics](#lecture-01-overview-of-computer-graphics)
  * [What is Computer Graphics](#what-is-computer-graphics)
  * [Why study Computer Graphics](#why-study-computer-graphics)
    * [小结](#小结)
  * [Course Topics](#course-topics)
    * [Four Topics](#four-topics)
    * [Out of the Course](#out-of-the-course)
  * [Course Logistics](#course-logistics)
* [Lecture 02 Review of Linear Algebra](#lecture-02-review-of-linear-algebra)
  * [Graphics' Denpendencies](#graphics-denpendencies)
  * [Vectors向量/矢量](#vectors向量矢量)
  * [Dot product点积](#dot-product点积)
  * [Cross product叉积](#cross-product叉积)
  * [Matrix矩阵](#matrix矩阵)
* [Lecture 03 Transformation](#lecture-03-transformation)
  * [Why study transformation](#why-study-transformation)
  * [2D Transforms二维变换](#2d-transforms二维变换)
  * [Homogeneous Coordinates齐次坐标](#homogeneous-coordinates齐次坐标)
  * [Inverse Transform逆变换](#inverse-transform逆变换)
  * [Composite Transform复合变换](#composite-transform复合变换)
  * [3D Transforms三维变换 I](#3d-transforms三维变换-i)
* [Lecture 04 Transformation Cont.](#lecture-04-transformation-cont)
  * [3D Transforms三维变换 II](#3d-transforms三维变换-ii)
  * [Viewing Transformation](#viewing-transformation)
    * [View/Camera Transformation视图变换](#viewcamera-transformation视图变换)
    * [Projection Transformation投影变换](#projection-transformation投影变换)
* [Lecture 05 Rasterization 1 (Triangles)](#lecture-05-rasterization-1-triangles)
  * [定义视锥frostum](#定义视锥frostum)
  * [Canonical Cube to Screen](#canonical-cube-to-screen)
  * [光栅化](#光栅化)
  * [**Drawing to Raster Displays**](#drawing-to-raster-displays)
* [Lecture 06 Rasterization 2 (Antialiasing and Z-Buffering)](#lecture-06-rasterization-2-antialiasing-and-z-buffering)
  * [Antialiasing](#antialiasing)
    * [**采样理论Sample theory**](#采样理论sample-theory)
    * [**原理分析**](#原理分析)
  * [可见性Visibility/遮挡occlusion（in Lecture 07）](#可见性visibility遮挡occlusionin-lecture-07)
* [Lecture 07 Shading 1 (Illumination, Shading and Graphics Pipeline)](#lecture-07-shading-1-illumination-shading-and-graphics-pipeline)
  * [着色Shading](#着色shading)
    * [**概念**](#概念)
    * [**A Simple Shading Model - Blinn-Phong Reflectance Model**](#a-simple-shading-model---blinn-phong-reflectance-model)
* [Lecture 08 Shading 2 (Shading, Pipeline and Texture Mapping)](#lecture-08-shading-2-shading-pipeline-and-texture-mapping)
  * [着色Shading](#着色shading-1)
    * [**着色频率Shading Frequencies**](#着色频率shading-frequencies)
  * [图形管线Graphics （Real-time Rendering） Pipeline](#图形管线graphics-real-time-rendering-pipeline)
  * [现代图形学发展](#现代图形学发展)
  * [纹理映射Texture Mapping](#纹理映射texture-mapping)
* [Lecture 09 Shading 3 (Texture Mapping Cont.)](#lecture-09-shading-3-texture-mapping-cont)
  * [Interpolation Across Triangles: 重心坐标Barycentric Coordinates](#interpolation-across-triangles-重心坐标barycentric-coordinates)
  * [纹理的应用Applying Texture 1](#纹理的应用applying-texture-1)
    * [**基本使用**](#基本使用)
    * [**纹理放大Texture Magnification - Easy Case**](#纹理放大texture-magnification---easy-case)
    * [**纹理放大Texture Magnification - Hard Case**](#纹理放大texture-magnification---hard-case)
    * [**Hard Case的处理1 - Mipmap**](#hard-case的处理1---mipmap)
  * [纹理的应用Applying Texture 2 (in Lecture 10)](#纹理的应用applying-texture-2-in-lecture-10)
    * [概述](#概述)
* [Lecture 10 Geometry 1 (Introduction)](#lecture-10-geometry-1-introduction)
  * [几何形体](#几何形体)
  * [More Implicit Geometry](#more-implicit-geometry)
* [Lecture 11 Curves and Surfaces](#lecture-11-curves-and-surfaces)
  * [Explicit Representations Geometry](#explicit-representations-geometry)
  * [Curves: **贝塞尔曲线Bézier Curves**](#curves-贝塞尔曲线bézier-curves)
  * [Surfaces](#surfaces)
    * [**贝塞尔曲面**](#贝塞尔曲面)
    * [**网格操作：几何处理**](#网格操作几何处理)
* [Lecture 12 Surfaces and Shadows](#lecture-12-surfaces-and-shadows)
  * [Surfaces](#surfaces-1)
    * [**Mesh Subdivision（upsampling）**](#mesh-subdivisionupsampling)
    * [**Mesh Simplification（downsampling）**](#mesh-simplificationdownsampling)
    * [**Mesh Regularization（same #triangles）**](#mesh-regularizationsame-triangles)
  * [Shadows](#shadows)
    * [**Shadow Mapping**](#shadow-mapping)
* [Lecture 13 Ray Tracing 1（Whitted-Style）](#lecture-13-ray-tracing-1whitted-style)
  * [定义光线（图形学中）](#定义光线图形学中)
  * [几种类型](#几种类型)
  * [光与物体表面交点Ray-Surface Intersection](#光与物体表面交点ray-surface-intersection)
    * [**与隐式表面求交**](#与隐式表面求交)
    * [**与显式表面求交**](#与显式表面求交)
    * [**光线与三角网格求交的优化**](#光线与三角网格求交的优化)
* [Lecture 14 Ray Tracing 2（Acceleration & Radiometry）](#lecture-14-ray-tracing-2acceleration--radiometry)
  * [包围盒的利用](#包围盒的利用)
    * [预处理包围盒网格](#预处理包围盒网格)
    * [空间划分Spatial Partitions](#空间划分spatial-partitions)
    * [物体划分Object Partitions & Bounding Volume Hierarchy（BVH）](#物体划分object-partitions--bounding-volume-hierarchybvh)
  * [辐射度量学Basic radiometry](#辐射度量学basic-radiometry)
    * [**Motivation**](#motivation)
    * [**Radiant Energy and Flux（Power）**](#radiant-energy-and-fluxpower)
    * [**Important Light Measurements of Interest**](#important-light-measurements-of-interest)
      * [辐射/发光强度 Radiant/Luminous Intensity](#辐射发光强度-radiantluminous-intensity)
* [Lecture 15 Ray Tracing 3（Light Transport & Global Illumination）](#lecture-15-ray-tracing-3light-transport--global-illumination)
      * [辐照度/辐射通量密度 Irradiance](#辐照度辐射通量密度-irradiance)
      * [辐亮度 Radiance](#辐亮度-radiance)
      * [辐照度Irradiance vs. 辐亮度Radiance](#辐照度irradiance-vs-辐亮度radiance)
  * [双向反射分布函数Bidirectional Reflectance Distribution Function（BRDF）](#双向反射分布函数bidirectional-reflectance-distribution-functionbrdf)
    * [**用辐射度量学解释反射** Reflection at a Point](#用辐射度量学解释反射-reflection-at-a-point)
  * [**渲染方程 The Rendering Equation**](#渲染方程-the-rendering-equation)
    * [解渲染方程](#解渲染方程)
  * [概率论Probability](#概率论probability)
    * [随机变量](#随机变量)
    * [期望](#期望)
    * [连续型随机变量的概率密度函数Probability Density Function](#连续型随机变量的概率密度函数probability-density-function)
    * [随机变量函数Function of a random variable](#随机变量函数function-of-a-random-variable)
* [Lecture 16 Ray Tracing 4（）](#lecture-16-ray-tracing-4)
  * [蒙特卡洛积分Monte Carlo Integration](#蒙特卡洛积分monte-carlo-integration)
  * [路径追踪Path Tracing](#路径追踪path-tracing)
    * [Motivation](#motivation)
    * [**A Simple Monte Carlo Solution（直接光照）**](#a-simple-monte-carlo-solution直接光照)
    * [**Global Illumination（引入间接光照）**](#global-illumination引入间接光照)
    * [问题](#问题)
    * [在 Low SPP 的情况下提高渲染质量](#在-low-spp-的情况下提高渲染质量)
    * [Side Notes](#side-notes)
* [Lecture 17 Materials and Apperances](#lecture-17-materials-and-apperances)
  * [材质](#材质)
    * [**漫反射 Diffuse / Lambertian Material**](#漫反射-diffuse--lambertian-material)
    * [**镜面反射 Specular Reflection**](#镜面反射-specular-reflection)
    * [**折射 Refraction**](#折射-refraction)
    * [**微表面材质/模型 Microfacet Material**](#微表面材质模型-microfacet-material)
      * [**Motivation**](#motivation-1)
      * [**Microfacet Theory**](#microfacet-theory)
  * [材质的分类](#材质的分类)
    * [**各向同性Isotropic / 各向异性Anisotropic Materials (BRDFs)**](#各向同性isotropic--各向异性anisotropic-materials-brdfs)
    * [**Anisotropic BRDFs**](#anisotropic-brdfs)
  * [BRDF的性质 Properties of BRDFs](#brdf的性质-properties-of-brdfs)
  * [BRDF的测量 Measuring BRDFs](#brdf的测量-measuring-brdfs)
    * [Motivation](#motivation-1)
    * [Image-Based BRDF Measurement](#image-based-brdf-measurement)
    * [BRDF测量结果的表示 Representing Measured BRDFs](#brdf测量结果的表示-representing-measured-brdfs)
* [Lecture 18 Advanced Topics in Rendering](#lecture-18-advanced-topics-in-rendering)
  * [高级光线传播 Advanced Light Transport](#高级光线传播-advanced-light-transport)
  * [](#)
* [Lecture 19](#lecture-19)
* [Lecture 20](#lecture-20)
* [Lecture 21](#lecture-21)
* [Lecture 22](#lecture-22)
* [Experiment](#experiment)
  * [环境配置](#环境配置)
  * [HW1](#hw1)
  * [HW2](#hw2)
  * [HW5](#hw5)
  * [FAQ](#faq)
    * [HW3](#hw3)
* [More](#more)
* [备用](#备用)

<!-- /TOC -->

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
  * 其中模型变换即在模型空间中做平移、旋转、缩放等基本变换。

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
* 相机根据 $M_{view}$ 变换后，根据相对运动，其它物体也统一作一次该变换。——也就是根据相机所作的旋转和平移，把物体也相对变化一下，注意也要先平移后旋转。
  * 【？这样看到的东西不就一直不变了吗orz？】【是的没错，就是为了给相机定位，但是相机看到的场景不能变】
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
  * 设 $l=-r$，$b=-t$ 则定义宽高比和垂直可视角就能推及 $r、t、n$ 三个方向的坐标范围。

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
    * 二维向量叉积
      $$ \overrightarrow{a}\times\overrightarrow{b} = \left|\begin{aligned} x_a\ &\ y_a \\ x_b\ &\ y_b \end{aligned}\right| = x_ay_b+x_by_a$$
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
      说明：考虑单位面积所能接收到的能量，与光线 传播的距离的平方成反比。
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
      ② $Diffuse\ Coefficient$ ：光的漫反射的出射能量占入射能量的比例。  
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
* 网格细分Mesh subdivision：三角网格更密集，使物体表面更光滑，细节更丰富。
* 网格简化Mesh simplification：用更少的三角网格描述，节省存储。当模型复杂但成像距离较远，不需要太多细节时也要简化。但简化时要维持连接关系。（细分的逆过程）
* 网格正规化Mesh regularization：使三角形趋向于正三角形，避免尖细三角形，会有较好的性质。改进三角形质量时不能丢失物体本身的质量。

# Lecture 12 Surfaces and Shadows
## Surfaces
### **Mesh Subdivision（upsampling）**
* 细分三角形后还要进行位置的变化，否则不能改变形状。
* **Loop Subdivision**
  * 增加三角形数量：取三角形的三边中点相连，从一个增加到四个。  
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img46.png) &nbsp;</br>

  * 调整三角形位置：即调整顶点位置。
    * 将顶点分为原有顶点和新增顶点。
    * 调整新顶点：新的顶点必然在原来三角形的边上，且通常情况下非物体边界的顶点必然被多个三角形共享。  
      </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img47.png) &nbsp;</br>

      将两三角形的共享中点位置调整到周围几个旧顶点值的平均：$\frac{3}{8}\cdot (A+B) + \frac{1}{8}\cdot (C+D)$
    * 调整旧顶点：考虑自己本身的原位置和周围旧顶点的位置。  
      </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img48.png) &nbsp;</br>

      定义顶点的度 $n$ （与几条边相关），以及一个与顶点的度相关的量 $u = \frac{1}{n}[\frac{5}{8}-(\frac{3}{8}+\frac{1}{4}\cos\frac{2\pi}{n})^2]$  
      将旧顶点位置调整到：$(1-n\cdot u)\cdot pos_{old} + u\cdot pos_{old\_neighbor\_sum}$
  * 只适用于三角形网格。
* **Catmull-Clark Subdivision（General Mesh）**
  * 适用于任意网格。
  * 定义 Quad face四边形面，Non-quad face非四边形面，Extraordinary vertex奇异点（度不为4的点）。
  * Step
    * 取每条边的中点、每个面的中心并相连。  
      性质：在非四边形的面内新增的点，由于要与各边相连，所以该点必然是奇异点。并且这些非四边形的面都会被细分为四边形面，再作细分不会新增奇异点。即“Catmull-Clark细分在第一次细分，增加非四边形面数的奇异点后，所有非四边形面被细分为四边形面，之后的细分不会再新增奇异点个数。”
    * 调整点的位置，分为三类点：面中心点Face point、边中点Edge point、原有旧顶点Vertex point  
      ① </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img49.png) &nbsp;</br>
        $$f=\frac{v_1+v_2+v_3+v_4}{4}$$
      ② </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img50.png) &nbsp;</br>
        $$e=\frac{v_1+v_2+f_1+f_2}{4}$$
      ③ </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img51.png) &nbsp;</br>
        $$v=\frac{f_1+f_2+f_3+f_4+2(m_1+m_2+m_3+m_4)+4p}{16}$$

### **Mesh Simplification（downsampling）**
* 不同情况下选用不同程度的复杂模型。
  * 问题：网格的复杂程度，近处精细远处粗略。何时变化？过渡时不能被人眼明显察觉。“几何的层次结构”问题，不好解决。
* **边坍缩Edge Collapse**
  * 直观感受如图</br>&nbsp;![](note&#32;-&#32;image/GAMES101/img52.png) &nbsp;</br>
  * 二次误差度量Quadric Error Metrics：衡量坍缩、保留哪些边。找到一个点，最小化二次误差。（二次误差：类似L2距离，找点到原来相关面的距离平方和最小。）
  * Step
    * 对原模型的每一条边，考虑其坍缩成点，其处于最优位置上时，二次误差最小值。
    * 从所有边中二次误差最小的，从小到大依次坍缩。
    * 由于坍缩时会引起附近其它边的变化，因此实际操作时，将受影响的边二次误差值进行更新。
  * 由于从局部优化到整体，所以实际上是贪心算法。（为啥可行呢，因为效果看起来害整挺好（

### **Mesh Regularization（same #triangles）**
* 无

## Shadows
* 之前所说的着色都是考虑局部的单个点，而考虑到全局中其它物体，应该要有阴影产生。光栅化方法中解决阴影的办法：Shadow Mapping。
### **Shadow Mapping**
* 图像空间算法Image-space Algorithm
  * 特点
    * 生成阴影时不需要知道场景中的几何信息
    * 会产生走样问题
  * 思想
    * 不在阴影里的点，说明摄像机和光源都能感知到该点。而阴影里的点，摄像机能看到，但光源看不到。
  * 这里介绍点光源产生的硬阴影（有明显边界）。
* Step
  * Render from Light. 从光源方向出发，渲染场景中像素点的深度图。（不着色）
  * Render from Eye. 从摄像机出发，渲染场景像素点时投影到深度图上，看此时的深度是否与深度图一致，若比深度图深，则说明光源对该点的照射应被其它东西遮挡。
    
    </br>&nbsp;![](note&#32;-&#32;image/GAMES101/img53.png) &nbsp;</br>

* 问题
  * 判断“是否与深度图一致”时，涉及到浮点数判等，以及两步Render时像素位置差等，导致判等精度问题很大。从而产生了各种优化办法：不判相等判大小，加上极小量后判大小等。
  * 两次Render的分辨率问题，深度图分辨率高消耗大，分辨率低容易走样。
* 软阴影：当光源有一定大小，从光源的不同处Render会产生不同的深度图。
  * 对阴影的理解：完全看不到光源处umbra本影，部分看到光源penumbra半影。软阴影就是本影到半影到光亮处的过渡。
* 对于阴影有很多的研究，但仍难以解决全局上的光照问题。

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
  * 之前定义了光本身的总能量Radiant Flux/Power $\Phi$
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


## 

# Lecture 19
# Lecture 20
# Lecture 21
# Lecture 22


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

<!-- 目录 -->


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