> # Unreal Engine 4 2020 Mobile Update
> * https://www.bilibili.com/video/BV11a4y1H7jC
> * Author 
>   * Epic Games - Unreal Engine Mobile Team Lead - Jack Porter
>   * Epic Games - Unreal Engine Mobile Rendering Programmer - Dmitriy Dyomin

## 移动端更新情况
### Mobile Platform Trends 移动平台发展趋势
* OpenGL ES -> Vulkan
* 用户期望更高的刷新频率
* 32-bit 减少
  * Google Play 现要求所有应用都有 64-bit 系统版本。
* 支持 ASTC 纹理压缩格式

> 下述许多移动端新特性为 UE 4.26 新增功能或实验性功能

### UE4 Mobile Update
#### 1. Android 系统
* 新增功能
  * New Google Play service support such as `App Bundles` and `Assets Delivery`
    * 如下载游戏的核心内容，启动后动态下载更多资源
  * High refresh rate (GLES & Vulkan)
  * NDK 21
* 开发中
  * 把 UE4 打包成 AAR（Android Archive） 并嵌入其它项目。达到在标准安卓项目中，渲染时调出 UE。
  * 更多移动端领域，收集相关数据并连接到 Unreal Insights 性能分析工具，以及安卓端的更多工具支持
#### 2. iOS 系统
* 支持更多输入设备，支持 iOS 14, XCode 12 and the latest iDevices
  * 对于苹果要求应用程序要准确显示输入控制器的按钮 UI 并提供了相应接口，已可在蓝图中获取
* 120Hz for iPad Pro
* `Windows Metal shader compiler` released at WWDC
  * 在 Windows 开发设备上编译 Metal 着色器
#### 3. Patching Plugin 补丁插件
* ChunkDownloader
  * Unreal Engine 4.26
  * 适用于包含大量小型内容的游戏
#### 4. Android Graphics - Mobile `Rendering` 移动端渲染
* 改进了移动端的图像功能和质量
* Compute Shaders
  * UE 4.25 对 GLES 最低版本要求从 2 提升到 3.1
  * 将 Compute Shader 用于
    * Niagara GPU 粒子模拟
    * Runtime 虚拟纹理压缩
    * GPU scene
    * 部分 post-processing（Eye Adaptation Histogram、`GTAO`）
  * 计划
    * `Global Distance Field` support 距离场
    * GPU-driven rendering for more advanced culling, instancing and geometry 用 GPU 驱动的渲染来处理更高级的几何体
* 安卓端的驱动问题
  * Vulkan 在 around 2017 的设备上有问题，改为使用 ES31
  * 而使用 GLES 时，许多基于 Mali GPU 的设备在`纹理缓冲大小`方面遇到了限制。部分功能无法使用：尤其是 GPU Scene，而其它缓冲在 GLES 的顶点着色器中无法访问。
#### 5. Android Graphics - Tools 调试工具
* 从使用设备或平台的特定调试工具转为使用通用调试工具
  * 平台相关调试工具如：Arm Mobile Studio（Mali Graphics Debugger）、骁龙 Adreno Profiler
  * `RenderDoc`：for OpenGL ES and Vulkan on Android
  * `Android GPU Inspector`：by Google, 需要最新驱动，但在支持的设备上可以提供 GPU Tracing，包括在 Adreno、Mali 设备上提供性能计数器。Beta Version：[https://gpuinspector.dev/](https://gpuinspector.dev/) 最新版本支持 Android 11 的 Pixel 4
#### 6. Mobile vs. Desktop 
* 渲染方式
    桌面端 | 移动端
    :---: | :---:
    延迟/前向渲染 | 仅支持前向渲染
* 光照
    <center>桌面端 | <center>移动端
    :------ | :------
    ① 多种带阴影光照<br>② 每个物体接收基于图像的光照（from reflection captures, blended per pixel）<br>③ 屏幕空间反射 Screen-space reflections（SSR）<br>④ 多种着色模型（default, clear-coat, skin, hair, ...） | ① 单个方向光照<br>② 定向光源的动态阴影<br>③ 没有阴影的点光源/聚光源 spotlights<br>④ 每个物体 only one reflection capture<br>⑤ 没有 SSR 只有平面反射 planar reflections<br>⑥ 着色模型仅 default
#### 7. 移动端的画质改进措施
* 4.26 brings the UE4 `Desktop` renderers, `Forward and Deferred` to mobile 移动端可选择使用桌面端渲染器
  * 适用于当前移动设备中的超高端机型
  * iOS 已完成 Beta 测试，Android（currently Vulkan only）测试中
  * 启动时可选 Desktop Renderer or Mobile Renderer
* 移动端的更多特性
  * Mobile deferred renderer 移动端的延迟渲染
    * 相对 Desktop Renderer 与移动端 GPU 更匹配
    * 是 4.26 的实验性功能
    * 下文由 Dmitriy 继续展开
  * dynamic shadows from movable spotlights on both static and moveable geometry 可移动聚光源的动态阴影（适用于静态/可移动几何体）
  * additional shading model
    * 目前仅支持无光照/默认光照（`unlit`/`default`）
  * ambient occlusion
    * 增加了 `Ground-Truth Ambient Occlusion （GTAO）`
    * 增强了间接光和阴影的表现
    * 低端设备上需要注意性能
  * screen-space reflections：`Pixel Projected Reflcetions`
    * 一种屏幕空间反射技术，比传统 SSR 更适用于移动端硬件
    * 是 4.26 的实验性功能
    * 仅适用于平面，选项 `Mobile - Planar Reflection Mode`
  * reflection capture compression 压缩反射捕捉贴图以减少反射捕捉占用内存
    * runtime virtual texturing
    * 通常用于将性能消耗极大的地形材质转换为虚拟纹理，改善运行时性能
### 8. Future Work
* 更多着色模型
* `CSM caching` for reusing cascaded shadow map data between frames 用 CSM 缓存在各帧之间重用层叠阴影贴图数据
* 把移动引擎的更多部分转到 Render Dependency Graph
* Global Distance Field 距离场功能（距离场阴影和环境光遮蔽）
* 更多由 GPU 驱动的渲染功能（advance culling, instancing and more advanced geometry）

## `Deferred Shading on Mobile`
### UE4 移动端渲染
* 移动端前向渲染（default）、延迟渲染，电脑端 Renderer（可以和 Mobile Deferred Shading 同时使用）的前向渲染、延迟渲染（default）
* 由于 Desktop Renderer 对移动端压力太大，因此推荐针对移动端 GPU 有相应优化的 Mobile Renderer Deferred Shading
* Deferred Shading 启用方法
  * `DefaultEngine.ini`
  * `r.Mobile.ShadingPath = 0/1`

### 前向渲染 vs. 延迟渲染
* Forward Shading 前向渲染
  * 前向渲染：单 pass 计算最终像素颜色，渲染完场景整个场景。
  * 优点
    * 移动端友好，不需要大量内存带宽。
  * 缺点
    * 由于要在单 pass 计算最终像素颜色，`材质着色器` material shader code 必须`包含光照`部分 lighting code（且要针对不同的静态、可移动、点光源等情况），增大了 shader 体量。
    * 每个像素都必须计算材质和光照，但如果该像素被遮挡，就会导致大量 overdraw `过度绘制`
    * 多光源情况下要把来自所有光源的光照整合到像素（即使该光源无贡献），性能开销很大
    * 没有很好的支持光照贴花 lit project decals 的方法（Need D-buffer, full depth prepass）

* Deferred Shading 延迟渲染
  * 延迟渲染：多 pass，最简过程两个 pass。第一个 pass 将所有对象和像素材质数据渲染为多种纹理，称之为 `G-Buffer`，第二个 pass 渲染光照体积 light volumes 并通过 G-Buffer 的数据计算最终像素颜色。
  * 优点
    * 材质和光照计算完全独立
    * Much less shader permutations
    * 减少 Overdraw
  * 缺点
    * 需要为 G-Buffer 准备 4-6 个额外的 render targets，大幅增加内存需求
    * 接上条，需要四倍空间的 MSAA 开销很大不能使用
    * Alpha blending 也不能和延迟着色一起使用（可用延迟着色渲染所有不透明物体，再用前向着色渲染半透明对象）
    * 有些旧设备不支持延迟着色所需要的 `multiple render targets（MRT）`

### Tile-based GPUs and Deferred shading
* 24：32





