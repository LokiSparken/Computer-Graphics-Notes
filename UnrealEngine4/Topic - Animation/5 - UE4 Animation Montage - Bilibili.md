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
* 逻辑节点
  * Montage Jump to Section

### 融合
* AnimBP - AnimGraph
  * `Layered blend per bone`：details - Layer Setup - Add elements 设骨骼节点名，控制以该骨骼为根的所有子骨骼节点。同组元素共享 Pose。
  * State Machine 只能输出一次：缓存动画 `New Save cached pose`，调用动画 `Use cached pose 'xxx'`

## 003


## 004


