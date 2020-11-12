> # Create Multiplayer Games with C++
> * https://www.udemy.com/course/unrealengine-cpp/
> * Implement & Compare & Q & A

## 一、拾取物体
* 碰撞通道相关？
  * 
* 为什么 BP_HUD 里 Create Widget 不用指定 Owner？
  * 
* WBP_ObjectiveInfo Text Bind function()
  * 用 if(branch) 的话 execute pin 会僵住=。=
### Challenge
* 我的实现
  * 瞎搞（
* Tomlooman
  * 规范的命名
  * 合理的事件绑定与调用
```cpp
InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapInnerSphere);
// 绑定函数到 OnComponentBeginOverlap 事件，并在其中销毁

UPrimitiveComponent *PrimComp in OverlappingComps;
PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
```
* **`UPrimitiveComponent`**
  * Component has a `Transform`、`Potential to be Physically Simulated`
  * 只对支持物理作用力的对象有效
* AddRadialForce() 外推力 => 施加负 Force

## 二、游戏规则

## 三、AI 基础

## 四、实现联网

## 五、Coop Game 1 - 角色基本组件及动画

## 六、武器设定

## 七、武器设定 2

## 八、伤害反馈

## 九、联网

## 十、基础 AI

## 十一、功能道具

## 十二、游戏规则

## 十三、高级 AI


