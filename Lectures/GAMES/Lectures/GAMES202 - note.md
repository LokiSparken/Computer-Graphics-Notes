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
  * [`Shading` from environment lighting](#shading-from-environment-lighting)
    * [Image-Based Lighting（IBL）](#image-based-lightingibl)
    * [Split sum approximation 1 - 光照项 $L_i$](#split-sum-approximation-1---光照项-l_i)
    * [Split sum approximation 2 - BRDF 项 $f_r$](#split-sum-approximation-2---brdf-项-f_r)
  * [`Shadow` from environment lighting](#shadow-from-environment-lighting)

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
## `Shading` from environment lighting
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

## `Shadow` from environment lighting


