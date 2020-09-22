> #  <i class="fa fa-book-open"></i> 后天星期六 - 《用C++带你走进虚幻4》

# 任务一：课程介绍

# 任务二：环境安装和版本控制
## 这个不行了，见底部版本控制
## SourceTree管理 UE4 C++ 项目具体步骤
* 选择项目文件夹。
* 忽略项：
  * .vs/：vs的项目相关
  * Binaries/：通过源代码生成的二进制文件
  * Intermediate/：
  * Content/StarterContent/：内置的
  * Saved/
  * `待记录`

# 任务三：创建第一个Cpp组件
## 准备工作
* `项目管理`：创建 Content/Maps/
* 在 Maps/ 中创建 file - new level （可选类型，此选 default ）
  * 创建后，保存到 Maps/MainMap
* 从 Content/StartContent/Props/ 中拖个椅子进场景，去掉默认的 playerstart

## 打印到游戏
### ① 蓝图的方式
* 不用创建蓝图类
* 项目管理：创建 Content/Blueprint/
* 可以直接在主界面的右侧，为物体 Add Component - Scripting - New Blueprint Script Component 
  * 命名 BP_Reporter
  * 保存到 Blueprint
* 与蓝图类的区别：没有 viewport ，只执行脚本。 event graph 中有 beginplay 及 event tick 。
* 用脚本的 event graph 实现`开始时打印椅子位置`
  * 首先用 `Get Owner` 获取脚本的所属 actor
  * 再 `Get Display Name` ，把它 print string 即可
  * 要一次输出多个量的话可以用 **`Append`** 拼起来

### ② C++的场合
* 同样只用脚本
* 直接在主界面右侧 Add Component - `New C++ Component` - actor component
  * 命名为 Reporter
* 进入 Reporter.cpp 可以发现初始方法
  *  `void UReporter::BeginPlay()`、`void UReporter::TickComponent(...)`
  *  与蓝图脚本中 event graph 里的两个事件触发结点相同

---
#### **[插播] UE4 命名规范 - 1. 类名前缀**
UE4的类名必须遵从命名规范，需要在类名前面加上正确的前缀，与之对应的C++文件名则不加前缀。否则会编译报错。
* 派生自 Actor 的类前缀为 A，如 AController。
* 派生自 UObject 的类前缀为 U，如 UComponent。
* 枚举 的前缀为 E，如 EFortificationType。
* 接口 类的前缀通常为 I，如IAbilitySystemInterface。
* 模板 类的前缀为 T，如 TArray。
* 派生自 SWidget(Slate UI)的类前缀为 S，如 SButton。
* 其余类的前缀均为 字母 F ，如 FVector。
#### **[插播] UE4 命名规范 - 2. 其他类型命名**
* bool类型变量需要加上b前缀，如 bCallable。
---

* 所以显然要在 BeginPlay() 中输出，类似蓝图脚本：
  * `GetOwner` 一下，根据 IDE 提示的类型 `AActor *UActorComponent::GetOwner() const` 可知，需要赋给一个指向 AActor 类型的指针。
    * 因此 `AActor *Owner = GetOwner();`
  * 得到父 actor 后，在调用 AActor 相关方法前，需要先 include 其头文件。
  * **`头文件获取`**：官方文档 C++ API Reference 点进具体类型底部 Header 即为所需头文件。
    * 一般截取头文件路径 Classes/ 之后的就可以。
    * 因此到 .h 中 `#include "GameFramework/Actor.h"`
    * **注意 .h 中 `#include "*.generated.h` 要放在头文件列表的最后**
  * 然后就可以 `FString Name = Owner->GetName();`
  * `FVector Location = Owner->GetActorLocation();`
  * 最后用 UE_LOG 输出到日志（不输出到游戏内）
* UE_LOG 接口格式参照文档：https://wiki.unrealengine.com/index.php?title=Logs,_Printing_Messages_To_Yourself_During_Runtime
  * `UE_LOG(自定义类型，级别，输出内容)`
  * `UE_LOG(LogTemp, Warning, TEXT("%s"), *FString)`
    * FString 输出时要加 * 转成 TChar*
    * FVector 则先 .ToString() 再 *
  * 输出的内容在 `OutputLog` 查看
    * Window - Developer Tools - OutputLog 打开输出日志窗口

## 旋转椅子
```cpp
// pitch, yaw, roll
FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
Owner->SetActorRotation(NewRotation);   // 也可以四元数，此用 FRotator
```
* 还要在主界面编辑器中把椅子的属性从 static 改为 movable

## Debug
* 一开始一直没有反应，方得不行
* 然后发现不知道为什么这个 C++ 脚本没有 attach 到椅子下面 orz
* 鲨了我吧 QAQ

# 任务四：创建OpenDoor组件
## 准备工作
* 从 Content/StartContent/Props/ 中拖出门框和门，搭起来
* 给门创建 C++ 脚本 OpenDoor
  * 在 .h 中
  * 把开门的角度

## 将Cpp变量参数暴露到UE4编辑器
* 在 OpenDoor.h 中定义 `float Angle = 0.0f;`
* 使用 UPROERTY 宏把角度暴露到主界面编辑器：https://wiki.unrealengine.com/UPROPERTY
  ```cpp
  UPROPERTY(EditAnywhere)
  float Angle = 0.0f;
  ```
* `开门`：类似椅子的转动
    ```cpp
    FRotator NewRotation = FRotator(0.0f, Angle, 0.0f);
    AActor *Owner = GetOwner();
    Owner->SetActorRotation(NewRotation);
    ```

## 触发区域 Trigger Volume
* 从左侧 Modes 中拿出 box trigger 拖到场景
  * 拿错了！
  * 应该拿一个 trigger volume
  * 这个 box trigger 不能绑定到 triggervolume 类型上去的
* 使用前，先查文档，查到 ATriggerVolume 的头文件是 */Engine/TriggerVolume.h
* 要在 OpenDoor.h 中定义触发区域，就要获取它。此处 `先定义 ATriggerVolume 类型的空指针，用 UPROPERTY 暴露，然后到主界面编辑器中绑定到 box trigger`
    ```cpp
    UPROPERTY(EditAnyWhere)
        ATriggerVolume *TriggerArea = nullptr;
    ```
* 还要定义一个东西去触发这个区域
    ```cpp
    UPROPERTY(EditAnyWhere)
        AActor *ActorThatOpen = nullptr;
    ```
* `每一帧判断能触发这个区域的东西是不是在区域里`
    ```cpp
    void UOpenDoor::TickComponent(...)
    {
        // 判断 trigger 区域是否和能触发它的物体接触
        if (TriggerArea->IsOverlappingActor(ActorThatOpen))
        {
            OpenDoor(); // 需要先在 .h 中定义
        }
        else
        {
            CloseDoor(); // 需要先在 .h 中定义
        }
    }

    void UOpenDoor::OpenDoor()
    {
        FRotator NewRotation = FRotator(0.0f, Angle, 0.0f);
        AActor *Owner = GetOwner();
        Owner->SetActorRotation(NewRotation);
    }

    void UCloseDoor::CloseDoor()
    {
        FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
        AActor *Owner = GetOwner();
        Owner->SetActorRotation(NewRotation);
    }
    ```
* 注意对指针做保护
    ```cpp
    if (TriggerArea == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TriggerArea is NULL!"));
        return ;
    }
    ```
* `在开始时设置能触发区域的物体`
    ```cpp
    void UOpenDoor::BeginPlay()
    {
        // 先在 .h #include "Engine/World.h"
        // Pawn 继承自 actor
        ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
    }
    ```
* 

## 小技巧
* 运行时F8脱出角色。
* vs 注释快捷键：c+k+c, c+k+u
* 整个空 Pawn 用来试 Trigger 。
* `【！】`注意UPROPERTY的编辑如果GUI忘记绑定，有空指针没赋值运行秒崩orzzz所以一定要加判空！！！

# 任务五：学习射线和DebugLine
## 准备工作
* 考虑功能：用射线抓取物体
  * 是进入游戏后，我们所控制的角色能抓取物体
  * 因此要先得到我们控制的角色
  * 默认情况下是 UE4 自动生成的 DefaultPawn

## 使用自定义的 Pawn
* play 后根据 DefaultPawn ， detail 中 blueprint / add script 生成一个与 DefaultPawn 功能一样的蓝图-Pawn 并保存到 Content/Blueprint/
  * 这样就不用纠结于去自定义左右移动等功能，可以先动起来
* 要使用自定义的 pawn ，所以也要创建自己的 GameMode 去更改 default pawn
  * 因为 C++ 项目会有默认生成的 GameModeBase
  * 右键，create blueprint class based on it 创建蓝图 GameMode
  * 在这个蓝图 GameMode 中设置 `Default Pawn Class` 为 BP_DefaultPawn
  * 最后在 world settings - `Game Mode` 设置 BP_GameMode

## 让自定义的 Pawn 发出射线
* 给自定义的 Pawn 创建 C++ 组件：
  * 在 BP_DefaultPawn 中 `Add New C++ Component` - Actor Component : Grabber
* 生成 .cpp 和 .h 后
  * 先给 .h 添加 "GameFramework/Actor.h" 和 "Engine/World.h"
* **`发出射线`**
  * 首先要确定`射线起点和发射方向`
    ```cpp
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    // 传入引用，获取 Pawn 的所在位置和旋转方向，也即射线起点和行进方向
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
    ```
  * 第二步设定`射线长度`
    ```cpp
    // .h 中，可视到编辑器
    private:
        UPROPERTY(EditAnyWhere)
            float reach = 100.f;
    ```
  * 通过起点和长度获取`射线终点`
    ```cpp
    // 终点世界坐标 = 起点世界坐标 + 发射方向世界坐标的单位向量 * 长度
    FVector LineTraceEndLocation = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * reach;
    ```
  * 用 **`Functions - DrawDebugLine 绘制射线`** 
    ```cpp
    // 首先查完文档后先在 .h 中
    #include "DrawDebugHelper.h"

    // 再回到 .cpp
    DrawDebugLine
    (
        GetWorld(), // 传入所在世界
        PlayerViewPointLocation, // 起点
        LineTraceEndLocation, // 终点
        FColor(255, 0, 0), // 射线颜色
        false, // 是否一直显示（其实本身就写在 tick 里的话无所谓）
        0.0f, // 生命周期？
        0.0f, // ？
        10.0f // 射线粗细
    );
    ```
  * **`设定具有实际功能的射线：GetWorld()->LineTraceSingleByObjectType`**
    * 回忆：蓝图中使用的是 ByChannel ，但此处要根据物体的 Object Type 属性判断能不能把物体举起来（可以举桌子椅子不能举门），所以要用 ByObjectType
    * 物体的 Object Type 在 detail - `collision - collision presets` - object type ，未勾选 `simulate physics` 时为 WorldDynamic 类型，勾选后为 `PhysicsBody` 类型
    * 勾选 simulate physics 后再勾选 massinKg 设定质量
    ```cpp
    FCollisionQueryParams QueryParameter = FCollisionQueryParams("", false, GetOwner());

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType
    (
        HitResult, // 返回击中的第一个物体及相关信息
        PlayerViewPointLocation, // 射线起点
        LineTraceEndLocation, // 射线终点
        // 射线可击中的类型：到编辑器去看物体 simulate physics 后的 ObjectType 是啥
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
        QueryParameter // 撞击类型
    );
    ```
  * 关于 `FCollisionQueryParams`
    * 第一个参数填 空 `""`
    * 第二个参数设置射线能击中的形体：主界面编辑器视口左上的 Lit 可以切换到 `Player Collision` 查看物体的大致几何形状，也可以切换到 `Visibility Collision` 看更细致的几何形体。如果物体中间有空洞那么射线就可以穿过去。此处用较简单的 `Player Collision`，即参数使用 `false`。
    * 第三个参数设置射线忽略的物体。此处将发射射线的自己本身忽略掉 `GetOwner()`。
  * **`从 HitResult 中获取击中的物体`**
    * 查文档，发现 HitResult 中有记录击中的 AActor
    * 所以通过它获取，并检查是否为空
    ```cpp
    AActor *ActorHit = HitResult.GetActor();
    if (ActorHit != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("hit: %s"), *ActorHit->GetName());
    }
    ```

# <i class="fa fa-star"></i> 任务六：优化代码和举起物品
## 优化代码结构
* 把之前的关于“确定射线起点”和“确定射线终点”封装一下
  * `FVector GetLineStartPos();`、`FVector GetLineEndPos();`
  * 然后在 Draw 和 LineTrace 两处分别调用
* 一般在 tick 中也不写大段代码，所以把发射射线的部分也封装起来
  * `FHitResult GetFirstPhysicsBodyInReach();`

## 举起物品
* 考虑能发射射线后，要接收来自鼠标的按下和松开信息

### 使 Pawn 能够拿起物品
* 在 BP_DefaultPawn 添加 **component - `Physics Handle（UPhysicsHandleComponent）`** ，使 Pawn 能够抓取和移动物理对象
  * 启动后会为 BP_DefaultPawn 生成 **`PawnInputComponent`** ，用于接收输入
* Edit - Project Settings - Engine - input
  * 添加 Action Mappings
  * Grab - Left Mouse Button
  * 使系统能够接收来自鼠标左键的信息
### 使 Grabber 接收输入信息
* **`使 Grabber 获取输入信息`**
  * 开始时，从代码获取相应的输入组件 **`UInputComponent`** 和物理句柄组件 **`UPhysicsHandleComponent`**
  * 由于 Grabber 是 Pawn 的脚本，因此获取 Pawn 的相关组件和信息只要 `GetPawn()->` 就能调用
  * 再使用 **`FindComponentByClass<ClassName>()`** 即可通过类名获取相应组件
    ```cpp
    // .h 中
    UInputComponent *InputComponent = nullptr;  // 输入组件

    #include "PhysicsEngine/PhysicsHandleComponent.h"
    UPhysicsHandleComponent *PhysicsHandle = nullptr;   // 物理句柄组件

    // .cpp 的 BeginPlay() 中，开始时获取
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr) // 检查是否为空
    {
        UE_LOG(LogTemp, Error, TEXT("PhysicsHandle NOT FOUND!!!"));
    }

    InputComponent  = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("InputComponent NOT FOUND!!!"));
    }

    ```
* **`将输入具体按键的事件绑定到输入组件 UInputComponent`**
  * 用 **`InputComponent->BindAction(FName ActionName, EInputEvent KeyEvent, UserClass *Object, TBaseDelegate )`** 传入要绑定的
    * FName ActionName 事件名，是设置的 input - action mappings 项
    * EInputEvent KeyEvent 可以直接输入 EInputEvent::查看类型值，此用 IE_Pressed 和 IE_Released
    * UserClass *Object 要绑定的对象，即 InputComponent 本身，`this`
    * TBaseDelegate 事件的委托，也即 Grab() 函数，传入函数的地址 `&UGrabber::Grab`
  * 因此还需要先定义两个事件，抓取和放开
    ```cpp
    // .h 中
    void Grab();
    void Release();

    // .cpp 中
    void UGrabber::Grab()
    {
        // 测试是否能响应
        AActor *ActorHit = GetFirstPhysicsBodyInReach().GetActor();
        if (ActorHit == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Grab NOTHING!!!"));
        }
        else
            UE_LOG(LogTemp, Warning, TEXT("name: %s"), *ActorHit->GetName());
    }

    void UGrabber::Release() {...}

    // 最后在获取输入组件，判断非空后为输入组件绑定相关事件
    InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
    InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
    ```
    * Debug：
    *  `EInputEvent::` 没加，跟访问了空指针一样直接炸 orz ，这个竟然编译不报错吗？！不应该 undefined 量吗我晕 QAQ
    * 好的，加了继续炸。
    * 然后在两个 set 组件里 find 前后分别都瞎几把输出就不炸了？
    * 但是抓取物体的时候输出的名字是空的！！！惊恐！！！
    * 给抓取的 actor 判空并不是空……
    * 好的，忘记 `%s` 了，我是傻子吗=。=
    * 可是这不能解释为什么加了四句 UE_LOG 就不炸了啊？？？
    * 迷惑
### 举起物体
* 用 **`PhysicsHandle->GrabComponentAtLocationWithRotation()`** 将物体和物理句柄组件绑定
  * ->GrabComponent 据说已经废弃了，反正用最长的
* 参数列表
  * UPrimitiveComponent 所抓取物体的基本信息，包含 Transform 、 Static Mesh 等 detail 中的基本信息，用 FHitResult.GetComponent() 获取
  * FName 是否要举起某个骨骼 BoneName ，对于带骨骼的物体，可以更真实。此处不需要，用 `NAME_None` 给出空值
  * FVector Location 从要抓的物体获取
  * FRotator Rotation 从要抓的物体获取
    ```cpp
    void UGrabber::Grab()
    {
        FHitResult HitResult = GetFirstPhysicsBodyInReach();
        UPrimitiveComponent *ComponentToGrab = HitResult.GetComponent();

        if (HitResult.GetActor() != nullptr)
        {
            PhysicsHandle->GrabComponentAtLocationWithRotation
            (
                ComponentToGrab, 
                NAME_None,
                HitResult.GetActor()->GetActorLocation(),
                HitResult.GetActor()->GetActorRotation()
            );
        }        
    }
    ```
* 此时举起来了，但是物体还没动

### 移动物体：每一帧判断句柄是否绑定物体，是则`刷新绑定物体的位置`
    ```cpp
    void UGrabber::TickComponent(...)
    {
        if (PhysicsHandle->GetGrabbedComponent() != nullptr)
        {
            // 把绑定物体位置刷新到射线末端
            PhysicsHandle->SetTargetLocation(GetLineEndPos());
        }
    }
    ```


### 松开物体
```cpp
void UGrabber::Release()
{
    // 判断当前是否抓着物体
    if (PhysicsHandle->GetGrabbedComponent() != nullptr)
    {
        PhysicsHandle->ReleaseComponent();  // 放开物体
    }
}

```

## 小技巧
* Visual Studio - 右键声明 - 快速操作和重构 - 创建声明/定义
  * 自动根据 .h 的声明创建定义
* 在封装时，选定语段，右键快速操作和重构，提取函数
  * 自动在 .h 和 .cpp 生成相应声明及定义
  * 在原地给出一个调用

# <i class="fa fa-star"></i> 任务七：通过重量判定开门
## 调整 BP_DefaultPawn
* `物理模拟（不飘）`：到 BP_DefaultPawn 里为其勾选 simulate physics，并设质量
* `视线高度`：在 BP_DefaultPawn(self) 设置 camera - `Base Eye Height`
* `移动速度`：MovementComponent - details - Floating Pawn Movement - `Max Speed 等几个量`
* 由于 DefaultPawn 是个球体，所以如果把东西举起来再放下，碰到自己会瞎几把滚。到 collision component 里把 constraint 的 rotation 锁住。

## 判定重量
* 首先，把物体放入区域，再根据物体的重量做判断。要使物体能触发区域的 `overlap` 事件。
  * 主界面编辑器中，选中物体，勾选 collision - **`Generate Overlap Events`**
  * 别勾错，collision 里第一项是 Hit Events
* 实现重量判定
  * `ATriggerVolume.GetOverlappingActors(TArray<AActor*>)` 获取与区域重叠的物体，返回到 TArray<AActor*> 中
  * 要遍历数组并获取每个物体的质量，即要 `GetMass` ，查文档，发现要使用 UPrimitiveComponent （很怪，document 里面查不到，只能在官网首页查）
  * 所以再用 `AActor.FindComponentByClass<ClassName>()` 找到相应组件
  * 记得加头文件
```cpp
// OpenDoor.h 中
#include "Components/PrimitiveComponents.h"
UPROPERTY(EditAnyWhere)
    float MassToOpen = 25.f
float GetTotalMassOfActors();

// OpenDoor.cpp
float UOpenDoor::GetTotalMassOfActors()
{
    // 获取区域中的物体
    if (TriggerArea == nullptr) // 加指针判定，在哪用在哪判定
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerArea is NULL!!!"));
		return -1.f;
	}
    TArray<AActor*> OverlappingActors;
    TriggerArea->GetOverlappingActors(OverlappingActors);

    float TotalMass = 0.0f;
    for (AActor *Actor:OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    return TotalMass;
}

// 当然 tick 里面也记得改一下
```

# <i class="fa fa-star"></i> 任务八：蓝图与 C++ 的互相调用
## 蓝图中调用 C++
### **1° 根据 StaticMeshActor 创建蓝图**
* 主界面编辑器选中物体，点 Blueprint （蓝色按键）创建 BP_OpenableDoor
* 原来的 StaticMeshActor 变为 BP_OpenableDoor
  * 注意 opendoor c++ 脚本绑定的 TriggerArea 失效，要重新绑定

### **2° 用蓝图调用 C++ 脚本**
* 在 C++ 脚本的 .h 声明函数时用宏 **`UFUNCTION(BlueprintCallable)`** 使其能被蓝图调用，如
```cpp
UFUNCTION(BlueprintCallable)
    void TestFuncFromC();
```
* 其它参数
  * `Category = "xxx"` ：用于在蓝图里创建 c++ 脚本结点后，拉出时有一页新的标签页 xxx ，而被该句宏声明的函数会显示在这个标签页的下拉条内。
* 然后在蓝图 event graph 中 beginplay 处调用即可。

## C++ 中调用蓝图
### **1° 为 C++ 类创建蓝图组件**
* 之前的 BP_OpenableDoor 蓝图是 OpenDoor C++ 类的父组件，所以不能子调父
* 因此要为 OpenDoor 创建它的蓝图，但是此时在项目内容中右键 OpenDoor 不能创建蓝图，所以要到 .h 中改一下 UCLASS
* **`UCLASS()`**
  * 在参数列表前加一项 **`Blueprintable`**
* 回到项目内容，右键 OpenDoor 创建蓝图 BP_OpenDoor
  * 在 BP_OpenDoor 编辑器内右上角，父类为 OpenDoor

### **2° C++ 内调用蓝图**
* 在蓝图内创建 function - TestFuncFromBP
  * 为函数增加 input
  * 直接用 print string 输出这个 input
* 由于 BP_OpenDoor 继承自 OpenDoor ，所以 OpenDoor 的功能它还都有。
* 到 C++ OpenDoor.cpp 的 BeginPlay 中调用 BP_OpenDoor 的函数 TestFuncFromBP
  * **`CallFunctionByNameWithArguments(TCHAR*, FOutputDevice, ...)`**
  * `TCHAR*` 从 FString 转，内容为 `蓝图中的 FuncName + 参数列表` ，中间以空格分割
    * `FString cmd = FString::Printf(TEXT("TestFuncFromBP hello"));`
    * FString::Printf 以经典 C 的 printf 形式构造 FString
  * `FOutputDevice` 
    * `#include "Misc/OutputDeviceDebug.h"` 随便 include 一个 outputdevice 子类头文件并创建它
    * `FOutputDeviceDebug device;`
  * 第三个参数 NULL 即可
  * 第四个参数表示是否强制执行，true
```cpp
void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();
    
    FString cmd = FString::Printf(TEXT("TestFuncFromBP hello"));
    FOutputDeviceDebug device;
    CallFunctionByNameWithArguments(*cmd, device, NULL, true);
}
```

### **`C++ 以创建代理的方式调用蓝图`**
* 在 .h 中创建代理 `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestRequest);`
  * 参数要以 F 开头
* 在 .h 的类定义中声明代理
  * 用宏 **`UPROPERTY(BlueprintAssignable)`** 。 BlueprintAssignable：Usable with multicast delegate only.
    ```cpp
    public:
        UPROPERTY(BlueprintAssignable)
            FTestRequest OnTestRequest;
    ```
* 在 .cpp 的 BeginPlay 处使用：做广播，给蓝图发送信息
    ```cpp
    BeginPlay()
    {
        ...;
        OnTestRequest.Broadcast();
    }
    ```
* 编译一下。
* 到 BP_OpenableDoor 中，点住 OpenDoor 组件，在 event graph 中右键 all actions for this blueprint - add event for Open Door - Event Dispatchers - `Add On Test Request`
  * 于是就可以通过这个事件触发结点，在蓝图里面搞事情
  * 而这个事件的触发点就是由 C++ 决定，在哪用它 broadcast 就在哪调用
* 与 Call 方式的不同： Call 需要先通过 c++ 生成蓝图，而这种方式不需要。可以直接用。

# <i class="fa fa-star"></i> 任务九：通过 TimeLine 开门
## 过程性开门
* 用上述创建代理的方式调用蓝图，在蓝图里用 TimeLine 开门，过程不赘述
* 问题：**`在蓝图中调用 C++ 的变量 Angle`**
  * 使用 **`UPROPERTY(BlueprintReadOnly) / (BlueprintReadWrite)`**
  * 给变量 Angle 的宏加一项参数
* 简化：关门的时候可以直接连 TimeLine 的 `Reverse`
* Debug
  * TimeLine 连到 play from start 了所以门一直没反应
  * 应该是因为帧间隔时间很短，所以每帧 from start 一直从 0 开始，门还没开又被重置了
  * 连到 play 解决

## 开门过程加声音
* 给 TimeLine 增加 `Event Track` - Play Sound
  * 添加点，设定 TimeLine 行进到某时刻，触发事件
  * 门 (0.3, 1) ，此设 (0.1, 1) 刚开门的时候触发声音
* 从 Play Sound 连出结点 `Play Sound At Location`
  * `Get Actor Location`
  * 选择音频

## 给门加碰撞体
* 到 Content/ 中找 SM_Door
* 进入静态网格编辑器
* 加碰撞体，simple 没有的话就去加加 box 之类的

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
  * 不过好像不能存蓝图相关的文件嗷？
* 插播一下 UE4 项目文件结构
* **`Windows 10 项目目录（~\Demo1）内容`**

    文件夹名        | 内容
    --------        | ------
    .vs             | VS生成的临时目录。（版本库可忽略）
    Binaries        | C++编译输出的动态链接库。（版本库可忽略）
    Config          | 工程配置文件。（手动修改/UE4GUI中改）
    Content         | 资源目录。（专用二进制存储，只能编辑器导入，不能手动拷入该目录）
    Intermediate    | 临时文件。（版本库可忽略）
    Saved           | 自动存储文件及日志信息。（版本库可忽略）
    Source          | C++代码存放路径。
    Demo1.sln       | VS工程文件。生成方法：UE4编辑器->文件->生成VS工程。（版本库可忽略）
    Demo1.uproject  | UE4项目工程文件。（json格式）

* Source目录
  * 项目同名文件夹Demo1：.cpp、.h、`.Build.cs`（描述当前工程依赖的库文件）
    * Demo1.h：预编译头文件，加快编译速度。`该目录下所有cpp文件需包含该头文件`【？】，其内也有通用而不会修改的代码。
  * 两个c#文件：`<Demo1>`.Target.cs（`类似于Makefile`的编译脚本）、`Demo1Editor`.Target.cs（构建编辑器相关代码，工程中存在依赖于UnrealEd的代码时，要放到Editor模块下，不能和Runtime放一起，否则无法打包）
* 子工程Module
  * 子工程在工程文件*.uproject中定义。
  * 添加子工程：Modules属性下添加引用，Source目录添加工程文件夹和编译文件*.Target.cs
# **End**
<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->