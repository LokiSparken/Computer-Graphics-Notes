> # 《UE4纯C++与Slate开发沙盒游戏》
> * 教程平台：腾讯课堂
> * 录播讲师：梁迪

# 第一节 Slate开发游戏菜单（上）
<details>
<summary>详细内容</summary>

## **1. 项目介绍与资源获取**
<details>
<summary>配置</summary>

* UE4.18
* VS2015/2017
* VS：VAssixtX插件
</details>

<details>
<summary>UE4制作UI方法</summary>

* 蓝图控件UMG
* UMG配合C++（复杂逻辑用C++实现）
* 命令行
* `Slate`
  * 跨平台UI框架
  * 可做应用程序的UI，也可做游戏中各种UI
</details>

## **2. 添加Slate到界面**
### **① ASlAiMenuGameMode : AGameModeBase**
<details>
<summary>SlAiMenuGameMode.h</summary>

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlAiMenuGameMode.generated.h"

UCLASS()
class SLAICOURSE_API ASlAiMenuGameMode : public AGameModeBase
{
	GENERATED_BODY() // .h声明+cpp实现
}
```
* 宏GENERATED_UCLASS_BODY()：旧版本，弃用。
* 宏`GENERATED_BODY()`
  * 使用注意：.h声明+.cpp定义。所标记的类中，默认成员属性private，需要手动public。
  * 作用说明：UE4在C++编译开始前使用工具UnrealHeaderTool对C++代码进行预处理，收集出类型和成员等信息，自动生成相关序列化代码。再调用真正的C++编译器，把预处理代码和原始代码一起编译，生成可执行文件。`该宏代表了预处理代码的注入位置。`
</details>

<details>
<summary>SlAiMenuGameMode.cpp</summary>

* 除了GameMode还要HUD给玩家显示，PlayerController让玩家能够进行操作。
```cpp
// SlAiMenuGameMode.cpp
#include "SlAiMenuGameMode.h"
#include "SlAiMenuHUD.h"
#include "SlAiMenuController.h"

ASlAiMenuGameMode::ASlAiMenuGameMode()
{
    // 提供操作途径
    PlayerControllerClass = ASlAiMenuController::StaticClass();
    // 显示信息给玩家
    HUDClass = ASlAiMenuHUD::StaticClass(); 
}
```
* `PlayerControllerClass = *Controller::StaticClass();`
  * `UObject::StaticClass()`是UE4反射机制的一部分。
  * 若类被UCLASS()、GENERATED_BODY()等标记，表示该类会在UnrealHeaderTool预处理时被收集类型等信息。调用"StaticClass()"会在使用"实例->GetClass()"方法（可能是UHT收集类型信息的途径）时，返回UObject实例类型。（理解自：https://forums.unrealengine.com/development-discussion/c-gameplay-programming/48349-uclass-staticclass-definition）
</details>

### **② ASlAiMenuController : APlayerController**
<details>
<summary>SlAiMenuController.cpp 向玩家显示鼠标</summary>

```cpp
// SlAiMenuController.cpp
#include "SlAiMenuController.h"

SlAiMenuController::SlAiMenuController()
{
    bShowMouseCursor = true;
}
```
</details>

<details>
<summary>启动，对玩家输入的响应设置</summary>

```cpp
// SlAiMenuController.h
UCLASS()
class SlAiMenuController_API SlAiMenuController : public APlayerController
{
    GENERATED_BODY()
public:
    ...
protected:
    virtual void BeginPlay() override;
}
```
* `APlayerController`继承关系
  * *Controller -> APlayerController -> AController -> AActor -> UObject
  * `AActor::BeginPlay` 关卡开始时调用。
```cpp
// SlAiMenuController.cpp
void ASlAiMenuController::BeginPlay()
{
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode); // 绑定到当前的 Controller
}
```
* `FInputMode`继承关系
  * FInputModeBase -> FInputMode(1. UIOnly 2. GameOnly 3. GameAndUI)
  * 设对用户输入的响应方式，第三种为UI不处理用户输入时转到player input或player controller尝试响应。
  * 文档：https://docs.unrealengine.com/en-US/API/Runtime/Engine/GameFramework/FInputModeDataBase/index.html
* `FInputModeUIOnly`方法
  * `SetLockMouseToViewportBehavior(EMouseLockMode)`  
    设置视口的鼠标锁定行为。
  * `EMouseLockMode` 四种类型  
        
    类型  | 说明
    ----  | ----
    DoNotLock | 不锁定
    LockOnCapture | 仅当鼠标is captured时锁定
    LockAlways | 总是锁定
    LockinFullscreen | 全屏时锁定
</details>

### **③ SlAiMenuHUD : ASlAiMenuHUD**
<details>
<summary>Slate使用</summary>

* 创建Widget
    ```cpp
    // SlAiMenuHUD.h
    UCLASS()
    class SLAICOURSE_API ASlAiMenuHUD : public AHUD
    {
        GENERATED_BODY()
        
    public:

        ASlAiMenuHUD();
        
        TSharedPtr<class SSlAiMenuHUDWidget> MenuHUDWidget;	// 声明一个共享指针（拥有引用对象）
    };
    ```

    ```cpp
    // SlAiMenuHUD.cpp
    ASlAiMenuHUD::ASlAiMenuHUD()
    {
        // 检查引擎运行，视口打开
        if (GEngine && GEngine->GameViewport)
        {
            // 创建一个SlAiMenuHUDWidget实例并赋给.h中声明的MenuHUDWidget
            SAssignNew(MenuHUDWidget, SSlAiMenuHUDWidget);
            // Slate向视口添加控件，SNew为另一种创建
            GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef()));
        }
    }
    ```
    
    ```cpp
    SlAiMenuHUDWidget.cpp
    #include "SSlAiMenuHUDWidget.h"
    #include "SlateOptMacros.h"
    #include "SButton.h"

    BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
    void SSlAiMenuHUDWidget::Construct(const FArguments& InArgs)
    {
        
        ChildSlot
        [
            // Populate the widget
            SNew(SButton)
        ];
        
    }
    END_SLATE_FUNCTION_BUILD_OPTIMIZATION
    ```
  * 由于GEngine与GEngine->GameViewport可能为0，使用前都要先判断
  * 控件创建方法  
    `TSharedPtr SNew(WidgetType)[.PossiblyNullContent(TSharedRef)]`  
    `SAssignNew(TSharedPtr, WidgetType)`  
    【？：参数有点晕，以后用到的时候再试试吧】
  * `GEngine->GameViewport->AddViewportWidgetContent` 向视口添加控件方法
  * `PossiblyNullContent(*.ToSharedRef())`，由于MenuHUDWidget为共享指针，根据指针文档“要确认引用的对象为非空时，请使用共享引用”，所以调用TSharedPtr中返回对象共享引用的方法。
  * 注意：控件默认全屏，所以要设置样式
* 相关文档
  * Slate使用文档：https://docs.unrealengine.com/zh-CN/Programming/Slate/InGameUI/index.html
  * 指针说明：https://docs.unrealengine.com/zh-CN/Programming/UnrealArchitecture/SmartPointerLibrary/index.html
</details>




## **3. 使用WidgetStyle设置样式**
<details>
<summary></summary>

### **① SlAiStyle 纯C++类**
* `SlAiStyle.cpp`：获取样式，并注册进游戏。

```cpp
// in SlAiStyle.h
class SLAICOURSE_API SlAiStyle
{
public:
	static void Initialze();
	static FName GetStyleSetName();	// 获取样式注册到游戏中的名字
	static void ShutDown();	// 当游戏关闭时取消注册
	static const ISlateStyle &Get(); // 给外部调用获取本单例

private:
	static TSharedPtr<class FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> SlAiStyleInstance;	// 创建单例变量
};
```
* 其中：`class FSlateStyleSet` 用来注册样式

```cpp
// in SlAiStyle.cpp
TSharedPtr<FSlateStyleSet> SlAiStyle::SlAiStyleInstance = NULL;	// 注意初始化

void SlAiStyle::Initialze()
{
	if (!SlAiStyleInstance.IsValid())	// 指针为初始状态时进入
	{
		SlAiStyleInstance = Create();	// 创建
		// 把本样式单例添加到Slate风格管理类
		FSlateStyleRegistry::RegisterSlateStyle(*SlAiStyleInstance); 
	}
}
```
* `void Initialze()`
  * `TSharedPtr.IsValid()` TSharedPtr共享指针类型判断是否为空指针的方法。
  * `FSlateStyleRepository` 追踪和管理Slate风格数据的总集合

```cpp
FName SlAiStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SlAiStyle"));
	return StyleSetName;
}
```
* `FName GetStyleSetName()`
  * 字符串文档：https://docs.unrealengine.com/zh-CN/Programming/UnrealArchitecture/StringHandling/index.html
  * `FText` 本地化类型。UI上的所有文字应为该类型。


```cpp
TSharedRef<class FSlateStyleSet> SlAiStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(SlAiStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");
	return StyleRef;
}

const ISlateStyle & SlAiStyle::Get()
{
	return *SlAiStyleInstance;
}

void SlAiStyle::ShutDown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle("SlAiStyleInstance");
	ensure(SlAiStyleInstance->IsUnique());
	SlAiStyleInstance->Reset();
}

```
* `TSharedRef Create()`
  * 

</details>

## **4. DPI屏幕适配**

## **5. 菜单布局实现**

## **6. 语言切换功能实现**

## **7. 自定义Button控件**

## **8. Debug与游戏设置控件**

## **9. 完成游戏设置控件**

## **10. 模板单例与文件读取**

</details>

# 第二节 Slate开发游戏菜单（下）

<details>
<summary></summary>

## **11. 读取存档Json文件**

## **12. 写入存档Json文件**

## **13. 进入游戏控件**

## **14. 菜单控件初始化**

## **15. UI动画实现**

## **16. UI音乐播放与调节**

## **17. 场景跳转与GameInstance**

</details>

# 第三节 玩家角色与动作

<details>
<summary></summary>

## **18. 添加玩家模型与相机**

## **19. 动作蓝图与玩家移动**

## **20. 完成玩家移动**

## **21. 视角切换与Montage播放**

## **22. 完成玩家动作蓝图**

## **23. 制作快捷栏UI**

## **24. 物品属性Json读取**

## **25. 注册快捷栏到PlayerState**

## **26. 快捷栏切换与右手插槽**

</details>

# 第四节 场景资源交互

<details>
<summary></summary>

## **27. 物品类与碰撞事件绑定**

## **28. 手持物品与动作切换**

## **29. 动作通知与读取资源Json**

## **30. 资源与可拾取物品**

## **31. 准星与C++操控材质**

## **32. 射线检测伐木挖矿捡东西**

## **33. 生成掉落物与动态创建材质**

## **34. 动态球形检测**

</details>

# 第五节 游戏背包系统

<details>
<summary></summary>

## **35. 玩家状态UI**

## **36. 游戏暂停与输入模式切换**

## **37. 游戏UI切换**

## **38. 绘制背包UI**

## **39. 鼠标选中背包容器**

## **40. 小扩展_蓝图背包拖拽**

## **41. OnPaint实现背包拖拽**

## **42. 丢弃物品与绑定快捷栏**

## **43. 合成台功能实现**

## **44. 添加物品到背包**

</details>


# 第六节 敌人与行为树AI

<details>
<summary></summary>

## **45. 敌人模型与动作**

## **46. 敌人血条与视野组件**

## **47. C++搭建行为树框架**

## **48. 运行行为树与实现巡逻AI**

## **49. 敌人追逐AI**

## **50. C++动画RootMotion**

## **51. 敌人攻击AI（上）**

## **52. 敌人攻击AI（下）**

## **53. 敌人受伤AI**

## **54. 逃跑与防御AI**

</details>


# 第七节 小地图与游戏存档

<details>
<summary></summary>

## **55. 敌人死亡AI**

## **56. 渲染小地图**

## **57. 小地图玩家点与方位**

## **58. 小地图敌人视野**

## **59. 聊天信息显示**

## **60. 聊天室与敌人血条修正**

## **61. 游戏暂停菜单**

## **62. SoundMix音量与玩家死亡**

## **63. SaveGame读取存档**

## **64. 保存存档与项目完结**

</details>


# 折叠语法：
<details>
<summary></summary>


</details>

# 环境问题
* vs，.h声明自动生成.cpp定义：右键+e+i（VAX插件功能）
* VS，dll符号库缓存位置：C:\Users\sparken\AppData\Local\Temp\SymbolCache
* 当前Carbon位置：一 2结束