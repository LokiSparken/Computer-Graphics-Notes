> # 初始动画
> * https://www.unrealengine.com/zh-CN/onlinelearning-courses/your-first-hour-with-animation
> * Author：Mathew Wadstein
> * 注：在 OL Learning 1 的基础上略记一些不同的内容

## 准备
* 项目：ThirdPersonTemplate

## 动画 Assets
* Assets
  * 骨骼网格体与静态网格体区别：加了骨骼才能应用动画
  * 动画序列 Animation Sequence：单个动画动作
    * 在外部程序中创建动画，导入到 UE4 转化为 Animation Sequence。
    * 动画序列附加在骨骼上
  * 动画蓝图 Animation Blueprint：控制动画运行方式
  * 混合空间 Blend Space：控制不同动作间的平滑过渡
  * 瞄准偏移 Aim Offset：瞄准时只偏移上半身
  * 动画蒙太奇 Animation Montage：将不同动画连接起来、添加循环、调用，**`适合制作连招`**
  * 关卡序列 Level Sequence、模板序列 Template Sequence：将动画记录在引擎中，用 Sequencer 播放
* `使用方式`
  * BP_Character - Animation - Animation Mode = Blueprint/Asset/Custom Mode

## 动画编辑器
* Skeleton 界面
  * 骨骼关节层级中可添加`插槽 Socket` 、`虚拟骨骼 Virtual Bone`
* 切换到 Mesh 界面
  * 左侧骨骼层级旁显示 Asset Details
    * 如果有多个网格体，则需要在多个网格体之间切换
    * Asset Details 和静态网格体编辑器相同，但增加了 Physics、Lighting
  * 顶部工具栏
    * Preview Animation 预览动画
    * Create Asset 根据当前网格体和骨骼创建动画蓝图等 Assets
    * Reimport Base Mesh
    * Section Selection 分段选择
    * Activate Cloth Paint 布料绘制
    * Make Static Mesh 用该骨骼网格体制作静态网格体
    * Bake out Materials 烘焙材质
  * 右侧 Preview Scene Settings
    * Preview Controller = Default/Reference Pose/Use Specitic Animation
* Animation
* Animation Blueprint
  * 如果绑定了多个动画蓝图，可在选项卡处切换
* Physics
  * 要运用物理效果时才使用
  * 顶部工具栏 - Simulate

## 混合空间
* 混合空间编辑 Animation - Asset Details
  * Horizontal Axis
    * Number of Grid Divisions 网格分区数量：即对应坐标轴的网格数，调整动画播放的时间粒度
    * Interpolation Time 插值时间：动画过渡所需时间（值较大可能会导致动作过渡不平滑，有明显的动作结束和停顿）
  * Blend Samples：在坐标轴上的关键帧
    * Snap to Grid 对齐到网格线
  * Sample Interpolation 采样插值：`2D Blend Space 中很有用`【？】然鹅有听没有懂，需要康康实例
* 注意：调整播放速率后 “Can't Play In Editor when performing Edit Rate Scale operation” 的话保存一下即可。

## 动画编辑器
* 内容浏览器中底部绿色的为单个动画动作
* 顶部工具栏
  * Preview Mesh 当骨骼设置有不同的网格体，可以在这里调整预览
  * Reimport Animation 如果导入过，会直接定位到导入的动画位置
  * Make Static Mesh 把特定动作做成静态网格体
* 中央底部：动画时间轴 Animation Time Line
* 右下只显示兼容当前骨骼的动画
* Asset Details
  * 使用 Root 骨骼时要打开选项 EnableRootMotion
  * Import 系列，调整导入的动画，只对 Import 生效。所以如果已经导好了，在这调整完要重新导入。
* 中央底部 Animation Time Line
  * Notifies：**`用于与蓝图交互`**，可通知蓝图当前的动画状态
  * Curves：放大或缩小对象【？】
  * Additive Layer Tracks 图层轨道：不借助第三方程序，对动画做调整，不更改基础动画本身
  * 小技巧：Ctrl+鼠标滚轮 缩放时间轴。底部设置时间和帧率。

## 动画蓝图编辑器
* 顶部工具栏：类似动画编辑器
  * Find/Hide Unrelated 寻找/隐藏结点
  * Class Settings/Class Defaults
  * Debug Filter
* 右下 Preview 属性设置
  * Root Motion Mode
  * `Notifies`
* 右下 Asset Browser 显示可用的动画序列和混合空间

## 用关键帧编辑动画
* 与 OL Learning 1 类似
* 小技巧 `造相同状态`：添加好的关键帧右端下拉列表 `Edit Curve` 显示其 Translation、Rotation、Scale，选中，用 Curve Editor 工具条的 `focus` 聚焦到具体帧，选中并复制，`Add Key` 黏贴

## 创建自定义角色
* 角色基本设置

## 使用动画蓝图
* 与 OL Learning 1 类似，GetPawnOwner 加个 Cast to Character
* 可以直接在动画蓝图的 AnimGraph 用 `Blend` 结点混合单个动画序列
  * Alpha Input Type = Float/Bool/Anim Curve

## 完成动画蓝图（状态机、混合空间）
### 状态机
* 与 OL Learning 1 类似
* 可对不同部位应用不同的状态机，如上下半身
  * 然鹅还是把动画蓝图里的 Blend 剪切进状态机惹（
  * 这就是封装吗（
* 除了初始拉线出来的 Transition Rule 还可以在状态间瞎几把拉更多的 Rule（
* `Debug Filter`
  * No debug object selected
  * Preview Instance 预览实例（把预览视口中的状态数据显示在状态机的状态上）
  * MyCharacterAnimBP_C_21 in MyCharacter 显示 Play 时使用了该动画蓝图的角色状态数据和流向
* Transition Rule
  * `Time Remaining (ratio)` 获取当前动画序列还有多久播放完 <= float = 0.1 -> Can Enter Transition
  * 即“小于 10% 时间结束当前动画序列时，可以开始过渡到另一状态”
  * `Get Relevant Anim Time Remaining Fraction` 获取上一动画状态中邻接过渡的动画序列剩余时间
  * 【？】两个差不多？
* Details
  * Blend Settings 设置过渡
  * Automatic Rule Based 自动决定基于上一动画的状态过渡规则
### 混合空间
* 与 OL Learning 1 类似

## 总结
* BP_Character - Details
  * 小技巧：搜索右侧 view options - `Show Only Modified Properties`
* More
  * `动画通知系统：让动画在播放期间触发事件（如挥剑时对敌造成伤害）`
  * 蒙太奇系统：将多个动画序列拼接到一个 Asset
  * 动画蓝图高级设置：用结点将骨骼或图层进行混合（单独调整上下半身）
  * 详见动画系统 doc

