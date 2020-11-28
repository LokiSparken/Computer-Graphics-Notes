> # Enhancing Animation with Control Rig
> * https://www.youtube.com/watch?v=TYSdxW2WHcI

## 准备
* 启用插件 Plugins - Control Rig，新增两种资源类型：Animation - Control Rig Blueprint & Control Rig Sequence
* 需求：让动作适应对角色的个性化定制。
* UE4 4.23

## Control Rig Blueprint - Procedural Animation
### 例子
* 角色戴上手部装备（铁爪护手）后，普通投掷动作手指和装备黏连（有丶穿模的感觉？）。
* Control Rig can help by procedurally animating this claw based on the pose from actual character. 根据人物姿势程序化生成所戴装备的骨骼动画。
### 使用
* 创建 Control Rig Blueprint - Content/Fortnite/Gauntlet/Rig_Gauntlet
  * Parent Rig - 大部分情况下可以使用默认的 COntrolRig 类，需要自定义则在 C++ 中创建
* 打开 Rig_Gauntlet 编辑器
  * 界面与动画蓝图类似，但左下多一个骨骼绑定面板（显示 Rig Graph 中所有节点）、一个关节层级面板（右键 Import 选择骨骼网格体导入）
* 添加预览
  * Preview Scene Settings - Preview Mesh
* 逻辑：根据手指位置生成铁爪动画
* `实现：控制手指移动`
  * ① 获得关节层级的引用，得到所有关节在任何时刻的位置：`Rig Hierarchy Ref` - BaseHierarchy -> `Apply FK`.Hierarchy Ref
  * ② 获取关节：在 Hierarchy 中复制某关节名 `JointName` ，填入 `Apply FK.Joint = JointName`
  * ③ 提供移动该关节的 Transform：给出开始和结束状态。
    * 获取开始状态：BaseHierarchy -> `GetJointTransform(Joint = JointName, Type = Current)`
    * 获取初始局部位置：Type = Initial Local
    * 控制上面两个 Transform：`Control(Base = GetJointTransform.Current, InitTransform = ~.Initial Local)` 重命名为 FingerControl
    * 相对手指当前位置做变化：GetRelativeTransform(Control, GetJointTransform.Current) -> Apply FK.Transform
  * 小技巧：Apply FK - details - Execution Type = In Editing Time，运行时希望动画驱动手指的移动，而不是该结点。该结点只用于测试。
* `实现：使铁爪根据手指位置移动`
  * ① 类似地，使用 Apply FK，设 `Apply FK.Apply Transform Mode = Additive`，接上 `Apply FK.Hierarchy Ref` = 手指 FK 的输出 Ref
  * ② 对铁爪的 Transform.Rotation 做变换：Multiply( Inverse(GetJointTransform.InitialLocal), GetJointTransform.CurrentLocal ) 用 Initial Local 的倒数乘当前位置得到增量 -> GetAngleAroundAxis(x=0, y=0, z=0) 在预览中可观察使铁爪适应手指的移动只要在 Z 轴上下摆动即可 -> FromAxisAndAngle -> Apply FK.Rotation
  * 此时只有一点点穿模了，把变换铁爪的 Rotation 里的 Initial Local 改成操纵的手指下一层的关节，就能再分开一点。
* `应用`
  * 内容浏览器 - 根据铁爪护手的 Skeletal Mesh 右键 Create Anim Blueprint - SK_F_Outlander_Gauntlet_Skeleton_AnimBlueprint
  * Anim Graph - `CopyPosefromMesh` - 勾选 use attached parent 关联到附加的父类代码，此处为使用该装备的角色
  * CopyPosefromMesh -> `Control Rig(class = Rig_Gauntlet)` -> Result
* `在骨骼网格体中测试`
  * 骨骼网格体编辑器 - 指定后期处理动画蓝图 Post Process Anim Blueprint = SK_F_Outlander_Gauntlet_Skeleton_AnimBlueprint

## Control Rig Blueprint - Retargeting
### 例子
* 《堡垒之夜》角色共用同一套基本骨骼，而狼人角色膝盖与脚之间多一个关节，导致关节层级不同，所以基本骨骼动画不匹配，使用纯 IK （Inverse Kinematics 反向动力学：子骨骼节点带动父骨骼节点运动）的话效果也比较奇怪。
### 使用
* 用 Control Rig 对骨骼进行重定位，类似前一例子，调整相关部位骨骼变换的变化量，应用到导入的 incoming human leg 来生成动画，定义新的旋转规则。
* 应用到动画蓝图，加上 IK 修正脚部动画。

## Control Rig Swquence - Biped Rig
* 示例项目：控制所有关节
* 用途：制作关键帧动画
### 使用
* 创建 Control Rig Sequence
* 打开 Sequencer 编辑器（一个非线性的轨迹库系统，在时间轴上设置关键帧属性，用于制作过场动画）
* 在场景中放入一个角色网格体 SK
* Animation - Actor 应用放入的角色网格体
* Sequencer - Track - ControlRig 指定 Control Rig Blueprint - BipedControlRigBP
  * 可以控制的关节控件结点出现在角色网格体上
  * 为该蓝图添加 Track ，选择关节控件结点，设定初始状态
  * 选中需要的 Track，拨时间轴，给出对应时间需要的动作状态

## 文档
* docs.unrealengine.com/Engine/Animation/ControlRig