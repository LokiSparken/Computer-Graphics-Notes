> # [GAMES104 Modern Game Engine - Theory and Practice](https://www.bilibili.com/video/BV1oU4y1R7Km)
> * 救命！！！大佬们出来教搭系统了！！！呜呜呜呜呜这个世界上怎么有那么多又强又乐于分享的前辈啊！！！！！
> * 希望自己也能早日成为可以分享踩坑经验的人 2022.03.16

<font size=5>目录</font>

<!-- TOC -->

* [Lecture 1 - From Getting Started To Practice](#lecture-1---from-getting-started-to-practice)
* [Lecture 2 - Layered Architecture of Game Engine](#lecture-2---layered-architecture-of-game-engine)

<!-- /TOC -->

# Lecture 1 - From Getting Started To Practice
* 从算法到系统：需要良好的系统工程的训练，知道大型软件系统是如何架构的
* 历史
  * 红白机：（坦克大战参上！！！！！）内存空间特别紧张
  * 游戏引擎概念的提出：John Carmack（卡神） - Wolfenstein 3D(1992) 重返德军总部（射击游戏）、Doom->游戏引擎，并授权 Raven 公司制作了 ShadowCaster
  * 早期游戏引擎：Quake
* Middlewares 中间件（speedtree植被、音频引擎等）
* About Game Engine
  * `Realtime`：在硬件限制、网络带宽、延迟的各种限制下使劲 realtime
  * 给创作者提供设计工具链
  * 使用该引擎做对于不同类型游戏的二次开发的能力
  * 提供多人协作进行设计的能力
* Course Content
  * Basic Elements：引擎的结构和层次、数据组织和管理
    * 游戏引擎从哪看起：`Update()/Tick()`
  * Rendering：如何组织渲染里的各种元素，把渲染算法拼起来
  * Animation
  * Physics
  * Gameplay
  * Misc. Systems
    * Effects：提供框架和结构给 designer
    * Navigation：寻路系统
    * Camera：影响镜头感
    * ...
  * Tool set（工业化）
    * C++ Reflection
    * Data Schema 升级后可兼容的数据格式
  * Online Gaming（同步问题）
  * Advanced Technology
    * Motion Matching
    * Procedural Content Generation（PCG）
    * Data-Oriented Programming（DOP）（借助多核）
    * Job System 任务系统
    * Lumen
    * Nanite
* Course Logistics
  * Website: https://games104.boomingtech.com（course slides）
  * BBS: games-cn.org/forums/forum/games104-forum
  * Ref: Game Engine Architecture
  * `Mini Engine`
  * Assignments: 给出小的命题
  * Assignment Submission Website: www.smartchair.org/GAMES104


# Lecture 2 - Layered Architecture of Game Engine
* 引擎架构分层与整体 Pipeline

    ![](note%20-%20image/GAMES104/1.png)
* A Glance of Game Engine Layers
  * `Tool layer`: Chain of Editors
  * `Function Layer`: Make it visible、movable and playable (Rendering、Camera, HUD and Input、Script, FSM and AI、Physics、Animation）
  * `Resource Layer`: Data and Files（加载、管理资源，定义数据格式 schema、数据在文件和编辑器中如何呈现）
  * `Core Layer`: Swiss Knife of Game Engine（数学运算等工具库）
  * `Platform Layer`: Launch on Different Platforms（处理不同的 OS、平台文件系统、图形 API、平台 SDK 等）
  * Middleware and 3rd Party Libraries: speedtree 等第三方专业工具库

* Resource Layer
  * 第三方建模工具导出的文件格式一般有许多冗余信息，要先把 resource（资源） importing 成引擎自身的 asset（资产）：如不同格式的纹理贴图文件中有不同的压缩算法，先统一成 dds 格式（DirectDraw Surface，DX 纹理压缩的产物），可以直接扔到 GPU 中
  * 定义 composit asset（关系脚本 XML）：规定某个物体使用哪种骨骼、网格体和动画（定义数据之间的关联）
  * `GUID` 系统：游戏资产的唯一标识
  * `Runtime Asset Manager`：通过 `handle system` 管理资产的生命周期（`GC`、延迟加载等）
* Function Layer

    ![](note%20-%20image/GAMES104/2.png)
  * 注意每帧所做的 `tickLogic` 逻辑运算、`tickRender` 渲染运算
  * 有些模块如 camera 等，难以区分属于引擎功能还是游戏功能，会在功能层打架（
  * Multi-Threading：把 logic、rendering 的计算分到不同线程，物理、animation 等分散到不同线程，or `JOB system`（注意 dependency 的管理）
* Core Layer（绝对的安全性、绝对的效率）
  * Math Efficiency：引擎需要自带的数学库，通过 hack 加速计算或者适应硬件上提供的一些快速运算，如 SIMD
  * Data Structure and Containers：`C++ STL 频繁分配空间又删除时内存碎片很多，且不受控制（如 vector 的两倍扩容，造成很大内存浪费）`，因此需要手撕的结构，使碎片少 && 访问效率高
  * Memory Management：`注意 CPU 主频/内存以外的缓存大小，通常可能是这块 CPU 性能的瓶颈`
    * 数据存放位置要集中
    * 尽可能顺序访问
    * 读写时批量
* Platform Layer
  * 对于不同平台的图形 API：`Render Hardware Interface`（RHI）、把不同 API 的接口再封装一层
  * 对于不同的硬件架构：如索尼 PS 的 PPU（即传统的 CPU） & SPU（小的协助 CPU，速度很快，可以直接写显存），以及 arm 的芯片有大小核，实现时需要知道算法运行在什么核中才合理。
* Tool Layer
  * 开发语言比较自由
  * `DCC`：Digital Content Creation，其他人开发的资产生成工具
  * 将 DCC 产出的资源通过 `Asset Conditioning Pipeline` 导入导出
* **`Tips: 只允许上层调用下层的功能`**


