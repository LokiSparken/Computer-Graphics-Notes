> # [GAMES202 Real-Time High Quality Rendering](https://www.bilibili.com/video/BV1YK4y1T7yY)
> * 男神终于又开课辣！！！

<!-- TOC -->

* [Lecture 1 - Introduction and Overview](#lecture-1---introduction-and-overview)
* [Lecture 2 - Recap of CG Basics](#lecture-2---recap-of-cg-basics)
  * [一、流水线回顾](#一流水线回顾)
  * [二、OpenGL](#二opengl)
  * [三、OpenGL Shading Language（GLSL）](#三opengl-shading-languageglsl)
    * [**`Debug`**](#debug)
  * [四、The Rendering Equation](#四the-rendering-equation)
  * [五、Calculus（In Lecture 3）](#五calculusin-lecture-3)
* [Lecture 3 - Real-time Shadow 1](#lecture-3---real-time-shadow-1)
  * [Recap: shadow mapping](#recap-shadow-mapping)
    * [Shadow mapping 做法回顾](#shadow-mapping-做法回顾)
    * [**`Shadow Map 的问题`**](#shadow-map-的问题)
      * [`1. Self Occlusion（采样精度造成的平面纹路）`](#1-self-occlusion采样精度造成的平面纹路)
      * [`2. Aliasing 采样问题`](#2-aliasing-采样问题)
  * [Shadow mapping 的数学原理](#shadow-mapping-的数学原理)
  * [Percentage closer soft shadows（PCSS）](#percentage-closer-soft-shadowspcss)
    * [Percentage Closer Filtering（PCF）](#percentage-closer-filteringpcf)
    * [Percentage Closer Filtering（PCSS）](#percentage-closer-filteringpcss)
* [Lecture 4 - Real-time Shadow 2](#lecture-4---real-time-shadow-2)
  * [More on PCF and PCSS](#more-on-pcf-and-pcss)
    * [卷积表达式](#卷积表达式)
    * [优化](#优化)
  * [Variance (soft) shadow mapping（V(S)SM）](#variance-soft-shadow-mappingvssm)
    * [VSSM 基本思想 1 - 基于 PCSS Step 3](#vssm-基本思想-1---基于-pcss-step-3)
    * [VSSM 基本思想 2 - 基于 PCSS Step 1](#vssm-基本思想-2---基于-pcss-step-1)
    * [Others](#others)
  * [MIPMAP and Summed-Area Variance Shadow Maps](#mipmap-and-summed-area-variance-shadow-maps)
  * [Moment shadow mapping（MSM）](#moment-shadow-mappingmsm)
  * [各种 CSM](#各种-csm)
  * [Distance field soft shadows（in Lecture 5）](#distance-field-soft-shadowsin-lecture-5)
* [Lecture 5 - Real-time Environment Mapping](#lecture-5---real-time-environment-mapping)
  * [`Shading` from Environment Lighting](#shading-from-environment-lighting)
    * [Image-Based Lighting（IBL）](#image-based-lightingibl)
    * [Split sum approximation 1 - 光照项 $L_i$](#split-sum-approximation-1---光照项-l_i)
    * [Split sum approximation 2 - BRDF 项 $f_r$](#split-sum-approximation-2---brdf-项-f_r)
  * [`Shadow` from Environment Lighting（in Lecture 6）](#shadow-from-environment-lightingin-lecture-6)
* [Lecture 6 - Real-Time Environment Mapping（Precomputed Radiance Transfer）](#lecture-6---real-time-environment-mappingprecomputed-radiance-transfer)
  * [基本数学知识（GAMES101 回顾）](#基本数学知识games101-回顾)
  * [Spherical Harmonics](#spherical-harmonics)
  * [用球谐函数解决 diffuse 物体的环境光 shading 问题](#用球谐函数解决-diffuse-物体的环境光-shading-问题)
  * [Precomputed Radiance Transfer（PRT） - Idea & Diffuse](#precomputed-radiance-transferprt---idea--diffuse)
  * [球谐函数的性质 Properties of Spherical Harmonics](#球谐函数的性质-properties-of-spherical-harmonics)
* [Lecture 7 - Real-time Global Illumination (in 3D)](#lecture-7---real-time-global-illumination-in-3d)
  * [Precomputed Radiance Transfer（PRT） - Glossy](#precomputed-radiance-transferprt---glossy)
  * [More basis functions](#more-basis-functions)
  * [More information](#more-information)
  * [Real-Time Global Illumination（in 3D/world space）](#real-time-global-illuminationin-3dworld-space)
    * [Chatting time](#chatting-time)
    * [Reflective Shadow Maps（RSM）](#reflective-shadow-mapsrsm)
    * [Light Propagation Volumes（LPV）（in Lecture 8）](#light-propagation-volumeslpvin-lecture-8)
* [Lecture 8 - Real-Time Global Illumination (Screen Space)](#lecture-8---real-time-global-illumination-screen-space)
  * [Real-Time Global Illumination（in 3D/world space）](#real-time-global-illuminationin-3dworld-space-1)
    * [Voxel Global Illumination（VXGI）](#voxel-global-illuminationvxgi)
  * [Real-Time Global Illumination（Screen Space）](#real-time-global-illuminationscreen-space)
    * [Screen Space Ambient Occlusion（SSAO）](#screen-space-ambient-occlusionssao)
    * [Screen Space Directional Occlusion（SSDO）（in Lecture 9）](#screen-space-directional-occlusionssdoin-lecture-9)
* [Lecture 9 - Real-Time Global Illumination（Screen Space cont.）](#lecture-9---real-time-global-illuminationscreen-space-cont)
    * [Screen Space Reflection（SSR）](#screen-space-reflectionssr)
* [Lecture 10 - Real-time Physically-based Materials(surface models)](#lecture-10---real-time-physically-based-materialssurface-models)
  * [微表面模型 Microfacet BRDF](#微表面模型-microfacet-brdf)
    * [The Kulla-Conty Approximation](#the-kulla-conty-approximation)
  * [Shading Microfacet Models using **`Linearly Transformed Cosines (LTC)`**（Lecture 11）](#shading-microfacet-models-using-linearly-transformed-cosines-ltclecture-11)
  * [Disney principled BRDF](#disney-principled-brdf)
  * [Non-Photorealistic Rendering（NPR）](#non-photorealistic-renderingnpr)
    * [Outline Rendering（轮廓线）](#outline-rendering轮廓线)
    * [Color blocks](#color-blocks)
  * [Strokes Surface Stylization](#strokes-surface-stylization)

<!-- /TOC -->

# Lecture 1 - Introduction and Overview
* About Lecture Name
  * Real-Time：Speed > 30FPS（VR/AR > 90FPS）
  * High Quality：时间和质量的 trade off、（至少近似）物理正确
* Lecture Content
  * 阴影和环境光
  * GI
  * PBS
  * 实时光追
* 课前闲聊系列
  * Lec 3 - RTR 4th（弹幕：《实时渲染导论》）

# Lecture 2 - Recap of CG Basics
## 一、流水线回顾
* Basic GPU hardware pipeline
* 纹理坐标的 UV 是如何参数化出来的：参数化问题，详见 GAMES102 几何处理

## 二、OpenGL
* OpenGL 渲染流程、相关主要概念及 API 举例
  * VBO
  * 在一个 framebuffer 绘制多个纹理（Multiple Render Target）
  * Vertex Shader：处理顶点属性
  * Fragment Shader：光照与着色计算，`深度测试`（OpenGL 内置/自定义）
  * V/F Shader 的交互：V 将 F 需要的顶点属性输出，由 OpenGL 插值后从 F 输入并使用
  * 一个 pass：一个场景渲染一次
  * Multiple passes：暂存到纹理
* 把 framebuffer 直接渲染到屏幕的问题：上一帧未渲染完（显示器刷新率问题），下一帧开始渲染，由于直接渲到屏幕，会导致撕裂。解决方案：
  * 垂直同步：锁帧，使显示器刷新率和显卡输出帧率匹配
  * 双重缓冲：暂存到某纹理，渲染完毕后交给屏幕。
  * 三重缓冲：双重缓冲在屏幕未刷新，暂存的纹理缓冲也渲染结束时需要等待纹理缓冲被腾出。再加一重更流畅。但显存占用大。（尤其在打开需四倍空间的 AA 处理后）

## 三、OpenGL Shading Language（GLSL）
* Shading Language 历史小姿势
* Shader 使用流程：写 shader 源码、创建 shader、编译、链接到 program
* Vertex Shader 命名：
  * attribute 顶点属性变量，前缀 `a`
  * uniform 全局变量，前缀 `u`
  * varying 待插值量，前缀 `v` （highp 计算精度相关）
### **`Debug`**
* Shader Debug 历史小姿势
* 新 Debug 工具
  * Nsight Graphics（cross platform，NVIDIA GPUs only）
  * RenderDoc（cross platform）（弹幕：可以调试 WebGL，需要从 RenderDoc 启动 Chrome）
* 男神 Debug 小技巧
  * 把值作为颜色输出，使用 color picker 色值提取工具（如 Mac - Digital Color Meter）看值（直播弹幕：RGB 调试法）

## 四、The Rendering Equation
* 实时渲染中对渲染方程的理解
    
    ![](note%20-%20image/GAMES202/1.png)
  * 考虑 visibility
    * 对环境光的理解更直观
    * `考虑某方向的入射光，在当前 shading point 是否可见`
  * 通常 BRDF 与 cosine-weighted BRDF 不作区分
* 实时渲染关注的问题：如何多 one-bounce 间接光照

## 五、Calculus（In Lecture 3）
* 微积分不复习辽，用到再提

# Lecture 3 - Real-time Shadow 1
## Recap: shadow mapping
### Shadow mapping 做法回顾
* `A 2-Pass, image-space Algorithm（双 Pass，图像空间算法）`
  * Pass 1：得到光源位置的深度纹理（shadow map）
  * Pass 2：从相机处渲染时通过光源的 shadow map 判断物体是否能被该光源照亮（比较两波得到的深度值）
  * 注意：产生的是硬阴影
* 优点：不需要完整的场景的几何信息
* 缺点
  * Self Occlusion 自遮挡问题
  * Aliasing 锯齿现象
* 历史小姿势：早期光追对离线开销都太大的时候也会用这种方法。如 Toy Story 玩具总动员。
* **`Tips`**：Shadow Mapping 两 Pass 所比较的 $z$ 值需要`统一`，都用“在做透视投影之前的到视点距离”（实际距离），或者都用“做完 MVP 后的 $z$ 值”
  * GAMES101 透视投影 Q：除了近平面与远平面，中间的平面被挤压后 $z$ 值趋向近平面还是趋向远平面？
  * A：远平面。（盲猜成功！！！（虽然还是不知道为什么
  * 总之透视投影前后 $z$ 值有改变，用于比较时注意一致性
### **`Shadow Map 的问题`**
#### `1. Self Occlusion（采样精度造成的平面纹路）`
* 问题产生原因
    
    ![](note%20-%20image/GAMES202/2.png)
    * 纹理的分辨率导致`一个像素会代表一小块区域`，并且算法默认一个像素内的深度值是个已知的定值。
    * 然而实际上采样的角度不同，会导致一些点，从光源角度采样到 A 像素，得到深度值略浅，从视点角度采样的是 B 像素，深度值略深，被附近的像素遮挡。
        
        ![](note%20-%20image/GAMES202/3.png)
    * 如闫老师灵魂图绘所示，光源角度越正，如垂直照亮平面，没有什么大问题。光源角度越偏，Grazing Angle 问题会最严重。
* Self Occlusion 问题解决办法：在比较深度值时，略加偏移。且这个偏移可以根据光源照射的角度（即 Self Occlusion 严重程度）在某区间内变化。
* `引入新问题 Detached Shadow：`部分该有的阴影无了
    
    ![](note%20-%20image/GAMES202/5.png)
* Detached Shadow 问题解决办法
  * 调参竟在我身边：找到合适的偏移，尽量解决自遮挡又不缺明显阴影
  * （工业界不咋用）Second-depth shadow mapping：光源深度纹理记录最小值和次小值，比较时使用两者中间值。（图为上面缺掉的鞋子）

    ![](note%20-%20image/GAMES202/4.png)
    * 缺陷 1：要求物体有正反面，保证次小值的存在。
    * 缺陷 2：求次小值问题。虽然时间复杂度不变，但是 **`RTR does not trust in COMPLEXITY！`** 只相信绝对的速度=。=（新效果加入游戏可供分配的时间：`1ms`）（这么说起来就算只要 30FPS，一帧也就只有 33ms？1ms 真的很巨额了……）

#### `2. Aliasing 采样问题`
* 问题产生原因
  * 因为去掉了完整的场景几何信息，通过光源的深度纹理采样做比较，因此会依赖于深度纹理的分辨率
* 解决办法：Cascaded Shadow Map（CSM）

## Shadow mapping 的数学原理
<!-- * 微积分中的一些不等式
  * Schwarz
    $$ [\int_a^b f(x)g(x)dx]^2 \leqslant \int_a^bf^2(x)dx \cdot \int_a^bg^2(x)dx$$
  * Minkowski
    $$ \left \{ \int_a^b [f(x) + g(x)]^2 dx \right \}^{\frac{1}{2}} \leqslant \left \{ \int_a^b f^2(x) dx \right \}^{\frac{1}{2}} + \left \{ \int_a^b g^2(x)dx \right \}^{\frac{1}{2}}$$ -->
* 实时渲染中关注：近似相等 approximate
    $$ \int_\Omega f(x) g(x) dx \approx \frac{\int_\Omega f(x) dx}{\int_\Omega dx} \cdot \int_\Omega g(x) dx $$
    * 其中，分母 $\int_\Omega dx$ 用于归一化。如 $f(x)、g(x)$ 有常值函数，则积分时要乘上积分区间，但又不希望因为使用近似导致能量的数量级暴增，所以把这个积分区间除掉。
    * 近似准确的情况
      * `情况一`：实际积分范围很小（如球面上的一小块）
      * `情况二`：函数 $g(x)$ （留在积分内的部分）足够 smooth（在其范围内 min/max 差别不大，或低频？低平？）【？】没听懂。【check】可能是指，导数是平滑的？啊不，就是这 smooth 不是指函数的连续性，而是值变化不大。如面光源的 Radiance 不变。
* 对 BRDF 应用近似相等
    
    ![](note%20-%20image/GAMES202/6.png)
    $$ \Downarrow $$
    ![](note%20-%20image/GAMES202/7.png)
    * 近似所得的形式，抽出的部分即 Visibility，剩下的为 Shading 部分
    * 成立的原因一：`点光源`、`平行光`发出的光，照射到各 shading point 时只有一个方向，就意味着积分区间已经是个极小点（注意渲染方程要积分的对象是不同方向的入射光），所以可以看作近似相等，且不用积分，直接相乘
    * 成立的原因二：留在积分函数内的部分（BRDF 和光照）smooth，即 Radiance 不变，BRDF 项为 diffuse（如果是高光则变化很大）
    * 因此不准确的情况：面光源、环境光（可看作超大面光源），会导致入射光方向很多，积分范围大。高光导致 $g(x)$ 项变化很大。（但面光源可以视为多个带权点光源）
* 可以用 numpy 试一下。

## Percentage closer soft shadows（PCSS）
* 古老但现在仍常用，可以产生软阴影
### Percentage Closer Filtering（PCF）
* 一种用于阴影抗锯齿的方法
  * 不是在阴影图或者最终结果图上做 blur，而是生成阴影、判断的过程中 filtering
  * 注意：在阴影图上 blur 是无效的，因为在深度测试时得到的结果还是 $0/1$
* PCF Solution [Reeves, SIGGRAPH 87]
  * Step 1 - 深度测试时不只采样深度图上对应单像素，而是考虑周围一圈（如 $7\times 7$ 范围）与 shading point 的遮挡关系，得到测试结果 $0/1$
  * Step 2 - 对这个范围的测试结果取均值（看作是在阴影 $0.0$ 到光源 $1.0$ 之间的一个比例，用它对着色做衰减）
* 启发：`filter 范围`决定阴影锯齿的软硬度 $\Rightarrow$ 决定阴影的软硬度

### Percentage Closer Filtering（PCSS）
* 定义影响 filter 范围的 `Blocker Distance`：`遮挡物`（产生阴影的物体位置）与`阴影接收物`（接收阴影的位置）之间的距离（可以观察落在纸上的笔尖）

    ![](note%20-%20image/GAMES202/8.png)
  * 即 relative `average` projected blocker depth （相对、平均、投影的遮挡距离）
  * $w_{Penumbra}$ 即阴影软硬程度，软阴影的范围
  * 由相似三角形求得 $w_{Penumbra}$ 即可，如：
    $$ w_{Penumbra} = (d_{Receiver} - d_{Blocker}) \cdot \frac{w_{Light}}{d_{Blocker}} $$
* 注意 `Average`：实际应用时 Blocker 物体形状不确定。对一个 shading point，考虑一定范围内（即 filter 范围），在 shadow map 上有多少像素能挡住该 shading point（即 filter 结果为 $1$ 的位置），取这些像素的深度的平均值
* **`PCSS Solution`**
  * Step 1 - 从 shading point 采样点光源的 shadow map，做 `blocker depth estimate`：考虑对应像素点周围的一块区域，判断是否在阴影里。在阴影里，则该像素点必是一个 blocker。得到所有 blocker 深度的均值，即 average blocker depth。
    * 【？】为什么又出现一个范围……那这个范围怎么取的？？？【check】阿巴阿巴……原来后面有解释啊懵了半天orz：随便（？）取个常量（如 $5\times 5$），或者根据光源大小、阴影接收物 receiver 到光源的距离动态调整（类似 frustum。越远范围可以取越小。）
        
        ![](note%20-%20image/GAMES202/9.png)
  * Step 2 - 用 average blocker depth 决定 filter size
    * 【？】说起来点光源的话 $w_{Light}$ 怎么整……貌似理论上点光源不产生软阴影……？闫老师：点光源和 directional 本身就应该产生硬阴影
  * Step 3 - PCF
* PCSS 与 PCF 的开销问题（Lecture 4）
* 闲聊时间
  * 喜闻乐见游戏安利阶段（第一人称开放世界）：Dying Light、辐射、上古卷轴

# Lecture 4 - Real-time Shadow 2
## More on PCF and PCSS
### 卷积表达式
![](note%20-%20image/GAMES202/10.png)
* PCF 的卷积表达式

    $$ [w * f](p) = \sum_{q\in \mathcal{N}(p)} w(p,q)f(q) $$
    * 在 $p$ 的邻域中取各 $q$ 的权重值
* PCSS

    $$ V(x) = \sum_{q\in \mathcal{N}(p)} w(p, q) \cdot  \chi^+ [D_{sm}(q) - D_{scene}(x)]$$
    * 其中，$\chi$ （$k\grave{a}i$）为一个符号函数，自变量大于 $0$ 时值为 $1$，反之为 $0$。
* 因此
  * 如果对 shadow map 作模糊，实际上的结果是 $\chi^+{[w * D_{SM}](q) - D_{scene}(x)}$ ，最后结果还是二值的。
  * 而对最后已有锯齿的图像空间结果作模糊则是 
  $$ \sum_{y\in\mathcal{N}(x)} w(x, y)V(y)$$
### 优化
* 问题
  * 一：考虑邻域，量大（blocker search & percentage closer filtering）
  * 二：越软的阴影 filter region 越大，量大
  * Solution：随机采样，Trade Off：Noise
    * 工业界常见做法：稀疏采样，最后在图像空间上做降噪
    * 边缘 `flicker` 问题：每帧随机采样，采样的点不同，导致 Noise 每帧也长得不一样，连续帧看起来会抖。
    * `boiling artifact` 问题：噪声无法被低通滤波去除所致

## Variance (soft) shadow mapping（V(S)SM）
### VSSM 基本思想 1 - 基于 PCSS Step 3
* 考虑 PCF 阶段的 key point - shading point 周围能遮挡它的纹素`比例`
  * （盲猜范围查询！……不，是第 k 大……范围第 k 大……范围均值和方差……假装盲猜成功（
  * 用`正态分布`作 `approximate`：需要`均值 mean`（期望）、`方差 variance`（决定中心位置、中心范围大小（宽度））
* 范围均值求法
  * Hardware MIPMAP：插值误差、只能正方形
  * **`Summed Area Tables`**（SAT）：二维任意矩形
* 范围方差求法 - 经典概率论公式
    $$ Var(X) = E(X^2) - E^2(X) $$
    * $E^2(X)$ 范围均值假设已求得
    * $E(X^2)$ 只需再记一张平方深度图（实现的时候可以直接写在 texture 的另一个通道）（妙啊！！！）
* 比例如何求 - CDF
    
    ![](note%20-%20image/GAMES202/11.png)
  * 即求 `PDF 图像面积`
  * `Gaussian PDF` 积分 -> **`Error Function（误差函数）`**
    * 详见补充材料
    * 有数值解（C++ erf()），没有解析解
    * 闫老师：数值解也比打表强嘛！（草w
* 然而求解还是很麻烦 - `切比雪夫不等式 Chebychev's inequality`
    $$ P(x>t) \leqslant \frac{\sigma^2}{\sigma^2 + (t-\mu)^2} $$
  * $\mu$：均值，$\sigma^2$：方差
  * 切比雪夫不等式：假装认为是个任意单峰分布，给定查询点 $t$，其右侧面积不超过 $\frac{\sigma^2}{\sigma^2+(t-\mu)^2}$
    
    ![](note%20-%20image/GAMES202/12.png)
  * 条件：$t$ 必须在均值的右侧
  * （草w，弹幕：看到不等式就两眼放光，又可以 trick 了）
* 问题：动态场景每帧更新的开销
### VSSM 基本思想 2 - 基于 PCSS Step 1
* 考虑 block search 阶段：需要知道`遮挡部分平均深度`$z_{occ}$（前述已解决了整体平均深度 $z_{Avg}$）
  * 能遮挡与不能遮挡的两部分分别以当前 shading point 的深度值 $d$ 为界，有：
    * Blocker 部分：$z < d$ 
    * Non-blocker 部分：$z > d$
  * 两部分必然满足
    $$ \frac{N1}{N}z_{unocc} + \frac{N2}{N}z_{occ} = z_{Avg} $$
    * $z_{Avg}$ 前述已求。
    * 其中 Non-blocker 部分所占比例和上述比例问题一样，可以用切比雪夫近似。于是 Blocker 部分比例同时得解！
    * $z_{unocc}$ 大胆假设：$z_{unocc} = t$（即阴影接收物为平面）（所以`曲面`和`与光源不平行`的情况下，该假设与实际差别太大，会出现问题）
### Others
* 为什么现在更常用 PCSS：因为现在图像空间的降噪手段 tql（时间空间结合，效果很好）
* 正态分布是举栗子，实际上 VSSM 直接切比雪夫

## MIPMAP and Summed-Area Variance Shadow Maps
* 来了！矩形范围查询！
* MIPMAP：大软阴影会有比较明显的 artifacts
* Summed-Area Table
  * 果然是你！二维前缀和！
  * 实现：各行各列求和时可以并行，还可以 compute shader（【？】高级起来了）

## Moment shadow mapping（MSM）
* VSSM 的问题
  * VSSM 思想的局限性：遮挡物比较少，PDF 可以看作几个峰值，用单峰的分布近似误差会特别大
    * `light leaking`：阴影处因为近似的不合理导致在阴影区域有的地方特别亮
    * `non-planarity artifact`

    ![](note%20-%20image/GAMES202/13.png)
  * 切比雪夫不等式本身的问题：$t$ 在均值右侧才比较准确
* MSM - 改进了 VSSM 中分布描述不准确的问题
  * `higher order moment` 用更高阶的`矩`描述分布
  * 四阶矩，如：$x$、$x^2$、$x^3$、$x^4$。 VSSM 中用了二阶，用更高阶的去描述。
  * `结论`：前 $m$ 阶矩可以表示 $\frac{m}{2}$ 个台阶的函数。通常四阶可以比较准确地描述深度图的 CDF。

    ![](note%20-%20image/GAMES202/14.png)
  * `给定四阶矩如何计算 CDF`：详见论文 Peters et al. *Moment Shadow Mapping*
* 工业界技巧
  * `packing` & `unpacking`，一个 32bit 的值按位拆开存不同的量。（是不是在哪见过……不过感觉和一张纹理不同通道的复用也差不多？总之勤俭持家就完事了=。=）问题：难以插值

## 各种 CSM
* 没了没了大概是不提了吧
  * Cascaded shadow map
  * Convelutional shadow mapping
  * Compressed shadow map

## Distance field soft shadows（in Lecture 5）
* 有向距离场 Signed Distance Field（SDF）
  * 回忆 Distance functions：定义空间中任意一点，`到某物体表面的（最近点的）距离`。若对物体内部/外部取不同的符号，则为有向距离。
  * “做任意形状的插值”
* Usage 1 - 已知整个场景的 SDF，用光线和其定义的隐含表面求交：`sphere tracing`
  * 某点的 SDF 值隐含意义 ①：`以该点为球心，附近最大安全距离`
  * 因此从光线起点开始，往发射方向不断地走该安全距离（每走一次更新起点），取所有安全球最小半径，直到 hit 物体或走了很远也 hit 不到东西
* Usage 2 - 生成软阴影
  * 某点的 SDF 值隐含意义 ②：`穿过该点的光线，偏多大的角度以内是安全的`（光线起点到安全球的切线）
  * 这个`安全角度越小`，能够看到的东西越少，阴影越黑。（就是如果偏一点点就会被东西遮挡的话那这东西后面肯定就是有阴影的）用该角度值作为 visibility。

    ![](note%20-%20image/GAMES202/15.png)

    即安全角 $\arcsin \frac{SDF(p)}{|OP|}$
  * `安全角计算` tips：在 shader 中尽量避免复杂计算，所以不要用反三角函数，又因为当 $x$ 较小时有 $\arcsin x \approx x$，取

    $$ \theta = min\{ k \cdot \frac{SDF(p)}{|OP|}, 1.0\} $$
    * $k$ 变大时会将安全角的影响放大，用来控制软阴影的程度
  * 不能确定安全角的限制具体出现在哪个方向（二维情况下两根切线，三维情况下一个环）
* 局限性
  * 需要预计算
  * 存储需求很大（三维信息）：可以存在场景管理数据结构里，对于非叶子结点不需要特别精确的信息，所以就只维护叶子结点的 SDF
  * 运动、形变的物体要重新算 SDF
  * 接缝处的 artifact
  * SDF 生成的物体（【？】指阴影吗）表面难以参数化，难贴纹理
  * 阴影比 PCSS 还假，因为近似更大胆（……确实很大胆？貌似理论上要 $x < 0.1$ 才成立的
* 安利时间：[github - troika](https://github.com/protectwise/troika) SDF 字符

# Lecture 5 - Real-time Environment Mapping
## `Shading` from Environment Lighting
### Image-Based Lighting（IBL）
* 认为环境光从无限远处发射，所以在场景中放东西会很飘
* 存储：cube/spherical map
* 俗名 Image-Based Lighting（IBL）
* 给出 IBL，着色（即解渲染方程）

    $$ L_o(p, \omega_o) = \int_{\Omega^+} L_i(p, \omega_i) f_r(p, \omega_i, \omega_o) \ cos\theta_i\ d\omega_i $$
    * 其中 $V(p, \omega_i)$ 阴影部分暂不考虑
* 解法
  * 一：通用法蒙特卡洛，但要大量采样才能收敛，一般来说在 shader 中用了采样就不考虑这个算法能用在实时领域。但！是！由于现在图像降噪很强所以不一定。（？突然想到那篇 Recurrent Denoising Autoencoder 降噪蒙特卡洛结果的……原来如此……怪不得 SIGGRAPH 上那么多跟蒙特卡洛硬刚降噪的……）
  * 二：努力避免采样……
### Split sum approximation 1 - 光照项 $L_i$
* 基本思路
  * 考虑渲染方程的 $L_i$ 和 BRDF 项，观察
    * 当 BRDF 是高光时，其出射方向区域范围小，即该入射光对着色结果的贡献小。
    * 当 BRDF 是漫反射时，往四面八方反射，但不同方向的过渡比较平滑（乘 $cos$）
  * `经 典 近 似`

    $$ \int_{\Omega} f(x)g(x) dx \approx \frac{\int_{\Omega_G\ f(x)\ dx}}{\int_{\Omega_G} dx} \cdot \int_{\Omega}\ g(x)\ dx $$
    $$ \Downarrow $$
    $$ L_o(p, \omega_o) \approx \frac{\int_{\Omega_{f_r}\ L_i(p, \omega_i)\ d\omega_i}}{\int_{\Omega_{f_r} d\omega_i}} \cdot \int_{\Omega^+}\ f_r(p, \omega_i, \omega_o)\ cos\theta_i\ d\omega_i $$
    * 其中 $\Omega_G$ 指 $g(x)$ 即 BRDF 的 support 范围
    * BRDF 为高光或漫反射时，分别满足该近似成立的条件其中之一（妙啊！！！！！！！！）
  * 把光照部分拆出来之后，也就是需要`影响某点的半球范围内光照均值`。也即 IBL 贴图模糊的结果：任意一点，取附近范围的均值并写回该点。
    * 预处理不同 filter size 的模糊图
    * 注意是`在球面上做 filter`，取不同的立体角，映射到 IBL 上
    * 使用的时候可以类似 MIPMAP 的三线性插值
* 对 IBL 贴图做模糊的正确性解释

    ![](note%20-%20image/GAMES202/16.png)
  * BRDF glossy 情况下，在 BRDF 的贡献范围内采样取均值，与事先在 IBL 上模糊得均值，效果类似
  * 漫反射可以用 normal 方向上的均值
### Split sum approximation 2 - BRDF 项 $f_r$
* 基本思路
  * 假设是 Microfacet BRDF，预计算需要至少五维信息，参数空间很大，就算预计算也承受不来
    * 用于决定 NDC 的一维 roughness $\alpha$
    * fresnel term：基础反射率 $R_0$（三通道 RGB）、在不同入射角 $\theta_h$ 下的曲线
  * `实时中能互换的角（近似角？）`：入射角、出射角、入射出射夹角的一半、入射或出射对半程向量 half vector 的夹角
  * 把基础反射率 $R_0$ 看成一个灰度 $\Rightarrow$ 三维预计算
  * 继续降维，试图把某个参数拆出去：把菲涅尔项用 Schlick 近似展开
    $$ R(\theta) = R_0 + (1-R_0)(1-cos\theta)^5 $$
    $$ \int_{\Omega^+}f_r(p, \omega_i, \omega_o)\ cos\theta_i\ d\omega_i \approx R_0\ \int_{\Omega^+}\frac{f_r}{F}(1-(1-cos\theta_i)^5)\ cos\theta_i\ d\omega_i + \int_{\Omega^+}\frac{f_r}{F}(1-cos\theta_i)^5\ cos\theta_i\ d\omega_i $$
  * 此时影响该积分值的参数只剩入射角 $\theta$ 和 roughness，打表！上纹理！
* 对于同一种 BRDF 都是同一张表
* Chatting time
  * 因为实时里通常把积分写成求和形式，所以叫 split sum（噗
  * 该方法用于 UE 的 PBR（ooops！
* 更好的方法：Linear cosine transform（LTC，应该是 SIGGRAPH 2016 的这篇 [*Real-Time Polygonal-Light Shading with Linearly Transformed Cosines*](https://eheitzresearch.wordpress.com/415-2/)？）

## `Shadow` from Environment Lighting（in Lecture 6）
* 实际上并做不到 :)
* 解决思路
  * 把环境光看成是 a many-light problem：按照多光源的做法，对每个光源都要生成一张 shadow map，是按光源数量呈线性级，显然无法接受。
  * a sampling problem：采样求解渲染方程，但是 visibility 项在不同方向上差别很大，且环境光的 support 范围针对一个 shading point 是整个半球，积分范围很大，以及 BRDF 项不低平，不满足 visibility 项的拆分条件，难整
    * 环境光遮蔽 environment occlusion 做出了近似，但条件是 constant environment lighting 
* 当前工业界主流方法：从环境光中只聚焦主要的光照来源（如野外的太阳）
* Related research
  * Imperfect shadow maps（全局光照相关）
  * Light cuts（离线）：把场景中的反射物作为小光源，归类，并做近似（从 many-light 角度出发）
  * Real-Time Ray Tracing
  * Precomputed radiance transfer

# Lecture 6 - Real-Time Environment Mapping（Precomputed Radiance Transfer）
* Precomputed Radiance Transfer（PRT），可以用于环境光以及全局光照

## 基本数学知识（GAMES101 回顾）
* 傅里叶级数展开
* 频域与频谱
  * 自然照片大部分信号为低频
  * 时域卷积 = 在原始函数上卷积 = 在频域上做乘积
* A general understanding
  * 将`两个函数相乘并积分`的操作认为是卷积操作，具有滤波意义
  * 乘积的频率由二者中更低的一方决定
* 基函数：用一系列函数的线性组合描述一个新的函数
    $$ f(x) = \sum_i c_i \cdot B_i(x) $$
    * Fourier series
    * Polynomial series

## Spherical Harmonics
* Spherical Harmonics
  * 一系列`二维`、`定义在球面上`的`基函数`
  * 可以认为是二维极坐标（$\theta$、$\phi$）表示的三维方向
  * 性质类似一维情况下的傅里叶级数（可以拆分为不同频率的 sin、cos），可以将最低频到最高频描述出来
* 球谐函数的可视化

    ![](note%20-%20image/GAMES202/17.png)
    * 在第 $l$ 层定义了 $2l+1$ 个函数
    * 第 $l$ 层也称为 $l$ 阶
    * 每阶的函数分别编号为 $m=-l$ 至 $m=l$
    * 前 $n$ 阶共有 $n^2$ 个函数
* 为什么不把三维球面展开到二维再用傅里叶级数求解和近似：求完反推回去会裂开（
  * 而 SH 本来就定义在球面上的任意方向，是连续的，适合用来直接分析球面上函数的性质
* 每个球谐基函数 $B_i(\omega)$ 用一个`勒让德多项式`（Legendre Polynomial）描述
* **`投影 Projection`** - 用基函数 $B_i(\omega)$ 表示某函数 $f(\omega)$ 时，求该基函数的系数的过程：两个函数对应位置逐点相乘再作积分
    $$ c_i = \int_{\Omega} f(\omega)B_i(\omega)\ d\omega $$
* **`Reconstruction`** - 用基函数及相应系数恢复原函数
  * 只需要用部分阶数，恢复出特征最突出的部分的原函数即可
* Q & A
  * 可以认为环境光 environment map 是一个描述了环境光的二维函数，投影到每个基函数得到一个值
  * 通常取前 $n$ 阶并将其中的所有基函数都用上
  * 投影积分的求法：采样/预计算
  * product integral 的本质就是点乘

## 用球谐函数解决 diffuse 物体的环境光 shading 问题
* Recall Prefiltering：即对环境光贴图做模糊
* `Consider 1` - 考虑对 diffuse 物体求环境光部分的 shading 式子：
  * Lighting - 来自 environment mapping，是一个定义在球面上的函数
  * BRDF - 定义在整个半球上的光滑函数，当物体是 diffuse 时，类似一个低通滤波器，大部分为低频，可以用较少阶（三阶）的 SH 就能描述。（取前几阶球谐基函数作投影，高阶部分的投影系数基本为 $0$，即没有高阶部分对应的高频信息）
  * 二者做 product integral 操作
* `Consider 2` - 又已知 product integral 中[`乘积的频率由二者中更低的一方决定`](#基本数学知识games101-回顾)，所以无论环境光频率多高，只要照射到 diffuse 物体上，最终结果基本都是低频的
* `Consider 3` - 于是考虑用几阶的球谐函数去表示光照：从一阶测起，看效果如何，且可以定量从 `RMS error` 的角度取得数值结果。
  
  <!-- * 一阶、二阶、三阶结果如图 -->

    <!-- ![](note%20-%20image/GAMES202/18.png) -->
    <!-- ![](note%20-%20image/GAMES202/19.png) -->
    <!-- ![](note%20-%20image/GAMES202/20.png) -->
    
  * 最终得出：任意环境光，只要物体是 diffuse，都能用三阶以内表示光照并得到不错的效果
* `Conclusion`：分析 BRDF 的频率，决定用几阶的函数近似光照
* Chatting time
  * 最后得到与法线相关的 $E(n) = n^tMn$
  * （两行代码拿博士学位并开创了 PRT 时代 orz

## Precomputed Radiance Transfer（PRT） - Idea & Diffuse
* 将渲染方程中的 lighting、visibility、BRDF 都用一张 mapping 表示

    $$ L(o) = \int_\Omega L(i)\ V(i)\ f_r(i, o)\ max(0, \overrightarrow{n}\cdot\overrightarrow{i})\ d_i $$
  * $L(i)$ - 即 environment map

    ![](note%20-%20image/GAMES202/21.png)
  * $V(i)$ - 从当前的 shading point 往各方向看，所得的遮挡贴图（【？】突然迷惑 visibility term 是不是只是实时渲染里考虑阴影的时候另外加的？原始 rendering equation 里没有的吧……好像也不是哪个项变化出来的……？lighting、BRDF、cos、$d\omega$ 看着都挺完整啊 orz... [CS348B - Lecture 13 - page 8](http://graphics.stanford.edu/courses/cs348b-10/lectures/renderingequation/renderingequation.pdf) 这疑似有个解释但没看懂怎么来的 orz（阿巴阿巴这课竟然是 PBR 那两位作者开的卧槽好羡慕……

    ![](note%20-%20image/GAMES202/22.png)
  * $f_r(i,o)$ - 本身是四维量，给定 $o$ 出射/观察方向，剩下的 $i$ 为二维，也能描述成一个球面函数（【？】怎么就四维二维【check】应该是指 $\omega_i$、$\omega_o$ 都是立体角，所以实际上是要用两个弧度量来表示，得到一个具体的三维方向？立体角 Solid Angle 转球形角 Sphere Angle：$d\omega = sin\theta\ d\theta\ d\phi$）

    ![](note%20-%20image/GAMES202/23.png)
* 简 单 粗 暴：每个 shading point 存表示三个项的 mapping 表示其球面函数，并遍历其中所有像素求乘积（迅 速 去 世
* 注意此时考虑了 visibility，带 shadow
* Paper SIGGRAPH 2002 by Sloan - *Precomputed Radiance Transfer for Real-Time Rendering in Dynamic, Low-Frequency Lighting Environments*
* **`Basic idea of PRT`**

    ![](note%20-%20image/GAMES202/24.png)
  * 假设：场景中只有光照发生改变。将渲染方程看作 lighting、light transport（除光照外的剩余项） 两部分
  * Step 1 - `用基函数表示 lighting 项`
    $$ L(\bold{i}) \approx \sum\ l_i\ B_i(\bold{i}) $$
  * Step 2 - `预计算 light transport 项`：由于假设了该部分不变，① 可看作当前 shading point 本身的一个属性，所以提前算出来；② 整体也是一个球面函数，也可以用基函数表示
  * Step 3 - 运行时 diffuse 物体做点乘，glossy 物体作 matrix-vector multiplication
    * diffuse 情况：

        ![](note%20-%20image/GAMES202/25.png)
      * ① BRDF 为常数（$k_d$），直接提出积分。
      * ② $L(i)$ 用基函数及系数表示后代入
      * ③ 交换求和与积分号（目前除了 differentiable rendering 以外，渲染领域都不考虑什么情况下能交换，摁换就完事了（
      * ④ 惊奇地发现用来表示 $L(i)$ 的基函数和 light transport 拼起来了！也就是 `light transport 投影到各个基函数上的系数`（可以看作是用基函数代替了 lighting 项，即“用该基函数所描述的环境光照，照亮该物体”[Lecture 6 - 93:14]）
      * ⑤ 最终求 shading + shadow 的时候只要对 $l_i$、$T_i$ 求点乘即可
      * ④ 另一条途径：直接将两部分都用基函数表示，在积分中展开，转化为双重求和问题，每一项为两个系数与积分值的乘积。
            
        ![](note%20-%20image/GAMES202/26.png)
        * 此时由于基函数的正交性质，当且仅当 $p=q$ 积分值为 $1$ 需要计算，其它情况积分值都为 $0$，所以复杂度还是 $O(n)$
    * glossy 情况：（in Lecture 7）
  * `Tips`
    * 基于只有光照改变的假设，所以场景中物体不能动，保证各 shading point 的 visibility term 保持不变
    * 由于预计算了 lighting term 的 environment mapping，对于换光源的情况可以通过换贴图解决。对于相同光源做旋转，利用球谐函数的旋转不变性处理，可以直接得到旋转后的相应系数。
* Q&A
  * Q：旋转光照不会影响 visibility term 吗？  
    A：不影响。  
    【？】这旋转是不是指光源自身的 rotation？而不是在世界坐标系下绕什么东西转了一下导致自身的 position 发生变化？【？？？】晕了，指哪种转 orz...
  * Q：物体变化的情况能处理吗  
    A：能，有相关研究方向
  * Q：随时间变化的程序纹理的环境光  
    A：无法通过这种预计算的方式做
  * Q：任意点的 visibility map 如何得到？  
    A：可以认为从 shading point 发射很多光线 trace 得到，预计算的时间充裕（编译时间）

## 球谐函数的性质 Properties of Spherical Harmonics
* `正交性` orthonormal：将一个基函数投影到其它基函数，系数为 $0$
    $$ \int_\Omega B_i(\bold{i})\cdot B_j(\bold{i})\ d_i = 1 (i = j) $$
    $$ \int_\Omega B_i(\bold{i})\cdot B_j(\bold{i})\ d_i = 1 (i \neq j) $$
* simple projection/reconstruction：任意球面函数投影到基函数即做 product integral
* **`旋转不变性`** simple rotation：旋转任意一个 SH Basis 函数的结果，都可以由同阶的基函数的线性组合得到
  * 所以光源旋转情况的处理：  
    光源旋转  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; $\Downarrow$  
    lighting mapping 定义的球面函数旋转（因为是由光源得到的）  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; $\Downarrow$  
    用来表示该球面函数的基函数旋转（感觉可以类比坐标系的相对旋转=。=）
  * 于是又可以打表：对某基函数的旋转，相当于`做一次对同阶基函数系数的更改`
* 更自然的处理：将光线的多次弹射当做一种 light transport 的方式，并预计算 [Lecture 6 - 约 95:00]

# Lecture 7 - Real-time Global Illumination (in 3D)
## Precomputed Radiance Transfer（PRT） - Glossy
* **`Basic idea of PRT`**

    ![](note%20-%20image/GAMES202/24.png)
  * 假设：场景中只有光照发生改变。将渲染方程看作 lighting、light transport（除光照外的剩余项） 两部分
  * Step 1 - `用基函数表示 lighting 项`
    $$ L(\bold{i}) \approx \sum\ l_i\ B_i(\bold{i}) $$
  * Step 2 - `预计算 light transport 项`
  * Step 3 - glossy 物体作 matrix-vector multiplication
    * diffuse 情况：in Lecture 6
    * glossy 情况：不同的观察方向 $o$ 会产生不同的 BRDF，也即产生不同的 light transport 项和不同的投影结果（投影结果仍然是关于观察方向 $o$ 的函数，即一向量，而非定值），=> 把该投影结果再投影到基函数，此时得到的系数即为一系数矩阵，行列头分别为其中一层投影
        
        ![](note%20-%20image/GAMES202/27.png)
        * 此时存储需求 up，最终计算从点乘（16）变成向量矩阵乘（vector16 * matrix(16*16)），开销也 up
        * 直播现场 discuss：当 glossy 频率非常大（接近镜面反射），低阶基函数的近似描述与实际相差很远时，PRT 无法解决，可以直接 ray tracing 了 2333
* **`Interreflection`**：把多次反射当做 light transport 的一部分，预计算部分间接弹射
  * 科普：实时中把材质分为 diffuse、glossy、specular 镜面反射三类
  * 科普：三类材质加 Light、Eye，给光线传播路径分类
    * LE：L(D|G)*E
    * LGE：LS*(D|G)*E
    * 如 caustics 路径为 LSDE
  * 根据 PRT 思想把 Light 和 light transport 分离，中间传播的 transport 预计算后最终运行时间与 transport 有多复杂无关，所以能计算任意复杂的 trans 路径
  * 考虑只替换 Light 部分时的理解：“用基函数所描述的环境光照，照亮该物体”，
* 局限性小结
  * SH 自身特性：不适合表示太高频的信息
  * 预计算缺陷：适用于静态场景和材质
  * 大量预计算数据的存取
* Follow up works
  * 不用 SH，用其它的基函数
  * 把 light transport 进一步拆分成 BRDF、visibility
  * 试图让静态场景、几何、材质可以略作变化
  * 应用到更多的高级材质如 translucent、hair...
  * 试图不做预计算，求解析解 precomputation => analytic computation
* Q&A
  * 预计算时选取的观察方向：随机 grid
  * 目前的 DXR 可以结合在光栅化里做实时 rt
  * 预计算的结果可以看成材质的一部分内容
## More basis functions
* Wavelet（Haar，有多种）
  * SH 定义在球面上，小波定义在图块上
  * SH 取部分阶压缩信息，小波的投影大部分接近或为 $0$，取系数较大的部分项，保留高频信息
    
    ![](note%20-%20image/GAMES202/28.png)
    * 递归地对左上低频信息做多次小波变换，高度压缩
    * 科普：JPEG 格式图片用的压缩方式类似小波变换，为离散余弦变换（DCT）
  * 比 SH 的优越处：在频率高低方面没有局限性
  * 2D 表示球面函数有缝 => 不用 spherical map，用 cubemap
  * 局限性：没有 SH 的旋转不变性，不支持光照快速旋转
* Zonal Harmonics
* Spherical Gaussian（SG）
* Piecewise Constant
## More information
* [Ravi PRT survey - `Precomputation-Based Rendering`](https://sites.cs.ucsb.edu/~lingqi/teaching/games202.html)

## Real-Time Global Illumination（in 3D/world space）
### Chatting time
* GI survey - The state of the art in interactive global illumination
  * 科普：该 survey 的 teaser image（秀本文操作的绝美结果图）

    ![](note%20-%20image/GAMES202/29.png)
  * 简单地用 ambient 摁提亮度的 hack 不能解决 GI 问题，因为实际上复杂场景中的各处亮度差别很大。如上图书本下方右侧的一些 caustics。
* recap: primary/secondary light source

### Reflective Shadow Maps（RSM）
* 渲染被次级光源（secondary light source）照亮所需知道的信息
  * `次级光源` secondary light source：即被 primary light source 照亮的区域，看作一块块 surface patch
  * `各次级光源对当前 shading point 的贡献`：把各 surface patch 看作面光源 area light —— path tracing, 采样
* **`Step 1 - 求 secondary light source 及其出射能量`**
  * 次级光源即 shadow map 中各 texel（surface patch）
  * 对直接渲染即不考虑 GI 的情况：出射方向即 camera。此处要考虑间接光照，但在实际 shading 之前不确定出射方向 —— 
  * **`Assumption`**：反射物均为 diffuse（注意接收物不限制，因为只需在此处考虑次级光源的出射方向）
  * 则各出射方向的出射能量相同
* **`Step 2 - 求贡献（先考虑单个 texel surface patch 对当前 shading point 的贡献）`**
  * recap：area light 对 shading point 的贡献需要在计算时采样，但在 shading point 上采样入射方向的有效性低，因为只有能到达光源的采样方向才是有贡献的，可以反向直接在光源上采样。那么当前 shading point 来自单个 texel surface patch 的入射贡献就是 $L_i(q\rightarrow p)$ 
  * 将对单位立体角的积分换元成对微表面积的积分

    ![](note%20-%20image/GAMES202/30.png)
  * `近似`：当微表面极小时，在积分范围中任取一点代入求出式中各项值作为积分值的近似
  * `求解` one diffuse reflective patch 即 $L_i(q\rightarrow p)$
    $$ \begin{aligned}
        f_{r_q} &= \frac{\rho}{\pi} \\
        L_i &= f_{r_q}\cdot Radiance_{o_q}(=\frac{\Phi}{dA})
    \end{aligned} $$
    * 其中 radiance 给出的分母上的 $dA$ 与积分式抵消
    * 实际只需 BRDF 及 incident flux 的信息来求出 reflected flux
  * `问题`
    * 次级光源到 shading point 的 visibility 不好算：啊这？就不算了？
  * `剪枝`
    * visibility（但，难算）
    * orientation：部分次级光源从方向上就显然不会对当前 shading point 结果产生贡献
    * distance：较远的次级光源经衰减后贡献很小，可以只考虑 shading point 附近的次级光源。就近次级光源：又见大胆假设！把 shading point 投影到 shadow map 上，取附近 or 深度相近的认为是附近次级光源
  * `RSM 对 shadow map 的 record 信息需求`
    * depth
    * world coordinate
    * normal：计算 cos 项
    * flux
* 总结
  * Pros
    * 容易实现，基于 shadow map
  * Cons
    * 传承自 shadow map 的问题，primary light 较多时 shadow map 数 up，RSM 随之增长
    * 忽略了次级 visibility
    * 各种假设带来的问题
    * 采样率和质量的 tradeoff
* Extra
  * texel surface patch 类似于离线渲染中的 virtual point light（VPL）方法（Instant Radiosity 即时辐射度）
  * 关于 RSM 从技术来说基于 shadow map 是图像空间的做法（在第一个 pass 中将场景信息记录到纹理图像），这里归为 3D 是考虑到其不会在记录信息时丢失信息（图像空间做法的常见问题）

### Light Propagation Volumes（LPV）（in Lecture 8）
* 基于 RSM
* Chatting time
  * LPV first introduced in CryEngine 3 （Crysis 孤岛危机（显卡危机
  * by Anton Kaplanyan
* Key：`Query the radiance from any direction at any shading point`
* Idea：`Radiance travels in a straight line and does not change`
  * 沿直线传播
  * 定值
  * 注：平方衰减的是 intensity，定义在单位面积上。而 radiance 定义在直线上。
* Solution：把场景划分为网格 grid
  * Step 1 - Generation（求次级光源，同 RSM）
  * Step 2 - Injection（把场景信息，即`各次级光源接收到的直接光照`，注入到 `3D grid`）
    * 可用三维纹理
    * 对每个 grid cell，计算其内部所有 virtual light sources 总和
    * 得到各 grid cell 朝各方向的 radiance distribution
    * 对该分布用 SH 做压缩（工业界：前两阶）
    * `得到 indirect radiance 初值`
  * Step 3 - Propagation 传播
    * 对每个 grid cell，把 radiance 按照其穿透 face 的方向传播到邻近的 6 cells【？诶是不是有状态转移内味儿了】
    * 传播后在其它 cell 中仍旧用 SH 表示
    * 迭代到 volume 稳定（约四五次）
  * Step 4 - Rendering
    * 把 shading point 定位到相应的 grid cell
    * 取其 incident radiance 
    * 着色计算
* Problem
  * Light leaking：grid 粒度不够细密，物体比 grid 粒度小的话，背面背光处在 shading 时可能会由于 grid 过大取到正面处的 incident radiance 导致背面亮度过大
  * 但 grid 粒度太细就有存储过大和 propagation 过程计算量太大的问题
* Q&A
  * propagation 过程中不考虑 visibility
  * propagation 不直接传播给斜对角 grid，因为会通过邻近的间接一步传过去
  * grid 粒度问题：自适应 or 分层（cascade/level of detail/multi scale）
  * 三维纹理：一般至少比 pixel 少一个数量级

# Lecture 8 - Real-Time Global Illumination (Screen Space)
## Real-Time Global Illumination（in 3D/world space）
### Voxel Global Illumination（VXGI）
* two-pass
* Differences with RSM
  * directly illuminated pixels -> hierarchical voxels：次级光源由像素 surface patch 改成体素，建立层级树形结构
  * sampling on RSM -> 支持反射物可以是 glossy：从 camera 出发渲染场景，tracing reflected cone 
* Pass 1 - `Light pass`
  * 在 voxel 中存储 incident radiance、light direction、normal
  * 记录照亮该 voxel 的直接光的方向分布、voxel 中的各反射表面的法线分布，求出出射的分布
  * 整合到高层
* Pass 2 - `Camera pass`
  * 渲染 glossy pixel 时
    * 往反射方向作 cone tracing
    * 认为该反射 cone 内的体素都对当前 shading point 有贡献
    * cone 与 voxel 求交过程中用 hierarchy structure 加速
  * diffuse
    * 整多个小圆锥

## Real-Time Global Illumination（Screen Space）
* screen space
  * using information only from 'the screen' or post processing on existing renderings
    * information：`the direct light rendering results`
  * （ATTENTION：RSM image space）

### Screen Space Ambient Occlusion（SSAO）
* Chatting time
  * SSAO first introduced by Crytek
  * 效果：物体之间接触部分的深阴影 contact shadow，加深空间立体感
  * 科普：三维建模（离线渲染）软件中称 AO 为天光
* SSAO 环境光遮蔽
  * an `approximation` of GI
  * in screen space
* `Key Idea`
  * 不计算间接光照，假设 ① `各方向 incident lighting 都相同`（类似 blinn-phong ambient），即 $L_i$ 定值
  * 但不同 shading point 各方向上 `visibility 不同`
  * 假设 ② 物体 diffuse，即 $f_r = \frac{\rho}{\pi}$ 为定值
* Theory（数学原理）
  * according to the approximation

    ![](note%20-%20image/GAMES202/31.png)
  * separating the visibility term

    ![](note%20-%20image/GAMES202/32.png)
    * 插播微积分紧急复习：$d\omega_i$ 换元 $sin\theta d\theta d\phi$
    * 【？】怎么 cos 也跟出来了，拼一起能换元？【check】确实w，见 projected solid angle。
    * 拆出的 $k_A$ 项代表任意 shading point 往各方向 visibility 关于 $cos$ 项的加权平均值（【？】但 $cos = \overrightarrow{n}\cdot \overrightarrow{\omega_i}$，就……看起来仿佛疑似又有那么一点物理意义？）
    * 剩余的 $L_i$、BRDF 由假设 ①、② 易求都是常数，且符合该拆项近似的 accurate 条件（constant 即 smooth）
  * 【！】不得了，感觉自己大脑突触有所发育（不
  * `Projected solid angle`：$d_{x_\perp} = cos\theta_i\ d\omega_i$ 将半球表面的表面微元投影到其下的单位圆

    ![](note%20-%20image/GAMES202/33.png)
    * 科普：$\LaTeX$ 中正规微分符号写法 $\,\mathrm{d}$ - 最小空格加 \mathrm（\$\\,\mathrm{d}\$）（此处敲出正规的 $\LaTeX$ 向严谨致敬！）
  * 另一角度，从两个假设所得的常量出发直接提到积分之外可得

    ![](note%20-%20image/GAMES202/34.png)
    * 但此时积分内剩余的部分不是关于 cos 的均值
* `implement`
  * in world space: ray tracing，但慢
    * AO approximation：limited radius，限制 trace 半径
  * in screen space?（SSAO）
    * Step 1 - `在 shading point 为中心的球体内随机取点`
    * Step 2 - `判断随机点是否在物体内部`，大胆假设：假装 camera 看不到就 shading point 也看不到，与深度图信息比较（【？】所以如果只是有物体把什么反射面挡住了的情况那这个反射面的贡献就算不到了吧【check】芜湖确实

        ![](note%20-%20image/GAMES202/35.png)
    * 考虑整个半球的原因：当年不能保证可以得到法线（弹幕：现在的 SSAO 会考虑半球）
      * 此时`当不可见点超过半数时才考虑 AO`，即认为该情况下表示所需半球也有不可见点
      * 没有考虑 cos 项
* 问题
  * 会出现不该有的遮挡 false occlusion

    ![](note%20-%20image/GAMES202/36.png)
  * 现在能得到法线，就在半球上整：HBAO，考虑的遮挡范围也有优化，减轻了一些 false occlusion

### Screen Space Directional Occlusion（SSDO）（in Lecture 9）
* SSDO 屏幕空间方向性遮挡
  * 对 SSAO 的改进
  * 考虑次级光源，在 occlusion 部分不止是变暗，而且加深的阴影部分带上次级光源的颜色

    ![](note%20-%20image/GAMES202/37.png)
* `Idea`
  * 不假设 uniform incident indirect lighting
  * 考虑来自 directional light 结果的次级光源信息
* 做法（类似 path tracing）
  * 次级光源信息来自渲染好的图像信息
  * 计算某点 p 时：
    * 从 p 点发射光线，未遇到障碍物，直接光照
    * 遇到障碍物，加上间接光
* SSAO/DO 对比（间接光的假设来源不同）
  * AO：假设任意点可接收四周间接光照（间接光来自很远的地方），考虑四周有障碍物的方向接收不到的情况
  * DO：假设任意点没有间接光，有障碍物的方向上传来该障碍物反射的光（假设间接光打到其它障碍物才产生，来自很近的地方）
  * 障碍物的距离是小范围
  * 所以理论上应该结合 AO/DO，分别考虑远处/近处的间接光
* 采样方法 Lecture9 - 00:19:15
  * 考虑着色点 p 所在的半球内随机采样
  * 避免 trace 光线，将 p 到采样点 A 的可见性转化为 camera 到渲染成图像后的 A 的映射点的可见性（一种假设，当两种可见性不同时会有大问题（
    
    ![](note%20-%20image/GAMES202/38.png)
* 总结
  * 优势：效果尚可
  * 问题
    * 只能表示小范围的间接光
    * visibility 部分判断的是 camera 到这些点的可见性，准确性不足
    * screen space：间接光来自图像空间（视野场景内最浅的深度），缺失了从 camera 看不见的表面的信息

    ![](note%20-%20image/GAMES202/39.png)
    
# Lecture 9 - Real-Time Global Illumination（Screen Space cont.）
### Screen Space Reflection（SSR）
* SSR 屏幕空间反射
  * 在屏幕空间做 ray tracing（在近表面的球壳上做 ray tracing；可以写在 shader 里加速）
  * 不需要三维几何信息（同样只从屏幕空间获取）
* 解决的问题
  * 计算交点：对任意从 camera 出发的光线，与场景（屏幕空间下的）求交
  * 着色：求交点对着色点的贡献
* ① 求交
  * 考虑：反射的内容`大部分`来自“去掉反射后”场景中已有的内容
  * 已知屏幕空间
    * 场景渲染结果
    * normal map
    * depth map
    * 求：具有反射的部分的反射结果
  * 在反射面上取点，从其深度开始，步进式减小其深度，看该深度是否小于视野场景某点的深度
  * 动态决定步长：对深度图做 mipmap，但过程中不取均值而取深度的最小值（类似三维中的 BVH/KD-Tree。设上层为小一维度的深度图，其值为下层四个像素的最小深度（最浅）。则如果光线连最浅的那个像素都无法相交，那必然也无法与下一层该处其它像素相交。动态步长：每次步长是往下一层/上一层走）[00:48:00]
* 问题
  * screen space：由于 tracing 数据只来自屏幕，所以除了“表面”的信息，深度更大的几何信息丢失了，所得的反射结果也就不存在

    ![](note%20-%20image/GAMES202/40.png)
  * edge cutoff：超出屏幕的部分断层式消失 -> 改进为 edge fading，根据反射距离逐渐虚化
* ② 着色
  * 同样假设作为次级光源的部分都是 diffuse 的（反射到 camera 与反射到 shading point 的颜色相同，前者为屏幕空间能得到的信息，后者为着色的入射项 $L_i$）
* 问题
  * 有没有距离平方衰减？No. 从 shading point 做 tracing，没有对次级光源的 area 做积分算贡献。不定义在面积上，就不会因为距离衰减。（BRDF sampling 都不存在平方衰减的问题，而 light sampling 一定会有）
* 自然地达到以下现象
  * sharp and blurry reflections（BRDF 不同导致的反射清晰度）
  * contact hardening shadow 接触硬化阴影（越近的物体反射结果越清晰）
  * specular elongation（反射物体上下拉长）
  * per-pixel roughness and normal
* approach
  * BRDF 重要性采样
  * hit point 复用：一个交点对多个 shading point 有贡献（需要多次 trace）时
  * 对屏幕空间结果 prefilter 时，由于其含有明确的深度信息，要考虑深度之间的关系（深度差别很大的像素不能直接均值，即前后景关系不能混乱，另外深度本身不能混合）（GI 中环境光认为从无穷远处来，不影响）

# Lecture 10 - Real-time Physically-based Materials(surface models)
* PBR materials in RTR
  * 表面：微表面模型（根据使用情况，有时其实不是真正的 PBR）、disney principled BRDF（艺术家友好，轻量，然而并不 PBR）
  * 体积：云雾烟，头发皮肤
## 微表面模型 Microfacet BRDF
* 微表面把 $\omega_i$ 反射到 $\omega_o$ 方向上

    ![](note%20-%20image/GAMES202/41.png)
* ① The Fresnel Term
  * 反射的量取决于入射角度（grazing 掠射，即入射角度近乎垂直于表面法线时，反射量最大。如下图三）

    ![](note%20-%20image/GAMES202/42.png)
  * 决定了反射率。
  * 一般用 Schlick 近似
* ② `Normal Distribution Function（NDF）`
  * 考虑不光滑表面时，可以认为是由光滑表面的法线分布高度场放大变成的

    ![](note%20-%20image/GAMES202/43.png)
    ![](note%20-%20image/GAMES202/44.png)
  * 描述法线分布的常用模型：Beckmann、GGX（、Yan 2014/6/8）
  * 三维法线，由二维球面极坐标描述。可视化时使用 projected solid angle（三维半球压缩成二维平面圆，横纵分别 [-1, 1]）
  * Beckmann 模型（各向同性情况）：形似高斯函数（正态分布的通用解释）

    ![](note%20-%20image/GAMES202/45.png)
    * $\alpha$ 即表面的法线分布 lobe
    * 指数上为什么是 $tan^2$ 不是直接 $\theta_h^2$：因为模型定义在坡度空间 slope space 上。如图圆心为 shading point，过圆心的横线为物体表面，则 shading 时整个上半球都是法线可能分布的方向。微观微表面法线（红色箭头）与宏观法线（黑色箭头）夹角为上式 $\theta_h$。单纯的角度在不限制范围的前提下，当 $\theta_h$ 超过 $90\degree$，法线指向下半球，是有问题的。而在上半圆的切线（推广到三维即上半球的切面）上定义高斯函数（support 无限大，在某处衰减趋近于 0 但不会为 0），直接保证法线角度处于上半球。注：保证微表面法线不朝下，但反射光可能朝下。

        ![](note%20-%20image/GAMES202/46.png)
    * 分母是为了归一化：令该函数在 projected solid angle 域中积分为 $1$。【？】然而这又是为什么=。=【是在球面上的 $cos$ 项和积分两部分整体为 $1$，也即投影为 $1$】
  * GGX 模型（TR, Trowbridge-Reitz）[Walter et al. 2007]
    * 同样形似高斯，但有 long tail 特征

        ![](note%20-%20image/GAMES202/47.png)
    * 长尾特征带来的性质：峰值处对应高光，衰减处有光晕，比 Beckmann 柔和

        ![](note%20-%20image/GAMES202/48.png)
  * Extending GGX [by Brent Burley from WDAS]
    * GTR（Generalized TR）：为 GGX 定义参数 $\gamma$，$\gamma=2$ 时为 GGX，值越大越趋近于 Beckmann，越小尾巴越长
* ③ `Shadowing-Masking/Geometry Term`
  * 解决微表面的自遮挡问题。
  * 其中将“从 light 出发，到达微表面并受到自遮挡问题（光线无法照射到部分微表面）”的部分称为 shadowing，“反射后通往视点过程受到自遮挡问题影响（视点看不到部分微表面）”的部分称为 masking

    ![](note%20-%20image/GAMES202/49.png)
  * 问题主要来自于 grazing angle，由于部分受到遮挡，所以整体所能看到的能量应该要做衰减。考虑不存在 $G$ 项时，为了归一化导致分母中有 $\overrightarrow{n}\cdot \overrightarrow{i}$，接近 grazing angle 时点积趋近于 0，整体结果无限大，体现的结果就是相应位置全白，显然不合理。
  * 常用方法 The Smith shadowing-masking term：假设法线分布，并推出相应的项。其假设 shadowing 与 masking 无关，即 $G(i, o, m) \approx G_1(i, m)G_1(o, m)$（m 为半程向量）

    ![](note%20-%20image/GAMES202/50.png)
* G 项引入了新的问题
  * 白炉测试 The White Furnace Test，看出在不同 roughness 的情况下，照射到物体的能量产生了不同程度的能量损失，不符合能量守恒

    ![](note%20-%20image/GAMES202/51.png)
  * 原因：越粗糙的表面，光线在微表面之间多次弹射的概率越大，其受到自遮挡问题影响的概率也越大
  * 方法
    * 离线：通过模拟把损失的能量加回去（accurate method: Heitz et al. 2016）
    * 实时：考虑“光线被遮挡 = 其会发生下一级 bounce”（The Kulla-Conty Approximation，通过经验性的方式补全多次反射丢失的能量）
### The Kulla-Conty Approximation
* 考虑从某单个方向观察，单次弹射，能够从表面上出来的能量

  ![](note%20-%20image/GAMES202/52.png)

  其中：
  * $\mu = sin\ \theta$
  * 假设各方向入射光 $L_i = 1$
  * 假设微表面 BRDF $f(\mu_o, \mu_i, \phi)$ 为 issotropic 各向同性（$\phi$ 与 $i、o$ 无关）
  * 没有 $cos$ 项：对整个球面立体角 $(\theta, \phi)$ 积分即 $sin\theta \ d\theta \ d\phi$，令 $\mu = sin\theta$。原式 $f_{BRDF} \cdot cos \cdot sin\theta \cdot d\theta\ d\phi$ 变为 $sin\theta\ dsin\theta\ d\phi$，同时变化积分域（sin 的范围 [0, 1]）
* Key idea
  * 从方向 $o$ 观察，光线一次 bounce 损失的能量为 $1-E(\mu_o)$
  * 怎么补：由于可逆，对称应有 $1-E(\mu_i)$，保留要得到的值 $1-E(\mu_o)$，其余未知部分认为是一个系数 $c$ 即有

      $$ \int c(1-E(\mu_i))(1-E(\mu_o)) = 1-E(\mu_o) $$
  * 计算可得

      ![](note%20-%20image/GAMES202/53.png)

      $c=\pi(1-E_{avg})$ 代入验证
      ![](note%20-%20image/GAMES202/54.png)
  * 补在哪里：BRDF 项上，使其表现更真实
* 但 $E_{avg}(\mu_o)=2\int_0^1 E(\mu_i)\mu_i\ d\mu_i$ 过于复杂，类似 split sum：积分复杂不一定有解析解的情况下可以考虑 => 预计算/打表，考虑维度主要是 $\mu_o$ 和 roughness 两个参数，二维纹理表可用
* 对于材料本身就吸收部分能量的情况：加上由于吸收引起的能量损失
  * 定义 `the average Fresnel 项`：对于不同的观察角度，平均其 fresnel term。 fresnel 与 cos 项在球面立体角上进行积分，换元成 $\mu$

    $$ F_{avg} = \frac{\int_0^1 F(\mu)\mu d\mu}{\int_0^1 \mu d\mu} = 2\int_0^1 F(\mu)\mu d\mu $$
  * $E_{avg}$ 为能够观察到的单次弹射的所有能量，也即这部分能量“确定不会发生多次 bounce”
  * 即，最终观察到的能量可分为几部分
    * 直接看到的部分：$F_{avg}E_{avg}$
    * after 1 bounce：$F_{avg}(1-E_{avg}) \cdot F_{avg}E_{avg}$
    * ...
    * after k bounce：$(F_{avg})^k(1-E_{avg})^k \cdot F_{avg}E_{avg}$
    * 相加所得级数，称之为 `the color term`：$\frac{F_{avg}E_{avg}}{1-F_{avg}(1-E_{avg})}$
    * 将该项乘到无颜色的 BRDF 中即可
* 注：所有项都是三维量 (r, g, b)

## Shading Microfacet Models using **`Linearly Transformed Cosines (LTC)`**（Lecture 11）
* LTC：解决了微表面模型的着色问题
  * by Unity research
  * 最初基于 GGX，但可通用
  * 由于解决的是着色问题所以 no shadows
  * `under polygon shaped lighting` 多边形光源：通常在多边形上采样，LTC 不采样
* Key idea
  * 由于已经在着色阶段，所以已知 BRDF lobe。假设该二维 BRDF lobe 可以通过某种线性变换（“在球面上对各个方向做变换”）转化为一个余弦函数。【？】

    ![](note%20-%20image/GAMES202/55.png)
  * 使当前处理的面积光源各顶点随 lobe 同步变化

    ![](note%20-%20image/GAMES202/56.png)
  * 新定义出的面积光源照亮该 shading point 与原来的域中效果相同
  * 解渲染方程的时候就变成了对 cosine lobe 积分，有解析解（analytic）
* 做法

    $$ L(\omega_o) = L_i \cdot \int_P F(\omega_i)\ d\omega_i $$
  * 暂时假设多边形光源上各点发出的能量相同（$L_i$ 在不同方向相同，提出积分）
  * P 为积分域：光源覆盖的立体角范围
  * 原来的方向 $\omega_i$ 用经过变换后的新方向替换，由于变换后可能不在单位球面上，长度发生变化，因此归一化成单位向量

    $$ \omega_i = \frac{M\omega_i'}{|M\omega_i'|} $$
  * 回代

    $$ L(\omega_o) = L_i \cdot \int_P cos(\omega_i')\ d\frac{M\omega_i'}{|M\omega_i'|} $$
  * 换元变域得到有解析解的形式

    $$ L(\omega_o) = L_i \cdot \int_P' cos(\omega_i')\ J\ d\omega_i' $$
* 【？】
  * 怎么求变换 $M$：对常见的 BRDF lobe 预计算，求的时候可以“给定初值，通过优化方法求”
  * 对于有纹理的光源（各点 $L_i$ 不同）：可以作为近似方法
  * 对各向异性表面：可用，虽然 lobe 奇怪点但是不影响映射成 cosine

## Disney principled BRDF
* Motivation
  * 微表面模型不能解释多层复合材质
  * artist 不友好（参数都是物理量）
* Principles
  * 参数是直观的量（粗糙度、饱和度等）
  * 参数尽量少
  * 参数域映射到 [0, 1]（最小最大值）
  * 允许参数超过最值限制
  * 各种组合的情况都应尽可能得到 robust & plausible 的结果
* 实现：拟合了一个能量守恒的模型（详见 open source）

## Non-Photorealistic Rendering（NPR）
* NPR => stylization 风格化
  * 注意实时领域的 fast & reliable
  * （炼丹不能用的原因
* NPR steps
  * photorealistic 的结果出发
  * 对部分作加强/简化：NPR 重点，分析某风格的某现象如何抽象成统一的步骤作实现
* 安利环节
  * Atelier Ryza 2: Lost Legends & the Secret Fairy（莱莎的炼金工坊2）
  * Xenoblade Chronicles 2（异度神剑2 on Switch）
### Outline Rendering（轮廓线）
* 描边 -> 首先定义边 -> 轮廓分类 by RTR

    ![](note%20-%20image/GAMES202/57.png)
  * [B]oundary / border edge：物体边缘轮廓
  * [C]rease：折痕
  * [M]aterial edge
  * [S]ilhouette edge：多面共享的物体边缘轮廓
  * 物体边缘轮廓：在当前视角呈现的图像上的物体边缘
* 方法
  * shading
  * geometry
  * 后期处理
* shading 方法（描 silhouette edge）
  * 观察：该种类型边出现在物体两个面的法线朝向视点、背向视点的交界处，即其 grazing angle 处
  * 作法：shading 时 check 视线方向与 shading point 法线（接近）垂直时认为该点在 S 边上，把它描黑（描边范围根据垂直的范围大小进行控制）
  * 问题：不同位置的法线变化度会导致描边粗细不同
* geometry
  * 考虑：把模型整个扩一圈，渲两个模型
  * 作法：直接把“背向”视点的面放大，或者把顶点沿其法线往外扩一点距离
* 后期处理：图像边缘检测
  * sobel detector
  * 除了最终结果，也可以对中间结果如深度图做边缘检测
### Color blocks
* 色块：阈值化/量化 Quantization

    ![](note%20-%20image/GAMES202/58.png)
  * shading 过程中/最终结果中作限制都可
## Strokes Surface Stylization
* 素描风格：线条浓度体现颜色深浅明暗 => 不同密度的纹理
* Tonal art maps（TAMs）
  * 不同密度的纹理
  * 远近的 uv 放缩会导致密度变化，所以全作 mipmap 且保持密度不变

    ![](note%20-%20image/GAMES202/59.png)


