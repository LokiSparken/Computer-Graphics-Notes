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
* [Lecture 3 - Real-Time Shadow](#lecture-3---real-time-shadow)
  * [Recap: shadow mapping](#recap-shadow-mapping)
    * [Shadow mapping 做法回顾](#shadow-mapping-做法回顾)
    * [**`Shadow Map 的问题`**](#shadow-map-的问题)
      * [`1. Self Occlusion（采样精度造成的平面纹路）`](#1-self-occlusion采样精度造成的平面纹路)
      * [`2. Aliasing 采样问题`](#2-aliasing-采样问题)
  * [Shadow mapping 的数学原理](#shadow-mapping-的数学原理)
  * [Percentage closer soft shadows（PCSS）](#percentage-closer-soft-shadowspcss)
    * [Percentage Closer Filtering（PCF）](#percentage-closer-filteringpcf)
    * [Percentage Closer Filtering（PCSS）](#percentage-closer-filteringpcss)
* [Lecture 4](#lecture-4)
  * [Basic filtering techniques](#basic-filtering-techniques)
  * [Variance shadow maps（VSM）](#variance-shadow-mapsvsm)
  * [MIPMAP and Summed-Area Variance Shadow Maps](#mipmap-and-summed-area-variance-shadow-maps)
  * [Moment shadow maps（MSM）](#moment-shadow-mapsmsm)
  * [好多 CSM](#好多-csm)

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

# Lecture 3 - Real-Time Shadow
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
  * Step 2 - 对这个范围的测试结果取均值
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

# Lecture 4
## Basic filtering techniques

## Variance shadow maps（VSM）

## MIPMAP and Summed-Area Variance Shadow Maps

## Moment shadow maps（MSM）

## 好多 CSM
Cascaded shadow map

Convelutional shadow mapping

Compressed shadow map
