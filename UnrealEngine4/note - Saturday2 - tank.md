> # <i class="fa fa-book-open"></i> 后天星期六 - 坦克大战（C++）
# <i class="fa fa-star"></i> 任务一：简介

# <i class="fa fa-star"></i> 任务二：导入坦克模型
* 资源管理 `/Content/Assets`、`/Content/Maps`、`/Content/Blueprints`
* 导入 `tank.fbx_Body主体/Track履带/Barrel炮管/Turret炮塔.fbx`
  * 导入选项勾选 `Mesh - Conbine Meshes` 自动组装
  * 去除 import materials/textures

## 模型拼接
### 1. 蓝图中手动调整
### 2. 挂点
* Body 网格编辑器 - Details - Socket Manager - Create Socket 增加挂点插槽
* Preview Static Mesh 选择用于预览的网格模型
* Relative Location/Rotation/Scale 调整关联位置
* 创建Actor蓝图类BP_Tank做拼接
  * 插槽使用 `Add Component - Static Mesh - Details - Sockets - Parent Socket`

# <i class="fa fa-star"></i> 任务三：坦克视角控制
## 以Tank为视点
* 基于默认的GameModeBase创建BP_TankGameMode
  * 修改 Default Pawn Class
    * 需要绑定到Pawn或Pawn的子类
    * 开始时会在初始视点Player Start生成一个相应物体
* BP_Tank - Class Settings - Details - Class Options - Parent Class 
  * 修改父类为 Pawn
  * 绑定到BP_TankGameMode
* 应用GameMode
  * project settings - GameMode

## 视角调整
* 给TankBody添加组件Spring Arm及子组件Camera
  * Spring Arm - Details - Target Arm Length 修改摇臂长度
### **`根据鼠标的移动调整视角`**
* **`从外设获取输入`**
  * project settings - engine - input
    * `Action Mappings` 按键映射
    * **`Axis Mappings` 轴映射**
  * 添加轴绑定 LookH/V - Mouse X/Y 分别关联到鼠标水平/垂直方向的移动
  * 此时可在蓝图中获取到结点 `InputAxis LookH/V`
* **`移动逻辑`**
  * 项目管理：不在默认的 EventGraph 中处理输入，新建自定义的 InputGraph 用于处理输入
  * `基于摄像机摇臂当前的 rotation 做偏移`：`AddRelativeRotation`
    * 三维 rotation 展开，在 viewport 中观察并确定需要偏移的轴是哪一维
    * 把 InputAxis LookH 连到相应的水平维度
  * 垂直方向可同理新增一个 AddRelativeRotation 结点，但两个方向独立在旋转角度过大时会翻车（【？】其实我这瞎子没看出来翻了什么车……）
* **`Scene组件：只有位置信息`**
  * 给 TankBody 添加只有位置信息的 Scene 组件
  * 把 SpringArm 移入 Scene
  * 将两个处理维度偏移的结点其中一个 target 设为 Scene
* `对垂直方向的移动略做限制`
  * 使用 `SetRelativeRotation` ，把 SpringArm 原来的 rotatorX、rotatorZ `GetRelativeRotation` 取出来连进去不变
  * 用 `Clamp` 对偏移结果 rotatorY+MouseY 做 Min、Max 限制
    * 仍可在 viewport 中观察合适的视角范围
    * 此可用 [-40, 5]

# <i class="fa fa-star"></i> 任务四：创建 Controller


# <i class="fa fa-star"></i> 任务五：LineTrace 寻找瞄准点

# <i class="fa fa-star"></i> 任务六：创建火控系统 AimingComponent

# <i class="fa fa-star"></i> 任务七：炮塔和炮管转向

# <i class="fa fa-star"></i> 任务八：发射炮弹

# <i class="fa fa-star"></i> 任务九：完善射击状态


# <i class="fa fa-star"></i> 任务十：开始坦克移动并修复一个炮台 Bug

# <i class="fa fa-star"></i> 任务十一：OnHit 事件绑定及WASD控制移动

# <i class="fa fa-star"></i> 任务十二：优化坦克移动

# <i class="fa fa-star"></i> 任务十三：AIController

# <i class="fa fa-star"></i> 任务十四：重写 Projectile

# <i class="fa fa-star"></i> 任务十五：炮弹粒子效果

# <i class="fa fa-star"></i> 任务十六：炮弹伤害与冲击波

# <i class="fa fa-star"></i> 任务十七：创建血条和死亡代理

# <i class="fa fa-star"></i> 任务十八：玩家重生

# <i class="fa fa-star"></i> 任务十九：可拾取物品


<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->