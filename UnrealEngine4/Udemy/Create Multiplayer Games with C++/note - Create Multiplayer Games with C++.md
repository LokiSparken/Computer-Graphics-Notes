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
### 2. 绑定组件
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
        UE_LOG(LogTemp, Log, TEXT(""));
    }
    ```
* 使用重叠组件
  * 主界面左侧 Modes 中 search classes - FPSExtractionZone 拖入场景
  * `显示重叠组件`：`SetHiddenInGame`
### 2. 完善通关口
* 向项目的 Content 添加内容
  * 右键 Content - Show in Explorer
  * Ctrl + 把 Materials 拖入
* **`贴花`**
    ```cpp
    // FPSExtractionZone.h
    protected:
        UPROPERTY(VisibleAnywhre, Category = "Components")
        UDecalComponent *DecalComp;
    
    // .cpp
    #include ""
    AFPSExtractionZone::AFPSExtractionZone()
    {
        // 创建对象
        DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
        // 尺寸与通关口范围一致，API Alt + G 到
        DecalComp->DecalSize = FVector(200.0f);
    }
    ```
* p18 02:19