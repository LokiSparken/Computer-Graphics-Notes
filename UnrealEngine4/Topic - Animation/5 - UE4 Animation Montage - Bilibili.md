> # UE4 Animation Montage
> * https://www.bilibili.com/video/BV1q7411d7xb

## 001 基本操作
### Animation Composite
* 顺序组合 Animation Sequence 
* 用于动画蓝图
### Animation Montage
* 紫色底
* 创建
  * New - Animation - Montage
  * 右键 Animation Sequence - Create - Create AnimMontage
* 设置
  * 主界面比 Composite 多一条 `Section`，用于切分顺序组合条
  * 可任意排序拼接、循环
* **`使用`**
  * 在动画蓝图中添加 `Slot` 进行关联
    * AnimBP - AnimGraph - StateMachine -> Category = Montage : Slot -> Result
    * 对应 Montage - AnimSlotManage 
  * 调用 Montage 相关节点播放蒙太奇
    * `Play Montage`(`In Skeletal Mesh Component`, Montage to Play, Starting Section)
    * 动画蓝图 or 人物蓝图皆可，4.16 后可在人物蓝图中使用，为异步节点

## 002
### 通知
* 在 Curve 选取所需时间点，创建 Notify，可在该处捕获事件
* AnimBP - EventGraph - `Add Anim Notify Event` - 取对应的 Notify
* 动画蓝图获取角色信息：`GetPawnOwner` -> Cast to BP_Character
* 逻辑节点：`Montage Jump to Section`

### 融合
* AnimBP - AnimGraph
  * `Layered blend per bone`：details - Layer Setup - Add elements 设骨骼节点名，控制以该骨骼为根的所有子骨骼节点。同组元素共享 Pose。
  * State Machine 只能输出一次：缓存动画 `New Save cached pose`，调用动画 `Use cached pose 'xxx'`

## 003
* 创建另一个 Montage
* 添加 Notify 时可添加 Skeleton 已有通知事件
* 逻辑节点
  * Montage Jump to Section End
  * 反正搜 montage 康康有什么可以用的
* Slot
  * Slot 在各 Montage 间共享可见，所以对不同的 Montage 要使用不同的 Slot 才能在动画蓝图中正确关联。
  * 即 `调用时通过 Slot 识别 Montage`
  * Slot 的 Group 类似 Category 做分类
* 角色蓝图中使用 Montage 要指定骨骼而动画蓝图不用：动画蓝图创建时就与某种骨骼绑定，而角色组件中可能有多个骨骼网格体
* `位移动作`
  * 相应 Animation Sequence 设 `Root Motion` = true
  * AnimBP - Anim Preview Editor - Edit Defaults - `Root Motion Mode`
* `重定向`
  * 选中动画资源 - Asset Actions - `Bulk Edit via Property Matrix`
  * 重定向界面，左侧所选资源，右侧共同属性，设 Skeleton
  * File - Save

## 004
* Pain Causing Volume 触发 BP_Character: Event AnyDamage
* 混合节点
  * `Blend Pose by Bool`
* 角色中获取动画蓝图的信息
  * Mesh -> `Get Anim Instance` -> `Cast to xxx_AnimBP`
* Play Anim Montage 指定默认骨骼

