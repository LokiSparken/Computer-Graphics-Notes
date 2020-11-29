> # 动画入门
> * https://www.unrealengine.com/zh-CN/onlinelearning-courses/animation-kickstart
> * Author：Sjoerd De Jong，Mario Palmero Pavon
> * 注 1：This is a useless markdown.
> * 注 2：听听最强光头又说了点啥，然鹅他就说了四句话？
> 好框架啊可是也没有很多底层细节记不动了卒

## 简介
* 动画系统相关模块设计和运行机制

## 图解
* 导入 FBX（含有动画、骨架、网格体，在不同文件中）
### Skeleton
* Skeleton
  * Virtual Bone：创建自己的骨骼层级
  * Socket：与 Gameplay 交互
* Skeleton Mesh
  * 存储了 Clothing
* Retarget Manager：将动画/动画蓝图重定向到另一骨架，目标骨架需要与源骨架有类似结构
### Animation
* Animation Sequence 动画序列
  * Anim Curves
  * Anim Notifies
  * Sync Markers：一种特殊的 Anim Notifies（10:06 有听没有懂系列 :)
* 蒙太奇
  * 听起来和混合空间一样也是一种组合动画序列的方式
* `PoseAsset`
  * 暂停动画，选取动画帧，创建为 Pose ，可以将不同的 Pose Assets 混合到一起创建新的动画
  * 下一句打脸：但也可以直接通过 Gameplay 变量来控制动画时间
### Flow Control 19:04
* Slot
* Pose Caching
* Blend and Additive
### Procedural Animations 22:30
* Physic Assets
* Rigid、IK
### Animation Layers 25:52
* 开发中
### Control Rig
* 详见 GDC 2019 - Enhancing Animation with Control Rig
### Final Pose 27:20
* ？突然说起优化？如一堆角色共享四个动作姿势时，CPU 只对四个姿势做处理
* Sequence Recorder
  * 检查动画的过渡
  * 记录物理模拟的结果
### Performance 30:39
* 真。优化
* Animation Budget Allocator：动画部分计算超限的时候阉割部分效果或功能
* LOD：减少多边形数、骨骼数，如抓取行为当角色在远处会由于手部骨骼被砍所以无效
* Fast Path：动画蓝图 Event Graph 结点的闪电标记：原生 C++ 方式编译，会比较快
* Multi Threaded Update：需要激活

## 建议
* 重定向：把一些动作行为单独封装出来，可以通过重定向应用到不同但骨骼类似的角色
* 状态机
  * 进行分层
  * 每层尽量简单
* Pose Caching 不会占用很大开销
* BP_Character - Mesh - details - `Display Debug Update Rate Optimizations` 通过颜色显示角色更新速率（动画 Tick）
* Physics
  * 多个物理配置文件，可运行时更改

