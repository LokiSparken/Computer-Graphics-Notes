> # Computer-Graphics-notes
> **`All notes about my daydream for game developing & my Atlantis.`**

说明  
* 列出一些学习资源，存放笔记的目录结构和学习资源列表分类不尽相同。
* 笔记 markdown 预览以 VS Code 插件 Markdown All in One 为准，部分在 github 上不渲染

格式  
* 课程/书籍/资源名称 | 作者/来源 | 资源类型/发布平台 | `备注`

目录
<!-- TOC -->

* [图形学与游戏引擎 Computer Graphcis \& Game Engine](#图形学与游戏引擎-computer-graphcis--game-engine)
  * [Basic 基础入门](#basic-基础入门)
  * [Rendering 渲染](#rendering-渲染)
  * [API \& Engine](#api--engine)
    * [API - DirectX](#api---directx)
    * [API - OpenGL](#api---opengl)
    * [API - Vulkan](#api---vulkan)
    * [Engines](#engines)
  * [GPU](#gpu)
  * [文章资料](#文章资料)
  * [好东西！\& Toolbox](#好东西-toolbox)
* [虚幻引擎 Unreal Engine](#虚幻引擎-unreal-engine)
  * [入门教程](#入门教程)
  * [基本主题](#基本主题)
    * [NPC AI](#npc-ai)
    * [动画 Animation](#动画-animation)
    * [地形 Landscape](#地形-landscape)
    * [光照 Lighting](#光照-lighting)
    * [材质 Material](#材质-material)
    * [建模 Modeling](#建模-modeling)
    * [UI](#ui)
    * [特效 VFX](#特效-vfx)
      * [VFX - Niagara](#vfx---niagara)
    * [Houdini](#houdini)
      * [1. SOP（Surface Operator）](#1-sopsurface-operator)
      * [2. VEX](#2-vex)
  * [技术分享](#技术分享)
    * [Unreal Fest Online 2020 | bilibili](#unreal-fest-online-2020--bilibili)
    * [Unreal Open Day 2020 | bilibili](#unreal-open-day-2020--bilibili)
    * [Fest Europe 2019 | bilibili](#fest-europe-2019--bilibili)
    * [Unreal Engine GDC 2019 | bilibili](#unreal-engine-gdc-2019--bilibili)
    * [Inside Unreal | YouTube](#inside-unreal--youtube)
  * [文章资料](#文章资料-1)
  * [好东西！](#好东西)
* [计科基础 Computer Science](#计科基础-computer-science)
  * [C++ 是不可能会用的](#c-是不可能会用的)
  * [工程是不可能会写的](#工程是不可能会写的)
  * [软硬件协同设计](#软硬件协同设计)
  * [其它](#其它)
* [深渊天坑 TODO Flag](#深渊天坑-todo-flag)
  * [Sparkler](#sparkler)
* [第九艺术](#第九艺术)
  * [Sparkle 光](#sparkle-光)
* [个人小结 Personal Road to Games \& CG](#个人小结-personal-road-to-games--cg)

<!-- /TOC -->

---

# 图形学与游戏引擎 Computer Graphcis & Game Engine

> <font color=#6495ED size=6>Welcome to CG & Engine！(>ᴗ<*)ฅ</font>  
> <font color=#6495ED>—— 有生之年。</font>

## Basic 基础入门
- [ ] 1. [【授权翻译】如何开始学习图形学编程](https://zhuanlan.zhihu.com/p/55518151) | 知乎
- [ ] 2. [Computer Graphics (CSE167x)](https://www.edx.org/course/computer-graphics-2) | Ravi Ramamoorthi | edX | `数学部分挺好，狂敲黑板注意几何意义`
- [ ] 3. [GAMES101](https://www.bilibili.com/video/BV1X7411F744) | 闫令琪 | GAMES | bilibili | `★★★★★，入门第二课，男神超可爱！`
   - [x] Lectures & Notes
   - [ ] Homeworks 3/8
- [ ] 4. Fundamentals of Computer Graphics, 4th Edition | Book | `虎书`
- [ ] 5. [GAMES202](https://www.bilibili.com/video/BV1YK4y1T7yY) | 闫令琪 | GAMES | bilibili | `Real-Time High Quality Rendering`
  - [x] Lectures & Notes
  - [ ] Homeworks 1/5
- [ ] 6. [GAMES104](https://www.bilibili.com/video/BV1oU4y1R7Km) | 王希 | GAMES | bilibili | `引擎架构入门`（配合 Game Engine Architecture？）
  - [ ] Lectures & Notes
  - [ ] Homeworks 
<!-- - [ ]  -->

## Rendering 渲染
- [ ] 1. Ray Tracing 三部曲 | Peter Shirley | Book | `cookbook，入门第一课，还有很多？？？的地方，据说看了PBRT再来review会豁然贯通=。=`
   - [x] Ray Tracing in one weekend
   - [x] Ray Tracing the next week
   - [ ] Ray Tracing the rest of your life | `蒙特卡洛+重要性采样做优化`
- [ ] 2. Real-Time Rendering, 4th Edition | Book | `RTR`
- [ ] 3. Physically Based Rendering: From Theory to Implementation, 3th Edition | Book | `PBRT`
- [ ] 4. Advanced Global Illumination | Philip Dutre, Kavita Bala, Philippe Bekaert | Book | `全局光照`
- [ ] 5. Veach Thesis | Eric Veach | Paper | `光线传播一条龙`

## API & Engine
### API - DirectX
- [ ] DirectX 12 3D 游戏开发实践 | `龙书`
- [ ] [Windows 渲染引擎入门](https://www.zhihu.com/column/c_1465096004047822849) | MaxwellGeng | 知乎专栏 | `龙书精炼`
### API - OpenGL
  - [ ] [LearnOpenGL](https://learnopengl.com/) | `OpenGL入门，2020 & 2021 更新了 OIT 等几块高级内容`
  - [ ] [LearnOpenGL 中译](https://learnopengl-cn.github.io/) | `社区好人翻译，更新部分暂未收录`
### API - Vulkan
  - [ ] [GameTechDev/IntroductionToVulkan](https://github.com/GameTechDev/IntroductionToVulkan) | `入门示例`
  - [ ] [vulkan-tutorial](https://vulkan-tutorial.com/) | `入门`
  - [ ] Vulkan Cookbook | Pawel Lapinski | Book | `据说不适合初学者（`
  - [ ] [awesome-vulkan](http://www.vinjn.com/awesome-vulkan/) | Vinjn张静 | `资料汇总`
### Engines
- [ ] [Game Engine Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) | The Cherno | YouTube | `更新至93p`
- [ ] 从零开始手敲次世代游戏引擎 | 陈文礼 | 知乎 | `2020.06.11更新至八十三`
- [ ] 游戏引擎架构 | 叶劲峰 译
- [ ] Unity Shader 入门精要 | 冯乐乐
- [ ] Unity Tutorials | Jasper Flick | (Catlike Coding)(https://catlikecoding.com/unity/tutorials/)

## GPU
- GPU Gems & Pro & Zen
  - [ ] GPU Gems 1
  - [ ] GPU Gems 2
  - [ ] GPU Gems 3
  - [ ] GPU Pro 1
  - [ ] GPU Pro 2
  - [ ] GPU Pro 3
  - [ ] GPU Pro 4
  - [ ] GPU Pro 5
  - [ ] GPU Pro 6
  - [ ] GPU Pro 7
  - [ ] GPU Zen

## 文章资料
1. [Ke-Sen Huang's Home Page](https://kesen.realtimerendering.com/) | Kesen Huang | `CG论文集锦`
2. [由浅入深学习PBR的原理和实现](https://www.cnblogs.com/timlly/p/10631718.html) | 0向往0 | `PBR概览`
3. [Filament 文档](https://jerkwin.github.io/filamentcn/) | `PBR资料`
4. Behind the Pixels | 文刀秋二 | 知乎
   - [ ] 基于物理着色（一）
   - [ ] 基于物理着色（二）- Microfacet材质和多层材质
   - [ ] 基于物理着色（三）- Disney和UE4的实现
   - [ ] 基于物理着色（四）- 次表面散射
5. 浅墨的游戏编程 | 毛星云 | 知乎
6. SIGGRAPH Courses
   - [ ] [Physically Based Shading in Theory and Practice](https://www.youtube.com/watch?v=zs0oYjwjNEo)
7. 会议
   * SIGGRAPH
   * SIGGRAPH Asia
   * Eurographics
   * Symposium on Interactive 3D Graphics and Games
8. ShaderX 系列

## 好东西！& Toolbox
* [stb](https://github.com/nothings/stb) | `图片读写库`
* [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) | `模型导入`
* [IMGUI](github.com/ocornut/imgui) | `超香GUI`
* [The-Forge](https://github.com/ConfettiFX/The-Forge) | `轻量开源引擎？`
* [Shadertoy](http://shadertoy.com/) | `Shader is magick!`
* [GLSL Sandbox Gallery](http://glslsandbox.com/)
    * [嗷嗷嗷嗷嗷！！！](http://glslsandbox.com/e#71861.0)
* [POV-Ray](http://www.povray.org/)
* [Panorama to Cubemap](https://jaxry.github.io/panorama-to-cubemap/) | `全景图转 cubemap`
* [NormalMap-Online](https://cpetry.github.io/NormalMap-Online/) | `在线生成 specular 贴图等`

---

# 虚幻引擎 Unreal Engine

> <font color=#6495ED size=6>虚幻引擎</font>  
> <font color=#6495ED>—— 这辈子都不可能会用的。</font>

## 入门教程
1. 后天星期六 | 泰课在线 | `看了 TomLooman 所以小男神剩下的部分应该要咕了`
   - [x] 三维弹球（蓝图）
   - [x] 用C++带你走进虚幻4
   - [ ] 坦克大战（C++）
2. TomLooman | Udemy | `★★★★★`
   - [x] Create Multiplayer Games with C++

## 基本主题
### NPC AI
1. - [ ] Unreal Engine AI with Behavior Trees | Unreal Engine | YouTube

### 动画 Animation
1. - [x] 虚幻引擎编辑器基础——动画 | UE4 Online Learning
2. - [x] 初始动画 | UE4 Online Learning
3. - [x] 动画入门 | UE4 Online Learning
4. - [ ] Character Animation in UE4 | Unreal Engine Livestream | Live Training | YouTube
5. - [x] UE4 Animation Montage | 安宁Ken | bilibili
6. - [ ] first hour in sequencer

### 地形 Landscape
1. - [ ] [UE4零基础入门到独立游戏开发【Landscape地貌篇】](https://www.bilibili.com/video/BV1mD4y1D7D6) | CG学习笔记 | bilibili
2. - [ ] [WorldMachine基础知识与节点释义](https://www.bilibili.com/video/BV1t7411z7HR) | CG学习笔记 | bilibili

### 光照 Lighting
1. - [ ] [UE4零基础入门到独立游戏开发【灯光篇】](https://www.bilibili.com/video/BV1Gt4y1i7Ht) | CG学习笔记 | bilibili

### 材质 Material
1. - [x] 虚幻引擎编辑器基础——材质 | UE4 Online Learning
2. - [ ] 创建简单水体材质 | UE4 Online Learning
3. - [ ] 创建燃烧的木材材质 | UE4 Online Learning
4. - [ ] 创建PBR材质 | UE4 Online Learning
5. - [ ] 材质大师课程 | UE4 Online Learning
6. - [ ] [UE4零基础入门到独立游戏开发【材质基础算法】](https://www.bilibili.com/video/BV1B7411P7cC) | CG学习笔记 | bilibili

### 建模 Modeling
1. - [ ] [UE4零基础独立游戏开发系列教程【maya专辑模型篇】](https://www.bilibili.com/video/BV1i74118719) | CG学习笔记 | bilibili | `开头 2min 笑得我腹肌八块 2333`
2. - [ ] [UE4零基础独立游戏开发系列教程【ZBrush入门篇】](https://www.bilibili.com/video/BV19741187S8) | CG学习笔记 | bilibili

### UI
1. - [ ] Make UI With C++: How to use Slate in Unreal Engine | Reuben Ward | YouTube

### 特效 VFX
#### VFX - Niagara
1. Unreal Engine Niagara Tutorials | CGHOW | YouTube

### Houdini
#### 1. SOP（Surface Operator）
* [ ] [Houdini 入门](https://www.bilibili.com/video/av77323910) | 官方入门 | bilibili | `原官方地址 https://www.sidefx.com/tutorials/`
* [ ] [Houdini Workflows with Unreal Engine Houdini到虚幻的工作流](https://www.bilibili.com/video/BV11p4y1U7TW) | Unreal 英文直播 官方汉化 | bilibili
#### 2. VEX
* [ ] [通过案例学VEX-零基础](https://www.bilibili.com/video/BV1Zp411d7Hw) | 捷佳 | bilibili | `需要 Houdini 基础`
* [ ] [Houdini VEX中文百科](https://www.bilibili.com/video/BV12W411x7df) | 捷佳 | bilibili | `vex/编程基础`

## 技术分享
### [Unreal Fest Online 2020 | bilibili](https://space.bilibili.com/138827797/video?keyword=UnrealFestOnline)
1. - [ ] [Optimizing and Building UI for AAA Games 用虚幻示意图形（UMG）UI设计器优化并构建3A级UI(官方字幕)](https://www.bilibili.com/video/BV1EK4y1j7VB) | Carey Hickling
### [Unreal Open Day 2020 | bilibili](https://space.bilibili.com/138827797/video?keyword=UnrealOpenDay2020)
1. - [x] [2020虚幻引擎4移动平台上的更新](https://www.bilibili.com/video/BV11a4y1H7jC) | Epic Games - Mobile Team Leader & Mobile Rendering Programmer
2. - [ ] [虚幻引擎移动端ComputeShader的应用](https://www.bilibili.com/video/BV1ey4y1q7s4) | 刘炜
3. - [ ] [深入GAS架构设计](https://www.bilibili.com/video/BV1zD4y1X77M) | 大钊
4. - [ ] [Procedural Worlds in a Persistent Universe - Workflow from Houdini to Unreal 恒续游戏中的程序化世界生成-从Houdini到虚幻引擎的流程](https://www.bilibili.com/video/BV1wv411b7Ew) | Directive Games TA & Houdini Lead TD 
5. - [x] [虚幻引擎4开放世界ARPG《幻塔》技术分享](https://www.bilibili.com/video/BV1Ka4y1W7NE) | 幻塔 丁许朋 | `开放大世界的地形优化，移动平台限制（DrawCall、顶点数），超大视距（UE中的裁剪优化、动态遮挡查询、植被DC优化、阴影方案）`
6. - [ ] [虚幻引擎4全平台热更新方案](https://www.bilibili.com/video/BV1ey4y1q7s4) | 查利鹏
### [Fest Europe 2019 | bilibili](https://space.bilibili.com/138827797/video?tid=0&page=1&keyword=FestEurope2019&order=pubdate)
1. - [x] [Using the Gameplay Ability System](https://www.bilibili.com/video/BV1gJ411J7AM) 使用游戏玩法技能系统
2. - [ ] [Gameplay Abilities Meet Behavior Trees](https://www.bilibili.com/video/BV12E41147eb) 游戏技能系统搭配行为树
3. - [ ] [Digital Material with the Substance Tools](https://www.bilibili.com/video/BV1dE41147gn) UE4里的Substance流程
4. - [x] [UE4 Pixel Streaming](https://www.bilibili.com/video/BV1gJ411J7Jv) UE4像素流技术
5. - [ ] [100 Unreal Engine 4 Tips & Tricks](https://www.bilibili.com/video/BV1EJ411J7ac) 100个UE4的小技巧
6. - [ ] [Engine Tools for Performance on Open World Games](https://www.bilibili.com/video/BV1D4411B7Tn) 开放大世界引擎性能优化工具
7. - [ ] [充分利用动画蓝图优势-《堡垒之夜》中的动态动作](https://www.bilibili.com/video/BV1gJ411J7hJ)
8. - [ ] [使用插件在多个UE4项目间共享代码(官方汉化)](https://www.bilibili.com/video/BV1gJ411J7s7)
9. - [ ] [UE4网格渲染管线重构(官方汉化)](https://www.bilibili.com/video/BV1gJ411J7j1)
10. - [ ] [AMD-集成有限元物理系统到UE4中(官方汉化)](https://www.bilibili.com/video/BV1EJ411J7WP)
11. - [ ] [游戏中的光线追踪运用实践(中文字幕)](https://www.bilibili.com/video/BV1D4411B7NM)
12. - [ ] [常见危险性能瓶颈和定位点(中文字幕)](https://www.bilibili.com/video/BV1D4411B7hJ)
13. - [ ] [使用Python简化资产工作流程(官方汉化)](https://www.bilibili.com/video/BV1gJ411J7Fh)
14. - [ ] [A Postmortem on Implementing AutoPlay in UE4](https://www.bilibili.com/video/BV17J411y7En) 自动游戏功能的实现(官方汉化)
15. - [ ] [Niagara介绍 | Introduction to Niagara(官方汉化)](https://www.bilibili.com/video/BV1UE411478B)
16. - [ ] [《盗贼之海》聚合Tick技术优化大规模场景(中文字幕)](https://www.bilibili.com/video/BV1D4411B7nX)
17. - [ ] [复制图：优化RTS游戏带宽(中文字幕)](https://www.bilibili.com/video/BV1D4411B7YX)
18. - [ ] [可见日志：调试所有玩法需求(中文字幕)](https://www.bilibili.com/video/BV1D4411B7x4)
19. - [ ] [怀旧与新奇的融合-《歧路旅人》开发技巧分享(官方汉化)](https://www.bilibili.com/video/BV1AE411V7rC)
20. - [ ] [虚幻引擎新增动画特性 | New Animation Features in Unreal Engine (官方汉化)](https://www.bilibili.com/video/BV1UE41147jS)
21. - [ ] [分层材质系统塑造环境 | Layered Materials for Environment(官方汉化)](https://www.bilibili.com/video/BV1UE41147BB)
22. - [ ] [颜色管理 | Colour Management–A Bird's Eye View for Artists(官方汉化)](https://www.bilibili.com/video/BV1RE41147BT)
23. - [ ] [数据驱动音效设计 | Data-Driven Sound Design(官方汉化)](https://www.bilibili.com/video/BV1dE41147XB)
24. - [ ] [异步载入界面和过渡关卡 | Async Loading Screens and Transition Levels(官方汉化)](https://www.bilibili.com/video/BV1XE41147dQ)
25. - [ ] [《堡垒之夜》工作流程分享(官方汉化)](https://www.bilibili.com/video/BV13J411J7Uf)
26. - [ ] [拥抱虚幻引擎的方法(官方汉化)](https://www.bilibili.com/video/BV1gJ411J76e)
27. - [ ] [蓝图深入探讨 | Blueprints In-depth (官方汉化)](https://www.bilibili.com/video/BV1sJ41167np)
28. - [ ] [《盗贼之海》的自动化测试框架(官方汉化)](https://www.bilibili.com/video/BV1EJ411J7Yz)
29. - [ ] [SplashDamage-UE4开发工作流程规范(官方汉化)](https://www.bilibili.com/video/BV1sJ411677R)
### [Unreal Engine GDC 2019 | bilibili](www.bilibili.com/video/av61595751)
1. - [ ] A Hands-on Look at Using Ray Tracing in Games with UE 4.22
2. - [ ] Building Effects with Niagara and Blueprint
3. - [ ] Causing Chaos - The Future of Physics and Destruction in Unreal Engine
4. - [x] Enhancing Animation with Control Rig
5. - [ ] Learning to Make Games with UE4 and Action RPG
6. - [ ] New Animation Features in Unreal Engine
7. - [ ] Order from Chaos - Destruction in UE4
8. - [ ] Ray Tracing in Unreal Engine 4.22
9. - [ ] Refracting the Mesh Drawing Pipeline for Unreal Engine 4.22
10. - [ ] Unreal Engine's Audio Rendering - Retrospectives and Case Study Analysis
### [Inside Unreal | YouTube](https://www.youtube.com/playlist?list=PLZlv_N0_O1gbggHiwNP2JBXGeD2h12tbB)
1. - [ ] ...

## 文章资料
1. - Unreal Engine 4 Documentation | Unreal Engine | `官方文档`
   <!-- - [ ] Slate -->
2. - Inside UE4 专栏 | 大钊 | 知乎
   <!-- * [x] 开篇
   * [ ] 基本概念
   * [ ] GamePlay架构
     * [ ] Actor & Component
     * [ ] Level & World
     * [ ] WorldContext, GameInstance & Engine
     * [ ] Pawn
     * [ ] Controller
     * [ ] PlayerController & AIController
     * [ ] GameMode & GameState
     * [ ] Player
     * [ ] GameInstance
     * [ ] 总结
     * [ ] Subsystems
   * [ ] UObject -->
3. - TomLooman 博客 | tomlooman.com
4. - [ ] UE4行为树详解 | ksun | 知乎
5. - [ ] 浅析UE4-BehaviorTree的特性 | Lights999 | 知乎
6. - [剖析虚幻渲染体系](https://www.cnblogs.com/timlly/p/13512787.html) | 0向往0 | `PBR概览博客作者又更新惹！！！`
   <!-- - [ ] 剖析虚幻渲染体系（01）- 综述和基础 -->
7. - [Orfeas 博客](https://www.orfeasel.com/) | `UE4 C++`
8. - [Asher 博客](http://asher.gg/) | `可爱TA在线炫技`

## 好东西！
* Unreal Marketplace `AdvancedLocomotionSystem` | `动画系统高级使用示例`

---

# 计科基础 Computer Science

> <font color=#6495ED size=6>计算机基础</font>  
> <font color=#6495ED>—— 空空如也，莫得基础。 :)</font>

## C++ 是不可能会用的
- C++ Primer
- Effective 系列
  - [ ] Effective C++
  - [ ] More effective C++
  - [ ] Inside the C++ Object Model
  - [ ] Effective STL
  - [ ] Effective Modern C++
- STL 源码剖析
- CMake
  - git:cmake-examples

## 工程是不可能会写的
- 设计模式

## 软硬件协同设计
- [一生一芯](https://ysyx.oscc.cc/) | `轮子之心一路造到底层`

## 其它
- 深入理解计算机系统结构
- 操作系统
  - [ ] 操作系统概念
  - [ ] 现代操作系统
- 计算机网络
  - [ ] 计算机网络（自顶向下方法）
  - [ ] 现代计算机网络
- 编译原理

---

# 深渊天坑 TODO Flag

> <font color=#6495ED size=6>永不下落的旗帜</font>  
> <font color=#6495ED>—— 实现当然是不存在的。</font>

## Sparkler
* IMGUI
* Renderer QAQ
  * Soft Rasterizer & Ray Tracer？
  * DX12？
  * Rendering algorithm comparator？？？
* Debugger
  * Rendering Statistics：Resolution、Render Time、FPS、Batches、Saved by batching、Tris & Verts……
  * Frame Debugger：Pixel Tracer（a pixel picker and show some intermediate rendering data about this pixel?）、Events List、DC with results……

---

# 第九艺术
> <font color=#6495ED size=6>创世美学须知</font>  
> <font color=#6495ED>—— 我说，要有光。</font>
## Sparkle 光
* [ ] [基础色彩理论](https://www.bilibili.com/video/BV1t7411o79q)
* [ ] [光影色彩理论](https://www.bilibili.com/video/BV14t41127Xz) | Jerry Mickery
* [ ] [色彩与光线](https://www.bilibili.com/video/BV1rW411B7qX) | James Gurney

# 个人小结 Personal Road to Games & CG
> <font color=#6495ED size=6>DONE List Encourage！</font>  
> <font color=#6495ED size=6>—— 假装有变强。</font>
<!-- 
TIPS: Incremental learning notes.

## DONE
* CG - CSE167 Maths
* CG - Peter Shirley Ray Tracing 三部曲
  * Ray tracing in one weekend
  * Ray tracing in the next week
* CG - GAMES101
* Engine - 后天星期六 & TomLooman（UE 入……入不了门）
* CG - Unity Shader 入门精要（主 shader）

## DOING
* CG - LearnOpenGL
* CG - GAMES202
* CS - Effective C++

## NEXT
* CG - DX12
* FLAG - Renderer with 
  * soft rs.
  * rt.
  * API dx12
 -->


> # To Be Continued...

<!-- 
---

* 想变强喵w
 * Shader
 * RenderDoc
 * Houdini

---

* 考虑整理的笔记？
 * CSE 167 Math
 * RT I & II
 * GAMES101
 * ...

-->

<!-- <style> h1 { border-bottom: none } </style> -->
