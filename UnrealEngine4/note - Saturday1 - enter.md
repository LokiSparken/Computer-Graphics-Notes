> #  <i class="fa fa-book-open"></i> 后天星期六 - 《用C++带你走进虚幻4》

# 任务一：课程介绍

# 任务二：环境安装和版本控制
## SourceTree管理UE4 C++项目具体步骤
* 选择项目文件夹。
* 忽略项：
  * .vs/：vs的项目相关
  * Binaries/：通过源代码生成的二进制文件
  * Intermediate/：
  * Content/StarterContent/：内置的
  * Saved/
  * `待记录`

# 任务三：创建第一个Cpp组件
## 头文件获取
* 官方文档C++ API Reference点进具体类型底部Header为所需头文件。

## 打印到游戏：UE_LOG
* 格式参照文档：https://wiki.unrealengine.com/index.php?title=Logs,_Printing_Messages_To_Yourself_During_Runtime
* `UE_LOG(自定义类型，级别，输出内容)`

# 任务四：创建OpenDoor组件
## 将Cpp变量参数暴露到UE4编辑器
* 使用UPROERTY宏：https://wiki.unrealengine.com/UPROPERTY
  * `EditAnywhere`

## 小技巧
* 运行时F8脱出角色。
* vs 注释快捷键：c+k+c, c+k+u
* 整个空Pawn用来试Trigger。
* `【！】`注意UPROPERTY的编辑如果GUI忘记绑定，有空指针没赋值运行秒崩orzzz所以一定要加判空！！！

# 任务五：学习射线和DebugLine
## DebugLine
* 文档：Functions -> DrawDebugLine
* 获取角色位置和旋转方向（即射线起始点）  
`GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(&PlayerViewPointLocation, &PlayerViewPointRotation);`
* 角色位置+视线方向*长度 = 往看向的地方的着眼坐标
`FVector LineTraceEndLocation = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;`
* 绘制射线：`DrawDebugLine`
* 获取击中物体
    ```cpp
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType
    (
        HitResult,					// 返回击中的第一个物体
        PlayerViewPointLocation,	// 射线起点
        LineTraceEndLocation,		// 射线终点
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),	// 射线可击中的类型
        QueryParameter				// 撞击类型
    );
    ```



# <i class="fa fa-star"></i> 任务六：

# <i class="fa fa-star"></i> 任务七：

# <i class="fa fa-star"></i> 任务八：

# <i class="fa fa-star"></i> 任务九：



# Debug
* `The global shader cache file '*SM5.bin' is missing.`
  * 按下面三种解决方案配置重新构建生成一下：
    - Development Win64
    - DebugGame Win64
    - Development Editor Win64
  * 然后用Development Editor Win64调试运行

# 当 UE4 狂吃磁盘空间当缓存
* C:\User\sparken\AppData\Local\UnrealEngine
  * 4.24
  * Common
  * ...
* 引擎配置修改
  * 编辑器偏好设置 - 通用 - 全局
  * `Derived Data`
  * 如果目录无法访问，会缓存到默认位置

# 版本管理
* 可以直接内置 initial 启用 git 了，自动生成相关 .git 和 .gitignore
* 可以忽略远程仓库

# **End**
<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->