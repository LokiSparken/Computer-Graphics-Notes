# UE Docs

## 理解基础概念 - 入门 - 编程
### 1. 编程和脚本编写
* [编程指南](https://docs.unrealengine.com/4.27/zh-CN/ProgrammingAndScripting/ProgrammingWithCPP/)
  * [x] 编程快速入门
  * 开发设置
    * [x] 编译配置参考
    * [x] [从源代码构建虚幻引擎](https://docs.unrealengine.com/4.27/zh-CN/ProductionPipelines/DevelopmentSetup/BuildingUnrealEngine/)
    * [x] 编译游戏项目
    * [x] 管理游戏代码
    * 编程工具
      * [x] C++ 中的控制台变量
      * [x] Low-Level Memory Tracker（`LLM`） | 跟踪内存使用情况的工具
      * [ ] Sparse Class Data | 消除 Actor 类型的冗余属性（值在不同 Actor 实例中总是不变的属性，使其只存一份）
    * [x] 代码规范
      * 命名、注释规范
      * 关于标准库/关键字使用事项
      * Q: range replacement（为容器提供的 range for 基础）如何实现？
      * 匿名函数捕捉问题声明
      * enum、enum class
      * std::move -> MoveTemp 可显式调用 UE 实现的容器移动语意（移动构造/移动赋值）
      * default member initializers
      * Visual Studio 默认在 C# 中使用空格缩进，建议改为制表符与 C++ 保持一致
      * 不用于派生的类建议使用 final 关键字
      * 一般格式：文件末尾空白行、字符串固定使用 TEXT() 宏、`指针和引用空格加在后面（变量名前）`、不允许作用域覆盖、常量必须命名且能描述其含义、避免传 bool 参数给函数（以 enum class 代替）但在函数是 setter（ClassName::SetFlag(bool)）时可以、太长的参数列表开结构体、不要用 bool 和 FString 作为参数重载函数、接口类（前缀 I）为抽象类不能有成员变量、虚函数写明 virtual & override、平台有关的代码要做分离
    * [x] [Visual Studio 配置](https://docs.unrealengine.com/4.27/zh-CN/ProductionPipelines/DevelopmentSetup/VisualStudioSetup/)及[使用技巧](https://docs.unrealengine.com/4.27/zh-CN/ProductionPipelines/DevelopmentSetup/VisualStudioSetup/VisualStudioTipsAndTricks/)
      * 命令：蓝图调用堆栈、当前帧数等
      * 禁用编译器优化
      * DrawDebugHelpers 及调试文本（对应蓝图 PrintString）
      * 更改调试配置以加速 VS2019
    * [ ] UnrealVS 扩展 | ？感觉没啥用？
  * 虚幻引擎架构
    * [x] Gameplay Classes | [Class Specifier UCLASS](https://docs.unrealengine.com/4.27/zh-CN/ProgrammingAndScripting/GameplayArchitecture/Classes/)（类在引擎/编辑器中的行为）及 Metadata Specifiers（类在引擎/编辑器中的行为，每种类型有自己的元数据说明符列表，此给出类相关的）
      * 类在引擎中的行为：如规定子类能否 tick
      * 类在编辑器中的行为：如能否在蓝图编辑器中显示、显示时的 display name 等
      * ConstructorStatics 结构体（ObjectBase.h 中定义的特殊命名空间。构造函数首次运行时才创建，之后复制指针）：资源引用 FObjectFinder（硬编码写死资源路径）、类引用 FClassFinder（跨模块引用）和 ClassName::StaticClass（其它情况）
      * 类的组件/子对象指针声明时必须带 UPROPERTY() 是为了保证组件被创建、销毁和垃圾回收，可以获得类当前所有附着组件（包括父类创建的组件）列表
    * [x] UFunctions
      * 函数说明符：在引擎/编辑器中的一些行为，多人模式的 CS 问题，禁止子类 override 等
      * 函数元标签
      * 参数说明符：out
    * [ ] 游戏模块
    * [ ] 接口
    * [x] [元数据说明符](https://docs.unrealengine.com/4.27/zh-CN/ProgrammingAndScripting/GameplayArchitecture/Metadata/) | 各类型元数据说明符
    * [ ] 属性
    * [ ] 结构体
  * Gameplay 指南
    * [ ] 游戏控制的摄像机
    * [ ] 组件和碰撞
    * [ ] 第一人称射击游戏教程
    * [ ] 玩家输入和 Pawn
    * [ ] 变量、定时器和事件
    * [ ] Player-Controlled Cameras
    * [ ] 使用 UMG 的用户界面
  * [ ] 断言
  * [ ] Core Redirects
  * [ ] 引用资源
  * [ ] 资源注册表
  * [ ] 编程基础
  * [ ] 蓝图函数库
  * 游戏逻辑编程
    * [ ] Actors 
    * [ ] [委托](https://docs.unrealengine.com/4.27/zh-CN/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/)
    * [ ] 对象
    * [ ] 字符串处理
    * [ ] TArray
    * [ ] Gameplay 定时器
    * [ ] TMap
    * [ ] TSet
    * [ ] TSubclassOf
    * [ ] 虚幻 Object 处理
    * [ ] 虚幻智能指针库
    * [ ] 资源和包的版本控制
* [ ] Actor 通信
  * [ ] 类型转换快速入门指南
  * [ ] 直接 Actor 通信快速入门
  * [ ] 事件分发器/委托快速入门指南
  * [ ] 接口快速入门指南
* 蓝图可视化脚本
* 类创建基础知识
  * [ ] 仅使用蓝图
  * [ ] C++ 和蓝图
  * [ ] 仅使用 C++
* [ ] 游戏性架构
* [ ] Gameplay 调试程序
* [ ] 编程子系统
* [ ] Gameplay 标签
* [ ] 虚幻项目和游戏性
* [ ] 生成/销毁 Actor 总览
* [ ] 在线子系统
### 系统指南
* 动画节点技术指南
* 自动化系统概述
* 蓝图技术指南
* 在线子系统
* Online Subsystem Steam
* 图形编程
  * [ ] FShaderCache
  * [ ] 图形编程总览
  * [ ] 渲染依赖图
  * [ ] 着色器开发
    * [ ] 自定义着色器
    * [ ] 异步计算
    * [ ] HLSL 交叉编译器
    * [ ] 调试着色器编译过程
  * [ ] 线程渲染
  * [ ] 着色器插件
  * [ ] 并行渲染概述
  * [ ] 网格体绘制管道
* Slate UI 框架
  * 
  * [x] [控件反射器](https://docs.unrealengine.com/4.27/zh-CN/ProgrammingAndScripting/Slate/WidgetReflector/)
* 编译工具
### 自动化编译
* BuildGraph 脚本条件
* BuildGraph 脚本元素
* BuildGraph 脚本类型
* BuildGraph
* BuildGraph 使用
### 资源处理参考指南
* 异步资源加载
* 资源注册表
* 数据验证
* 

### 理解基础概念 - 入门 - 对游戏进行测试
* [ ] 在编辑器中进行测试


* [ ] 
