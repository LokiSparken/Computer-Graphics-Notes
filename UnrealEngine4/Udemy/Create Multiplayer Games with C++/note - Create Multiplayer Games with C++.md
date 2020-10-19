> # Create Multiplayer Games with C++
> * https://www.udemy.com/course/unrealengine-cpp/

## Preparation
### Visual Studio settings
* Visual Assist X shortcut
  快捷键 | 功能
  :----:|:----:
  Alt + O | 在 .h 和 .cpp 之间切换
  Shift + Alt + O | 在解决方案中查找文件
  Shift + Alt + S | 查找任意符号
  Alt + G | 在定义和实现之间切换
* 基本设置 https://docs.unrealengine.com/zh-CN/Programming/Development/VisualStudioSetup/index.html
* VS 2017 建议不关闭 options - text editor - c/c++ - advanced - intellisense - disable squiggles
### UE4 Editor setting
* blueprint - compile - save on compile - On Success Only

## 常见问题
* **`已绑定事件但无法触发`**
  * 可能原因：未绑定成功
  * 建议：将 `AddDynamic` 放到 `BeginPlay()` 时调用
* **`热重载问题`**
  * 如：在构造函数中改变量值后无法正确加载属性（更改不生效）、编辑器运行时在 VS 中加了新函数等
  * 建议：关掉 UE4 编辑器，直接在 VS 中编译


## 预热：爆炸特效
* `使用粒子系统`：**`UGameplayStatics::SpawnEmitterAtLocation()`**

## 一、拾取物体
### 1. 创建类
* New C++ Class - Actor - FBSObjectiveActor
* 基于 FBSObjectiveActor 创建 BP_Objective
### 2. 绑定组件（in C++）
* 选取一个拾取物体的地点，并放置 BP_Objective 
* **`为 Actor 绑定组件`**
    ```cpp
    // FBSObjectiveActor.h
    class USphereComponent;
    UCLASS()
    class xxx_API AFPSObjectiveActor : public AActor    
    {
        // 静态网格体组件，蓝图可见
        UPROPERTY(VisibleAnywhere, Category = "Components")
        UStaticMeshComponent *MeshComp;
        // 球体组件，蓝图可见
        UPROPERTY(VisibleAnywhere, Category = "Components")
        USphereComponent *SphereComp;
    }
    ```

    ```cpp
    // FBSObjectiveActor.cpp
    #include "Components\\SphereComponent.h"
    AFPSObjectiveActor::AFPSObjectiveActor()
    {
        // 根据指定类创建默认子对象
        MeshComp = CreateDefaultSubobject<UStaticMeshComponent>（TEXT("MeshComp")）;
        RootComponent = MeshComp;   // 将静态网格体组件设为根组件

        SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
        // 将球体组件附加到网格体组件上
        SphereComp->SetupAttachment(MeshComp);
    }
    ```
  * 小技巧：发现没高亮的时候，Shift + Alt + O 查类名位置，关注 Private/Classes 之后的部分 include
  * 头文件直接加在 .cpp 中， .h 中使用向前声明告知那是一个类。（据说不要在头文件里加太多东西，会影响编译时间？）
  * 球体组件附加到网格体组件：网格体的移动会带动球体
* 编译后为 SphereComp 添加网格体 EditorSphere
  * 调整大小 Scale
* 静态网格体组件设为无碰撞（蓝图中）
  * collision - `collision presets`
  * `BlockAllDynamic` 改为 `NoCollision`
### 3. 设置碰撞和重叠事件
#### 设置碰撞属性
```cpp
#include "Components/StaticMeshComponent.h"
// 禁用静态网格体组件的碰撞属性
MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

// 不需要球体组件的物理效果，只使用查询 Line Traces 、 Overlap Events 等
SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
// 设置通道：相应所有通道
SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
// 为 Pawn 人形体通道启用碰撞
SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
```
* `ECR_Overlap` 使发射物击中目标物体时不受阻，直接穿过对象
#### 重叠事件：重叠时生成粒子效果（捡起物体特效）
* **`生成粒子效果`**
    ```cpp
    // .h
    protected:
        void PlayEffects();

    // .cpp
    #include "Kismet/GameplayStatics.h"
    void AFPSObjectiveActor::PlayEffects()
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
    }
    ```
    * **`SpawnEmitterAttached`** 附加到物体
    * **`SpawnEmitterAtLocation`** 附加到特定位置，对静止物体而言就使用其位置即可
        * `UObject *WorldContextObject`：this，用于获取世界场景上下文，明确在哪个世界场景中注册相应粒子效果
        * `UParticleSystem *EmitterTemplate`：PickupFX
        * `FVector Location`：`GetActorLocation()`
* **`创建粒子系统`**
    ```cpp
    // .h
    protected:
        UPROPERTY(EditDefaultsOnly, Category = "Effects")
        UParticleSystem *PickupFX;
    ```
    * 暴露到蓝图中进行赋值
    * `EditDefaultsOnly`：property can be changed only for Blueprints, in Blueprint->Defaults
* **`物体重叠时调用`**
  * 注册到球体组件的重叠事件：`SphereComp->OnComponentBeginOverlap()`
  * 使用 Actor `NotifyActorBeginOverlap` （想找接口时可以到相关类型的父类文件里查查看）
        ```cpp
        // .h
        public:
            virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

        // .cpp
        void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor *OtherActor)
        {
            Super::NotifyActorBeginOverlap(OtherActor);

            PlayEffects();
        }
        ```
### 4. 拾取物体
* 逻辑
  * FPSObjectiveActor 的 NotifyActorBeginOverlap 发生
  * 检查是否与 FPSCharacter 中角色类型发生重叠（已在碰撞设置中将过滤条件设为仅对 Pawn 有效，此处再用 cast 来 check 是否是对应需要的类型）
    ```cpp
    // FPSCharacter.h
    public:
        UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
        bool bIsCarryObjective;
    
    // FPSObjectiveActor.cpp
    #include "FPSCharatcer.h" 
    void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor *OtherActor)
    {
        AFPSCharacter * MyCharacter = Cast<AFPSCharacter>(OtherActor);
        if (MyCharacter)
        {
            MyCharacter->bIsCarryObjective = true;

            Destroy();
        }
    }
    ```
### 5. 向用户显示信息
#### 创建 UMG
* 创建文本 UI - UMG
  * 在 Content/UI 下创建 User Interface - Widget Blueprint - WBP_ObjectiveInfo
  * 添加 Text 控件
  * text - details - size to content 使大小适应文本内容
  * font - size 调整文本内容大小
* 应用 UMG
  * 在 Content/Blueprints 下创建 HUD - FPSHUD - BP_HUD
  * 在 Event Graph 中 `Create Widget`，target = WBP_ObjectiveInfo
  * 将 Create Widget Return Value `Add to Viewport`
* 应用 HUD
  * 在 Content/Blueprints 下创建 FPSGameMode - BP_GameMode
  * Classes - HUD Class 设为 BP_HUD
* 应用 GameMode
  * 主界面 World Settings - GameMode - GameMove Override 设为 BP_GameMode
* **`发生事件时修改文本信息`**
  * bind get text 0 - GetObjectiveText
  * 创建变量 Text - GetObjective、ExtractArea 并设置对应文本
  * get text 蓝图界面中 select，index = Boolean
  * 通过结点 **`Get Owning Player Pawn`** 找到玩家控制的 Pawn ，Return Value 用 `isValid` 或 `Cast To FPSCharatcer` 检查是否有效，此用 Cast （转换成功即有效）
  * 根据相应情况显示文本
### 6. Challenge：黑洞
* 一个会吸入周围 Actor 的黑洞
  * Sphere Component，Create and Destroy
  * Physics：`AddForce()`、`AddRadialForce()`
  * Find Nearby Actors：`SphereComp->GetOverlappingComponents` in `Tick()`
  * check all actors `Generate Overlap Events`
* p15 02:42

## 二、游戏规则
* 规则
  * 玩家将目标物体带至通关区域范围即完成任务。
  * 向玩家显示相应通知。
  * 暂停接收玩家输入。
  * 镜头离开玩家，切至下一关。
### 1. 通关口 Extraction Zone
* 创建 C++ 类 - Actor - FPSExtractionZone
* 添加盒体组件、重叠组件（检测重叠事件）
    ```cpp
    // FPSExtractionZone.h
    class UBoxComponent;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent *OverlapComp;

    // FPSExtractionZone.cpp
    #include "Components/BoxComponent.h"
    AFPSExtractionZone::AFPSExtractionZone()
    {
        OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
        OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
        OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
        // 设置盒体区域的响应范围
        OverlapComp->SetBoxExtent(FVector(200.0f));
        // 设为根组件
        RootComponent = OverlapComp;
        // 显示重叠组件
        OverlapComp->SetHiddenInGame(false);
        // 创建与玩家发生重叠时的事件
        OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
    }
    ```
* 定义绑定到重叠事件的代理函数
    * OnComponentBeginOverlap Alt + G 转到定义
    * 对其类型 Alt + G 转到定义
    * 找到 `DECLARE_DYNAMIC_MULTICAST_DELEGATE_*()` ：声明了代理，把首项去掉，后面的参数列表作为要定义的代理函数的参数，去掉类型和名称间的分隔逗号
    * 要标记为 UFUNCTION() ，通知虚幻后端该函数的含义及如何与事件绑定
    ```cpp
    // FPSExtractionZone.h
    UFUNCTION()
    void HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

    // .cpp
    void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
    {
        // 判断玩家是否携带目标物体
        UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone!"));
    }
    ```
* 使用重叠组件
  * 主界面左侧 Modes 中 search classes - FPSExtractionZone 拖入场景
  * `显示重叠组件`：`SetHiddenInGame`
### 2. 完善通关口
* 向项目的 Content 添加内容
  * 右键 Content - Show in Explorer
  * Ctrl + 把 Materials 拖入
* **`贴花组件`**
    ```cpp
    // FPSExtractionZone.h
    protected:
        UPROPERTY(VisibleAnywhre, Category = "Components")
        UDecalComponent *DecalComp;
    
    // .cpp
    #include "Components/DecalComponent.h"
    AFPSExtractionZone::AFPSExtractionZone()
    {
        // 创建对象
        DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
        // 尺寸与通关口范围一致。API 可 Alt + G 到相关头文件里查。
        DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
        // 
        DecalComp->SetupAttachment(RootComponent);
    }
    ```
    * 主界面中找到 DecalComp 为其设定材质 SpawnBox_M_Inst
    * 原材质颜色太亮，在强光照下不明显，把花纹调暗。将 SpawnBox_M 材质的 Opacity（不透明度）Clamp 的 Min Default 设高到 0.15 。
    * 基于 ExtractionZone 创建 BP_ExtractionZone ，便于更改 C++ 中设置的默认值 
    * DecalComp 相对 ExtractionZone 有偏移，重置 Location
    * 角度旋转 90 度
### 3. 游戏模式：通关规则
```cpp
// FPSExtractionZone.cpp
#include "FPSCharacter.h"
#include "FPSGameMode.h"
void AFPSExtractionZone::HandleOverlap(...)
{
    // 类型转换，并判断玩家是否携带目标物
    AFPSCharacter *MyPawn = Cast<AFPSCharacter>(OtherActor);
    if (MyPawn && MyPawn->bIsCarryObjective)
    {
        // 通知【游戏模式】目前的游戏状态
        AFPSGameMode *GM = Cast<FPSGameMode>(GetWorld()->GetAuthGameMode());
        if (GM)
        {
            GM->CompleteMission(MyPawn);
        }
    }
}
```
* `GetWorld()` 返回当前游戏世界
* `GetAuthGameMode()` 返回当前世界游戏模式的引用，仅在服务器上有效
```cpp
// FPSGameMode.h
public:
    void CompleteMission(APawn *InstigatorPawn);

    UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
    void OnMissionCompleted(APawn *InstigatorPawn);
```
* `UFUNCTION(BlueprintImplementableEvent)` 通过蓝图实现
```cpp
// FPSGameMode.cpp
void AFPSGameMode::CompleteMission(APawn *InstigatorPawn)
{
    if (InstigatorPawn)     // check
    {
        InstigatorPawn->DisableInput(nullptr);  // 禁用输入
    }
    OnMissionCompleted(InstigatorPawn);
}
```
* Pawn 与 PlayerController 
  * Pawn 生成后由 PlayerController 控制，输入经由 PlayerController 转换后发送给 Pawn
  * `DisableInput(nullptr)` 禁用对角色 Pawn 输入，但不阻止对 PlayerController 的输入（如调出游戏菜单等）
### 4. 添加通关反馈
* **`文字提示`**：创建提示任务完成的 UI Widget
  * 创建新的 Widget - WBP_GameOver
  * 放入 Text ，Anchor 调整至屏幕中心，重置 Text Position ，并放在屏幕中心上部。
* 在 BP_GameMode 蓝图中完成上述暴露给蓝图实现的函数 `OnMissionCompleted` ，向玩家显示任务完成提示
  * Create Widget(WBP_GameMode, default) -> Add to Viewport
  * Owning Player 保留默认值
* **`音效提示`**：未携带目标物进入通关口时的未完成提示
    ```cpp
    // FPSExtractionZone.h
    protected:
        UPROPERTY(EditDefaultsOnly, Category = "Sounds")
        USoundBase *ObjectiveMissingSound;
    ```
    * `EditDefaultsOnly` 游戏启动后无法编辑，只能在为其创建蓝图版本时进行编辑
    * 在 `BP_ExtractionZone` 中设置音效：details - sounds - objective missing sound
* 在 `HandleOverlap` 中调用
    ```cpp
    // FPSExtractionZone.cpp
    #include "Kismet/GameplayStatics.h"
    void AFPSExtractionZone::HandleOverlap(...)
    {
        AFPSCharacter *MyPawn = Cast<AFPSCharacter>(OtherActor);
        if (MyPawn == nullptr)
        {
            return;
        }

        if (MyPawn->bIsCarryObjective)
        {
            AFPSGameMode *GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
            if (GM)
            {
                GM->CompleteMission(MyPawn);
            }
        }
        else
        {
            UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
        }
    }
    ```
    * `UGameplayStatics` 中均为静态函数
    * `PlaySound2D` 播放声效，将信号传输至音频引擎
### 5. 视角切换
* 蓝图实现：`BP_GameMode` 中
  * 用 **`Sequence`** 接出另一条执行线
  * `获取控制器`：从 `Event On Mission Completed` 结点的 `Instigator Pawn` 拉出结点 **`Get Controller`** 并 **`Cast to PlayerController`** 
  * `更改视角`：`Cast As Player Controller` -> `Set View Target with Blend` 
  * `创建新视角`
    * 新建蓝图 Actor - BP_SpectatingViewpoint
    * 添加组件 StaticMesh ，设定 Static Mesh - MatineeCam_SM 
    * **`在游戏中隐藏`**：StaticMesh - details - Rendering - Hidden in Game
    * 将 BP_SpectatingViewpoint 拖入场景，右键 `Pilot` 调整视角
  * `应用新视角`
    * 回到 `Set View Target` 
    * `获取新视角`：**`Get All Actors of Class`** ，`Actor Class` 设为 BP_SpectatingViewpoint ，返回值 Out Actors -> `Get (a copy)` 
  * `视角切换优化`：仍然是 `Set View Target with Blend`
    * `Blend Time`：0.5
    * `Blend Func`：Cubic
* **`C++ 实现`**
    ```cpp
    // FPSGameMode.h
    protected:
        UPROPERTY(EditDefaultsOnly, Category = "Spectating")
        TSubclassOf<AActor> SpectatingViewpointClass;

    // FPSGameMode.cpp
    #include "Kismet/GameplayStatics.h"
    void AFPSGameMode::CompleteMission(APawn *InstigatorPawn)
    {
        if (InstigatorPawn)
        {
            ...
            if (SpectatingViewpointClass)   // check 新视角存在
            {
                // 获取新视角
                TArray<AActor *> ReturnedActors;
                UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

                if (ReturnedActors.Num() > 0)
                {
                    AActor *NewViewTarget = ReturnedActors[0];

                    // 获取控制器
                    APlayerController *PC = Cast<PlayerController>(InstigatorPawn->GetController());
                    if (PC)
                    {
                        // 应用新视角，并设切换过渡时间
                        PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target."));
            }
        }
        
    }
    ```
    * 编译后到蓝图中给 SpectatingViewpointClass 赋值为 BP_SpectatingViewpoint
    * 接口名与蓝图中类似，主要根据接口所需传入的参数逆推需要的变量
### 6. Challenge：发射平台
* 把人弹飞
  * 在 `LaunchCharacter()` 单个函数中完成，内置在 Character Class 中
  * 添加粒子效果
  * 可以把物体（如蓝色方块）也弹飞：Generate Overlap Events on blue cubes
* 关键点
  * 碰撞组件：球体/盒体碰撞组件，判定人物或物体是否与其重叠
  * 
* p22 02:23

## 三、AI 基础
* AI 行为
  * 守卫目标物
  * 能看到玩家，听到周围动静
  * 对守卫有干扰机制（可声东击西）
### 1. AI 守卫
* New C++ Class - Character - FPSAIGuard
  * Character 比 Pawn 多的内容：Static Mesh 组件、角色的移动
  * 不涉及玩家，可将 SetupPlayerInputComponent 部分删掉
  * 增加 Content 资源
* 基于 FPSAIGuard 创建 BP_Guard
  * `使用模型`：Mesh - details - Mesh - skeletal Mesh 使用导入的 DwarfGrunt_R_new
  * 调整位置 -80，调整胶囊碰撞体高度 Shape - Capsule Half H... = 60
  * 面向 X 轴方向（红轴方向）：Rotation_Z = -90
  * `设置动画效果`：details - animation - animation mode - use animation assets，anim to play 中选择动画效果 Idle
* **`人形体感应组件 PawnSensingComponent`**
    ```cpp
    // FPSAIGuard.h
    class UPawnSensingComponents;

    protected:
        UPROPERTY(VisibleAnywhere, Category = "Components")
        UPawnSensingComponent *PawnSensingComp;
    
    // FPSAIGuard.cpp
    #include "Perception/PawnSensingComponent.h"
    AFPSAIGuard::AFPSAIGuard()
    {
        PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
    }
    ```
    * **`添加 AI 模块`**：由于 AI 模块不在 Engine 或 Core 模块中，所以要在 `FPSGame.Build.cs` 的 `PublicDenpendencyModule` 添加模块依赖 `AIModule`
* 拽个 BP_Guard 进场景看效果 w（有丶可爱哈
### 2. 视觉感应
#### **`PawnSensingComponent`**
* 贼多放射线！（Debug Lines）
* 类似 `CharacterMovement` ，是 `Actor` 组件而非场景组件，没有确定的位置，无法附加到其它组件
* details - AI
  * Peripheral Vision ...：视野范围 FOV
  * Sight Radius：视野半径
  * Hearing Threshold：有遮挡最大听距
  * LOSHearing Threshold：无遮挡直线听距（$> Hearing Threshold$）
* details - Events
  * `On See Pawn`
  * `On Hear Noise`
* **`绑定视觉事件`**
    ```cpp
    // FPSAIGuard.cpp
    AFPSAIGuard::AFPSAIGuard()
    {
        PawnSensingComp->OnSeePawn.AddDynamic(this, &APFSAIGuard::OnPawnSeen);
    }
    ```
    * 查源码找到所需定义的函数接口形式
      * 注意标记为 `UFUNCTION()` ，否则会 `unable to bind delegate (function might not be marked as a UFUNCTION)`
    * 事件在 AIGuard 发现 Pawn 类型物体时触发
      * 需判定所发现的是其它 AI 还是玩家
      * 如果是玩家则 Game Over
    ```cpp
    // FPSAIGuard.h
    protected:
        UFUNCTION()
        void OnPawnSeen(APawn *SeenPawn);

    // FPSAIGuard.cpp
    #include "DrawDebugHelpers.h"   // 先随便画点东西当做反应
    void AFPSAIGuard::OnPawnSeen(APawn *SeenPawn)
    {
        if (SeenPawn == nullptr)
        {
            return;
        }
        DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
    }
    ```
* UE4 小技巧：运行中 `F1` 切……透视图？透视世界？
### 3. 听觉感应
* 基本设置类似视觉感应
* 触发听觉感应事件所需绑定的函数代理
    ```cpp
    // FPSAIGuard.h
    protected:
        UFUNCTION()
        void OnNoiseHeard(APawn *NoiseInstigator, const FVector &Location, float Volume);
    
    // FPSAIGuard.cpp
    void AFPSAIGuard::OnNoiseHeard(APawn *NoiseInstigator, const FVector &Location, float Volume)
    {
        Instigator
        DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);
    }
    ```
    * 由于 Actor 中本身定义有 Instigator ，会重名，因此找到的接口示例中 Instigator 需重命名一下。（编译时报错：`Function parameter: 'Instigator' cannot be defined in 'OnNoiseHeard' as it is already used`）（看起来 UE4 的类里面仿佛制止了变量名覆盖这种特性【？】）
* **`为玩家人物添加声音发射器组件 NoiseEmitterComponent`**
    ```cpp
    // FPSCharacter.h
    class UPawnNoiseEmitterComponent;

    protected:
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
        UPawnNoiseEmitterComponent *NoiseEmitterComponent;

    // FPSCharacter.cpp
    #include "Components/PawnNoiseEmitterComponent.h"
    AFPSCharacter::AFPSCharacter()
    {
        NoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
    }
    ```
    * 命名方式与原 Character 类中的变量保持一致。
    * 在 `PawnNoiseEmitterComponent.h` 中可以发现 `MakeNoise()` 接口
* **`制造声音`**
  * BP_Player event graph - 先用 Tick event 测试 - 结点 **`Pawn Make Noise`** ，参数输入注意 information：if zero vector, use the actor's location 因此 Noise Location 可为空。
  * 【？】问题：触发视觉感应时，听觉感应组件失效。（貌似是 Pawn 的特性？）
### 4. 给发射物附加触发 AI Guard 听觉感应的声效
```cpp
// FPSProjectile.cpp
void AFPSProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    // 发射物击中物体时发出音效
    MakeNoise(1.0f, Instigator);
    Destroy();  // 挪下来的
}
```
* MakeNoise 会 check 传入的 Instigator 是否具有 PawnNoiseEmitterComponent 而可发出声音
```cpp
// FPSCharacter.cpp
void AFPSCharacter::Fire()
{
    if (ProjectileClass)
    {
        FActorSpawnParameters ActorSpawnParams;
        ActorSpawnParams.SpawnCollisionHandlingOverride = ESPawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
        ActorSpawnParams.Instigator = this; // 将 Actor 自带的 Instigator 设为本 Character 自身
    }
}
```
* `ActorSpawnParams.Instigator = this;` 使 Projectile 调用时传入的 Instigator 为当前 Character
* 调整感官感应组件的感应间隔
  * BP_Guard - PawnSensingComponent - details - AI - `Sensing Interval`
### 5. 干扰 AI
* 逻辑：当有声音时让 AI 转向发声处
* 实现：
  * 蓝图库 KismetMathLibrary 中有 `LookAtRotation`
  * 【？】不直接调用蓝图函数，用它返回的 `MakeRotFromX()` （可能是因为效率问题？），再找一层，发现 `FRotationMatrix::MakeFromX(FVector X).Rotator();`
    ```cpp
    // FPSAIGuard.cpp
    void AFPSAIGuard::OnNoiseHeard(...)
    {
        // 把位置转换为方向
        FVector Direction = Location - GetActorLocation();
        Direction.Normalize();
        // 获取转向 rotator
        FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
        // 设置新的 rotation
        SetActorRotation(NewLookAt);
    }
    ```
    * 优化：令 Guard 只做左右转动（只更改 `Yaw` 值，`Pitch` 上下，`Roll` 倾斜），设 NewLookAt.Pitch/Roll = 0.0f
* 调试：
  * UE4 小技巧：运行时 `~` 调出控制台，`show collision` 显示碰撞体
* `受干扰一定时间后回到初始状态`
  * 记录初始状态
    ```cpp
    // FPSAIGuard.h
    protected:
        FRotator OriginalRotation;

    // FPSAIGuard.cpp
    void AFPSAIGuard::BeginPlay()
    {
        OriginalRotation = GetActorRotation();
    }
    ```
  * **`设置计时器`**
    ```cpp
    // FPSAIGuard.cpp
    void AFPSAIGuard::OnNoiseHeard(...)
    {
        SetActorRotation(NewLookAt);

        FTimerHandle TimerHandle_ResetOrientation;
        GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);
    }

    // .h 定义重置函数，用于绑定到计时器，用于执行
    UFUNCTION()
    void ResetOrientation();

    // .cpp 实现重置函数
    void AFPSAIGuard::ResetOrientation()
    {
        SetActorRotation(OriginalRotation);
    }
    ```
    * 计时器参数看接口
    * 此时多次干扰，之前干扰产生的时间句柄先执行重置，会让之后的干扰时效缩短。所以要`复用计时器`
    ```cpp
    // 句柄声明放到 .h protected
    // 清除原先的计时器
    GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
    GetWorldTimerManager().SetTimer(...);
    ```
### 6. 游戏模式：死亡规则
* 规则：被守卫发现就 Game Over
  * 显示 Game Over
  * 切换相机视角
  * 取消 Pawn 控制权
* 修改 Game Mode
  * 为 `FPSGameMode::CompleteMission()` 增加参数 `bool bMissionSuccess`
  * 通知 Game Mode 任务完成处的调用传入 `true`
  * 守卫发现即 `AFPSAIGuard::OnPawnSeen()` 处类似调用，并传入 `false`
* 修改 UI 显示的文字
  * WBP_GameOver 添加变量 bMissionSuccess ，并勾选 details - `Instance Editable` 和 `Expose on Spawn`（在 BP_GameMode 中的 Create Widget 刷新后会显示该变量）
  * 然后把 BP_GameMode - Event Graph - Event On Mission Completed - Mission Success 接到 Widget 的 Mission Success
  * 在 WBP_GameOver 给 Text 绑定函数：进入函数蓝图， `Get Mission Success` - `Select` 根据不同值指定文本，返回值连到 `Return Node`
### 7. 在守卫头顶添加 3D UI 反应
* Feedback：守卫被干扰，看向发声源发现没人的时候显示“？”；守卫发现玩家时显示“！”。
* 创建 Content/UI - WBP_GuardState
  * 添加 Text 控件
  * anchor 放到中心，重置 position，Alignment (0.5, 0.5)，Size to Content，Font Size 65，黄色，Shadow Color A 0.2。
  * Text 设为 “？”
* 在 BP_Guard 中
  * 添加组件 `Widget` 新建窗口控件组件
  * Widget - details - User Interface - `Widget Class` 设为 `WBP_GuardState`
  * 到 Viewport 中把问号往上提，调整位置
  * Widget - details - User Interface - `Space` 从 World 设为 Screen：令其从每个方向都能看到
* 根据状态调整 UI
  * 定义枚举类
    ```cpp
    // FPSAIGuard.h
    UENUM(BlueprintType)
    enum class EAIState : uint8
    {
        Idle,           // 默认状态
        Suspicious,     // 被干扰时，显示“？”
        Alerted         // 警惕状态，显示“！”
    }

    class ...
    {
    protected:
        EAIState GuardState;
        
        void SetGuardState(EAIState NewState);

        UFUNCTION(BlueprintImplementableEvent, Category = "AI")
        void OnStateChanged(EAIState NewState);
    }

    // FPSAIGuard.cpp
    AFPSAIGuard::AFPSAIGuard()
    {
        GuardState = EAIState::Idle;        // 设定默认值
    }

    void AFPSAIGuard::SetGuardState(EAIState NewState)
    {
        if (GuardState == NewState)
        {
            return;
        }
        GuardState = NewState;              // 更新状态

        OnStateChanged(GuardState);         // 调用 UMG 修改 3D UI 状态
    }
    ```
    * 枚举类型标记为 `UENUM(BlueprintType)` 使其在蓝图可用，`uint8` 为公开给蓝图的定义格式
    * 在 cpp 中更改状态后在蓝图中更改 UMG 文本，因此定义一个在蓝图中实现的函数接口，在此调用，并在蓝图中实现
    * 另外记得去 AI Guard 中 `OnNoiseHeard`、`OnPawnSeen` 两个事件中调用 `SetGuardState()`，注意 Alerted 优先级高于 Suspicious ，可以在 OnNoiseHeard 进入时即判定。最后在 `ResetOrientation()` 中同样判定及重置状态。
* 实现 UI 文本更改
  * 在 BP_Guard - Event Graph 中实现事件 `On State Changed`
  * 拖入 `Widget` 组件 -> `Get User Widget Object` 获得控件 -> Cast To WBP_GuardState
  * 把事件执行线连到 Cast。
  * 转到 WBP_GuardState 进入蓝图界面 Graph ，新建 Functions - UpdateText ，增加 Inputs - `Text NewText;`。回到 Designer 界面选中 Text - details - 勾选 `Is Variable`。再到 Graph 中，Text 显示到 Variables 栏下，拖入蓝图 `SetText`。
  * 再回到 BP_Guard，As WBP_GuardState -> `Update Text`，New State 输入从 On State Changed - New State -> Select 给出。
  * 在 WBP_GuardState - event graph - event construct -> `Get Text` -> `SetText` 使初始显示为空。
### 8. Challenge：AI 巡逻
* 逻辑
  * 两点间游走（可以范围内随机？）：**`寻路网格体 Nav Mesh Bounds Volume`**
    * 寻路系统相关
    * UE4 小技巧：右键物体，Select -> Select all matching classes 选中所有匹配类
    * details - `search navigation`（导航） - collision - `can ever affect` 取消寻路系统对相应物体的影响。（默认情况下物体会让寻路网格有洞，而模拟物理的物体被击中时会移动，运行时寻路网格静止，洞保留）
  * Suspicious 时停止巡逻
* p31 02:53

## 四、实现联网
* 总览
  * 让类在多人游戏设置下的客户端和服务器上运作
  * **Replication**
### 1. 场景调整
* 调整场景，增加难度。
* 为目标物创建简单材质
  * 新建 Content/Materials/M_Objective 闪光材质
  
  ![](images/1.png)
  * `Sine_Remapped` 两 Value 值可改变脉冲频率
* 尝试多人游（爆）戏（炸）
  * Play - Multiplayer Options - Number of Players 设为 2，同时打开两个客户端（实际上打开的是一个服务器和一个客户端）
  * UE4 小技巧：多端运行时 Shift + F1 挪开窗口
  * ↓ 在客户端做操作测试：
  * 问题 1：守卫头顶 UMG UI 只在触发客户端显示
  * 问题 2：客户端可出现拾起粒子特效，但目标物未显示销毁，只在服务器上显示销毁。但客户端的左上提示 UI 正常变化，服务器提示 UI 未改变。
  * 问题 3：任务完成时客户端视角切换，无 UI 提示。服务器未切换视角，有 UI 提示，仍可移动。
  * 问题 4：（p34 开头处）在客户端、服务端分别开枪，另一窗口都没有相应变化， Projectile 不通信。
### 2. 发射物 Projectile 通信
* `打开 Replication`：在要复制到客户端的 Actor 类的构造函数中将相关 Actor 的复制选项打开
	```cpp
	// FPSProjectile.cpp
	AFPSProjectile::AFPSProjectile()
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	```
	* `SetReplicates`：生成发射物 projectile 时在客户端复制同样的效果。
    	* 流程：
    	* ① 服务器窗口调用 `AFPSCharacter::Fire()` 
    	* ② `AFPSCharacter::Fire()` 中 `SpawnActor<AFPSProjectile>` 生成发射物
    	* 此时只对服务器有效，客户端中不显示
    	* ③ 启用 `SetReplicates` 后，服务器向所有客户端发送数据包，请求在客户端上生成该发射物
	* `SetReplicateMovement`：类似地，移动、位置、转动等信息改变时，服务器也向客户端发送数据包，将状态更新到客户端
* `确保代码在服务端上运行`
  * ue4 client-server mode ，只能从服务端给客户端发数据包。如果要反向的话需要调用服务端给出的事件触发接口传参实现：
  * 所以完成 SetReplicate 后，在客户端窗口生成发射物的数据不能被服务端知晓：`FPSCharacter::Fire()` 与玩家控制的 Character 绑定，客户端无法往服务端直接传数据包。
  * **`服务器函数`**
    ```cpp
    // FPSCharacter.h
    protected:
        UFUNCTION(Server, Reliable, WithValidation)
        void ServerFire();

    // FPSCharacter.cpp
    void AFPSCharacter::ServerFire_Validate()
    {
        return true;
    }

    void AFPSCharacter::ServerFire_Implementation()
    {
        // 需要运行在服务器上的部分代码
        if (ProjectileClass) { ... }
    }

    void AFPSCharacter::Fire()
    {
        ServerFire();
    }
    ```
    * `Reliable`：确保连接至服务器（可能遇到丢包等问题，但最终确保连接）
    * `WithValidation`：实现时要另外写一个 `_Validate` 结尾的 bool 函数，在服务器端进行完整性检查时用到。当客户端发起 return false 请求时服务器会强制取消连接，因为可能出现严重问题或在用外挂（
    * 注意实现时要加后缀 `_Implementation` ，调用时与头文件的 ServerFire() 保持一致。
    * 原因：`当创建带有 Server 关键词的 UFUNCTION 时，后台会自动为 _Implementation 和 _Validate 创建头文件`
    * 流程：在客户端 `Fire()` 中调用 `ServerFire()` 时，不在客户端执行，而是发送请求到服务器，让服务器执行 ServerFire_Implementation() 函数。在服务端 `Fire()` 中调用 `ServerFire()` 时（因为本游戏服务端自身也可以是游戏玩家），当然直接执行。
* 其它 Projectile 相关内容
  ```cpp
  // FPSProjectile.cpp
  void AFPSProjectile::OnHit(...)
  {
      // 施加推力等
      if (Role = ROLE_Authority)
      {
          MakeNoise(...);
          Destroy();
      }
  }
  ```
  * MakeNoise 用于影响 AI 逻辑，所以只需在服务器上运行。
  * Destroy 不应在客户端执行，因为客户端不拥有 Actor ，只是模拟生成了服务器的指令（replicate）。最终还是服务端决定何时销毁 Actor 。
* 客户端只能水平射击问题（p35 开头）
  * 在模板工程代码中使用了 `MuzzleLocation`、`MuzzleRotation`
  * 运行测试可以发现客户端抬枪的时候服务端并没有动。
  * 解决办法一：在服务器函数中给出发射物位置和旋转度信息，当然这样不能解决服务端观察客户端角色时没有抬枪的问题。
  * 解决办法二：**`uint8 APawn::RemoteViewPitch`** 
    ```cpp
    // FPSCharacter.h
    public:
        virtual void Tick(float DeltaTime) override;
    // FPSCharacter.cpp 
    void AFPSCharacter::Tick(float DeltaTime)
    {
        Super::Tick(DeltaTime);

        // check 是否被控制中
        if ( !IsLocallyControlled() )
        {
            // 设置玩家手臂的相对旋转度
            FRotator NewRot = Mesh1PComponent->RelativeRotation;
            NewRot.Pitch = RemoteViewPitch;
            Mesh1PComponent->SetRelativeRotation(NewRot);
        }
    }
    ```
    * 用到 FPSCharacter 的每台机器上的实例都按帧更新其位置。更新函数在服务器和客户端上都会运行，即运行两次。
    * `RemoteViewPitch` 是 replicated 的。
    * 注意：`不要和控制角色时给出的输入冲突`，因此只在不操作角色时执行。
* 组件拼接 Bug：手臂虚影
  * BP_Player 中 Mesh1PComponent 轴心在底部，但又附加到相机组件
  * 把上面更改的组件从 Mesh1PComponent 改为 CameraComponent
  * Bug：手臂狂晃
  * **`RemoteViewPitch的存储方式`**： Alt + G 转到定义，其类型为 `uint8` ，不能为负值，在整个文件中搜索 RemoteViewPitch ，发现设置该变量的地方，有注释“Compress pitch to 1 byte”，被压缩到了一个字节。因此该量不能直接设置为 Pitch ，而需要进行解压（做压缩处操作的逆操作）。偷懒笔记：$RemoteViewPitch \times 360.0f / 255.0f$，转为 [0, 360] 内的任一角度。
### 3. 
### 4. 
### 5. 
### 6. 
### 7. 
### 8. 
### 9. Activity：和基友一起愉快滴玩耍w

## 五、
## 六、
## 七、
## 八、
## 九、
## 十、
## 十一、
## 十二、
## 十三、