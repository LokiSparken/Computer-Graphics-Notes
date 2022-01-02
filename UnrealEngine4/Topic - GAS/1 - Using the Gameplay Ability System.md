> # [Using the Gameplay Ability System](https://www.bilibili.com/video/BV1gJ411J7AM)

## Gameplay Ability System（GAS）
* plugin - Gameplay Abilities
* 需要在 actor 上应用组件 Gameplay Ability System Component [C++ only]
* cons
  * 快速开发原型
  * 提供了较优的网络同步方案
* 基本概念
  * Gameplay Effects：`represent how to change sth` after setting and triggering it.
  * Gameplay Tags：`Conditions`
  * Gameplay Attributes：`represent some values`, e.g. health、damage、states……
  * Gameplay Cues：visuals, audio

## Gameplay Tags
* `source tags`：技能释放者，满足所有 require && 不含 ignore tags 的对象
  * same as target（受击者）
  * 在对应 class 中筛选可释放和承受的实例
* Granted Tags：当前 effect 施加到受击者上时，其身上出现的 tag
* On going Tag Requirements：必须具备/`不具备`某个 ignore tag，不满足时禁用 effect（如含 ignore tag: disable skills，就禁技能？）
* Application Tag Requirements：应用技能到某 actor 时，check 的 tag，不满足条件则施加失败
* Remove Gameplay Effects with Tags：某 tag 出现时，所有关联的 effects 被清除（净化 debuff？）

## GAS 与非 GAS 的通信
* GAS -> 非 GAS，通常是 initiated from/driven by GAS

## GAS 与普通工作流方案的对比
* 吐槽 at 24:08：少用 animation events，动画最后一帧的 events 很难正常工作，要用就别放最后一帧
* GAS：确认本地可释放后，发出信号让服务器提前模拟预测能否释放（当前服务器状态能否同步），服务器返回 Prediction Key 告知是否接受请求
* 小结
  * **`Task`：`encapsulate Asnychronous Behavior`**
  * Abilities：Brain

# More
1. [UE4 Wiki - Gameplay Abilities and you](https://unrealcommunity.wiki/gameplayabilities-and-you-0jz20ztl)：基本使用方法
2. [Video Tutorial - Intro to gameplay abilities](https://www.youtube.com/watch?v=Ev2P6BTUxN0)
3. [Github user: tranek - GASDocumentation](https://github.com/tranek/GASDocumentation)（翻译：[GASDocumentation_Chinese](https://github.com/BillEliot/GASDocumentation_Chinese)）：概念介绍、使用方式、运行机制
4. [Github UE GAS Demo - GameplayAbilitiesSample](https://github.com/daveratti/GameplayAbilitiesSample)


