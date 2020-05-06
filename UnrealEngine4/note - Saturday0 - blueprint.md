> # <i class="fa fa-book-open"></i> 后天星期六 - 三维弹球（蓝图）
# <i class="fa fa-star"></i> 任务一：简介

# <i class="fa fa-star"></i> 任务二：建立场景和小球材质
## 场景
* 用`模式`中的`Geometry几何体画刷`把主要的底拉出来。
  * Brush settings
    * 笔刷类型addictive叠加、subtractive抵消，可用来挖空
    * 形状可直接改几何体类型
    * XYZ：该几何体大小
* 比较暗的话加个天空光源提亮
* 项目管理：保存到Content/Maps/作为一个关卡

## 小球
* 项目管理：在Content/创建Content/Assets/放模型和材质等资源
* 导入*.FBX，不生成碰撞，不生成材质
* 双击导入的球体模型可以进入`静态网格体编辑器`
  * 快捷键
    * 聚焦：F
    * 缩放：鼠标滚轮/ALT+鼠标右键
    * 绕物体进行轨道运动：ALT+鼠标左键
    * 视角飞行：与主界面编辑器相同，鼠标右键+WASD
  * LOD：Levels of detail多层次细节，每个LOD可拥有不同的材质。
  * 工具栏：碰撞、UV等
  * 将对象附加到一个静态网格体actor：插槽
* 创建材质并进入`材质编辑器`
  * v+鼠标左键，生成一个三维向量节点作为RGB颜色，取色后用最上面的输出通道连到`基础颜色BaseColor`
  * 1+鼠标左键，生成一个常量节点作为金属性，设置数值后输出通道连到`Metallic`
  * 同金属性，生成常量节点作为粗糙度，连到`粗糙度Roughness`
  * 然后apply一下，save一下
* 把材质应用到小球
  * 静态网格体编辑器中，材质插槽，选刚刚编辑好的材质
* 把小球放置到地上：`End`

# <i class="fa fa-star"></i> 任务三：蓝图和小球移动
## 蓝图
### 项目管理：Content/BluePrints/
### **创建蓝图类-Actor 定义小球**
* 蓝图类-Actor BP_PinBall
* 在左侧`组件Components`中添加组件`Static Mesh`（因为之前导入的小球模型是该类型）
* 添加后在右侧`细节Detail`中，`static mesh`选择之前设定好的小球模型
* 可以在`组件`中把小球拉成新的根节点
* `编译`后可以将蓝图拖到主界面了（此时还没有设置其它属性，所以拖出来和模型拖出来是一亚一亚的）
### **设定小球属性**
* 在BL_PinBall中的 `detail` -> `physics`
  * 勾选 `模拟物理simulate physics` 启用物理引擎（再compile，把球放到空中play，球就会下落）
* 让小球沿着地板滑动（两种做法）
  * 做法一：做个倾斜的地板，但游戏坐标系就歪了，不利于扩展
  * 做法二：让小球自行滚动
* `事件图表 Event Graph`
  * 事件开始运行 Event BeginPlay：开始运行时执行一次。
  * 事件Tick Event Tick：每一帧都执行。
  * 从结点拉出线会产生结点：选取方法接口（如 `Print String`）
  * 假设俯视地板，小球顺某方向移动，拉一下看看哪个坐标动，这里是 X 坐标。
* 给小球每一帧加一个力
  * `Event Tick` 拉出结点，用方法 `添加冲量 Add Impulse`
  * 拉出的结点自动连了一个 `目标 Target` ，即目前为根结点的 `Static Mesh`，更名后该 Target 也会自动改名
  * 为了后续便于调整施加的力，在左下栏添加`变量`，此命名为 Speed ，右侧细节处改变量类型，编译后可在右侧更改值
  * 因为只想在 X 坐标上滑动，因此把 `Add Impulse` 的三维 impulse 右键分割成三个量
  * 把 Speed 直接应用到 X 上的话是以 `Event Tick` 事件的运行频率，及每帧的间隔时间为单位的，而我们想要设置的 Speed 可能是以秒为单位，因此要从 `Event Tick` 的 `Delta Seconds` 拉出一根 `float*float` 的结点与 Speed 相乘，把结果输出到 X 上
  * 又为了在施加力的时候忽视物体重量（在游戏中可以统一考虑净力，而不用考虑各个物体的重量），勾选 `Vel Change` 【？解释存疑】
* 小球在底部反弹后飞出面板的问题
  * 解决方法一：`BP_PinBall` 设置 `Ball（static mesh）` 中的 `physics -> 约束 Constraints` ，把 Z 坐标限定住。（但这样限制太死，不灵活）

# <i class="fa fa-star"></i> 任务四：Bumper的制作
* 小球在底部反弹后飞出面板的问题解决方法二
  * 给小球施加向面板的力，摁到面板上。
  * `获取面板的法向量`：从添加冲量结点的主通道串行拉出下一个结点 `LineTraceByChannel` ，起点设为小球（从 `start` 拉出结点 `getActorLocation`，由于该蓝图就是一个actor，所以get的就是这个小球的位置），终点设在小球正下方某个位置，即用小球位置减去一个 z 量，从小球位置结点拉出一个结点减去一个三维向量，并连向终点 `end`。（在 static mesh 的 collision 中可以设置物体是否能被射线命中。）
  * `LineTraceByChannel` 的输出 `out hit` 拉出结点 `break hit result` 可以给出这条射线的命中情况，在这里就会命中面板，`impact normal` 即射线发出点到命中点的单位法向。
  * 因此施加向面板的力即这个单位法向的反向。从 `impact normal` 拉出结点乘 $-1$ ，再乘上一个力值变量，此处命名为 Stickness 。最后再乘上 `event tick` 的 `delta seconds`，就可以施加到 `add impulse` 上了。
  * 并且作为变量的 Speed 和 Stickness 在蓝图左下打开可视，编译后就能在主界面的小球细节中更改。
## Bumper
* 导入 `PopBumperBase` 和 `PopBumperMechanism` 模型。
* `PopBumperBase`静态网格编辑器
  * 模型比较复杂，没有简单碰撞体，只能生成复杂碰撞体
  * `LOD0 -> sections` 可取消下层碰撞体
  * 再为碰撞生成一个胶囊型碰撞体
* 小球撞击Bumper：如何触发
  * 在 `Event Graph` 中，原始的最后一个结点 `Event ActorBeginOverlap` 就是撞击到其它东西时被触发的，所以要使用该结点。
  * 为了能够触发小球蓝图中的那个结点，要`在 Bumper 蓝图中再添加一个 collision` 。（之前在网格编辑器中加的capsule是阻止小球通过的，蓝图中添加的组件才是实际产生触发功能的。）
  * 蓝图中的这个 `capsule collision` 细节设置中 `collision presets` 中勾选的 overlap 表示可以被触发 overlap 事件。
  * 在 `BP_Bumper` 中右键添加 `add custom event` 事件结点 Bump。（也叫function）
  * 在 `BP_Bumper` 中的 `overlap` 事件，因为要知道撞击上来的是小球，所以从 `other actor` 拉出结点 `cast to BP_PinBall` ，从执行成功的输出通道拉出结点执行自己加的 custom event 事件结点 `Bump`。（call function）
  * 因为即使 `cast to BP` 了，还是可以有多个从 `BP_PinBall` 生成的小球，所以为了唯一确定撞击到的物体，要给事件结点 `Bump` 增加 inputs。
  * 增加的 input 命名为 Ball，类型为 BP_PinBall ，ObjectReference。
  * 然后把 `cast to` 的最后一个输出连到这个 input 上。
* 小球撞击Bumper：命中后对小球施加作用力
  * 此时已经触发了手动添加的 `Bump` 函数。
  * 施加的作用力为 Bumper 指向小球。使用 `get unit direction vector` 获取单位方向向量，起点用 `GetActorLocation` 获取自身位置，终点从 `Bump` 的输入，即小球那里获取 `GetActorLocation`，然后对该单位向量，乘上一个施加的力值。
  * 求出施加的作用力后，仍然从 Bump 的输入，小球 Ball 那里拉出结点 `set velocity`，把力连上去，并且将之与 Bump 函数的主通道相连。
* Alt+移动物体，就可以复制出一样的物体。

# <i class="fa fa-star"></i> 任务五：制作Bumper材质和添加撞击时的反馈
## Bumper的材质
* 导入材质 `T_PopBumperTop.TGA` （含 `alpha 通道`）
* 创建材质 `M_BumperTop`
  * T+鼠标左键，生成 `Texture Sample` 结点：可在左侧 detail 栏选取图片作为贴图。结点的输出有直接输出图片【？】、R/G/B通道、Alpha通道等。此处选 Alpha通道。
  * L+鼠标左键，生成 `LinearInterpolate` ，来改变贴图的颜色。输入为 $A、B、Alpha$ ，当 $Alpha=0$ 时输出 $A$ ，否则输出 $B$ 。输入可以从其它地方连过来，也可以直接在 detail 里改它的 const 值。
  * 材质编辑器效果预览中，L+鼠标右键，可以`改变光线角度`。
  * 同样可以使用 `LinearInterpolate` 改变底色和 Logo 图案的粗糙度，使 Logo 看上去有质感。
  * 用 `Multiply` 结点输出到 `Emissive Color` 调整发光颜色。令 $A=Alpha$， $B=const\ value$，则 $Alpha = 1$ 处才会发光，亮度由常量值控制。
  * 如何改变发出的光的颜色：把控制亮度的常量值也改为 `Multiply` 结点，融合 Logo 本身的颜色以及常量亮度。为了实现在撞击时才发光，把常量亮度用 `ScalarParameter` 代替，输出一个 float 型值，这样后续在蓝图中就可以更改这个值来控制发光。
* 把材质应用到 Bumper
  * 进入静态网格编辑器 `SM_PopBumperBase` 中的 details 修改 Material Slots 材质插槽。

## 撞击反馈
### **1° 撞击时 Mechanism 上下弹动**
* 在 BP_Bumper 的 Tick 主通道创建新的 `TimeLine` 。
  * 可在 `TimeLine` 中给出曲线（右键 add 或者 Shift+左键，设置 f(时刻)=value ），则这个 `TimeLine` 可以根据时间函数曲线，在对应时间给出对应的值。
  * 因此 BumperBot 的上下弹动可以让它随着 `TimeLine` 变化。
  * 在viewport中观察往下弹动到 $Z=-70$ 时与 Base 的底部贴合，因此从 `TimeLine` 主通道调用 `setRelativeLocation` ，target 为 BumperBot ，new location 通过 lerp(vector) ，Alpha 输入为时间函数曲线 TimeLine， A为Alpha零时位置即原始位置，B为Alpha为一时为止即 z=-70 位置。所以 lerp 就是对这两个三维向量做线性插值生成中间值。

### **2° 撞击时 Logo 闪光**
* 利用之前在材质中创建的 `ScalarParameter` 设置亮度值
  * `set scalar parameter value on materials (BumperBase)`
  * 生成后要把对应的 `parameter name` 设定为对应的 Emissive
  * 同样，给出的参数值也可以利用时间函数曲线，作 lerp 插值，令自发光亮度随时间线性变化。
  * 注意，多次撞击，时间函数曲线只有连向 play from start 才能每次从头开始，否则会一直继续下去。
  * Alt+点线，可以去掉连线。
* 为了让 Logo 闪光时有向外的光线，在 `BP_Bumper` 中再添加 component 点光源 point light 到 base 内部
  *  $z=100$ ，抬高接近表面 Logo
  * 默认值 intensity 设为 $0$
  * 把阴影 cast shadows 关掉
* 回到 `event graph` 中，添加 `set intensity (point light)` ，同样插值一下

### **3° 撞击声音**
* 项目管理：创建 Content/Assets/Sounds/ 放撞击声资源文件 .WAV
* 单独一个文件都只有一个 WAV ，在 Sounds/ 下创建一个 Sound/Sound Cue
  * 选中五个 WAV ，进入 Sound Cue ，右键 random: multiple waves (fom selected)
  * 可以随机输出一种撞击声，然后把 output 连到 cue 原始的 output 上
* 之前为发光等内容，在主通道拉出了独立的时间线，而撞击声只要撞到的时候立刻反馈一下音频文件即可，因此要在 BumperTimeLine 之前加入主通道，串行完成。
* 添加结点 `spawn sound attached`
  * 输入 sound 即设定好的 cue
  * attach 到 BumperBase

# <i class="fa fa-star"></i> 任务六：Fliper制作
* 导入 `Fliper.FBX` 模型文件
* 创建材质 `M_Plastic`
  * 颜色设为白色
  * 粗糙度 $0.2$
* 创建材质实例 Material Instance （把材质中的某些参数如颜色等暴露出来便于修改）
  * 注意要`从 M_Plastic 创建`，MI_Plastic_White/Yellow/Blue
  * 就可以便利地产生很多同样是塑料质感但颜色不同的材质
* 在 `fliper` 静态网格编辑器中
  * 应用材质
  * 生成 `auto convex collision` 后，应用，生成 `simple collision`
* 创建新的蓝图类-actor `BP_Fliper`
  * 添加 component static mesh fliper
  * 拉一个蓝图实例到场景中，根据情况再到BP中调整 fliper 的初始位置
* **创建镜像摇臂**
  * scale x=-1 就可以在 x 方向产生镜像
  * 使用 `construction script` （构造时调用的函数）
  * 在 Content/BluePrints/ 中创建蓝图的 `Enumeration` 枚举类型 E_Direction
  * 进去后 new 一个 Left、Right
  * 在 `BP_Fliper` 中添加变量 FliperType ，类型选择为 E_Direction ，编译后可以选令其值为 Left 或 Right
  * `应用到构造中`：从 `construction script` 拉出结点 `switch on E_Direction` ，输入的 selection 把 FliperType 拖过去，输出当 Left 时不用变化，为 Right 时，`set relative scale 3D (-1,1,1)` 把它变为沿 x 轴的镜像。
* **摇臂的角度设置**
  * 之前设好的摇臂是平直的，但一般要有个倾斜角度
  * 在蓝图 BP 中创建变量 `StartRotation` 、 `EndRotation`，类型设置为 `Rotator`
  * 在 `construction` 拉出结点，`set StartRotation`，因为要根据其左右设置不同的角度，因此输入一个结点 `select`，`select` 的 index 用代表摇臂为左还是为右的 Fliper Type，然后就可以根据 Left 和 Right 设置不同的初始 rotator 值。（左 (0, 0, -70) 右 (0, 0, -110)）（我这左边要110）
  * 同理 `set EndRotation`（左 (0,0,-120) 右 (0,0,-60)）（我这左70，右-70）
  * 上两步设的是两个变量值，接下来真正设置模型相关参数
  * `SetRelativeRotation`，把 `StartRotation` 作为输入，模型的初始值，然后连到 `switch on E_Direction` 根据左右决定是否镜像。
* **摇臂旋转角度**
  * 这个行为又是在运行过程中做的， 因此也是在 `event graph` 中完成。
  * 先不考虑键盘输入，只考虑摇臂上下摇的两个事件，然后在 Begin 时进行测试。
  * 创建 `custom event` FliperUp、FliperDown
  * 拉出结点 `Move Component To` ，把 Component Fliper 作为输入。FliperUp 即 Target Relative Rotation 为 EndRotation，Down 则恢复到 StartRotaion。在 over time 设置这个 move 行为的变化所需时间。
  * 测试：Begin 时 FliperUp ，Delay 一段时间（D+鼠标左键）， 再 FliperDown ，再 Delay ，循环回 FliperUp

# <i class="fa fa-star"></i> 任务七：为游戏添加Controller
## 场景搭建（斜坡）
* Geometry Box 画刷，在摇臂墙边弄个长方体，然后`打！开！几何体编辑模式！`，可以选中几何体的点进行编辑。
## 添加 Camera
* 调整摄像机视角
  * 初始运行时UE4提供了 `DefaultPawn` 作为默认视角
  * 在左侧模式中拿出一个 `camera` ，加入场景，调整视角
  * `启用camera`：在 `detail` 中找 `auto player activation` ，把默认的 default 改为 player0
## 添加 **`Player Controller 类`**
* 设置键盘输入
  * 编辑器 `edit` -> `project settings` -> `Engine` -> `input`
  * 在 `ActionMappings` 里增加 `Left/RightFliper`，并选择添加的要响应的键
  * 如 `Left/Right Ctrl` 、`Left/Right Mouse Button`
* 创建蓝图类-Player Controller BP_PinBallController
  * 在 `event graph` 中创建功能 `InputAction LeftFliper`
* `让 Controller 确定所要控制的 Fliper` ：
  * 【① 创建两个数组变量】：在 `BP_PinBallController` 中创建变量 `LeftFlipers` ，类型改为 BP_Fliper ，且把 single variable 改成 array。（考虑可能一边有多个 Fliper ）同理创建 `RightFlipers` 。（在 variable 中 Ctrl+W 可以直接复制创建一个新的同类型变量）
  * 【② 给数组变量赋值】：创建一个 custom event - FindAllFlipers 。【获取所有摇臂】拉出结点 `get all actors of class` ，输入设定为 `BP_Fliper`。输出为 `out actors` 数组，数组中同时有 Left 和 Right 类型的 BP_Fliper。【把摇臂分成左右】对输出的数组做 `ForEachLoop` 遍历，连上主通道，此时能从输出中得到 `array element` ，对它使用 `get fliper type` ，获取它的 FliperType 属性，再 `switch on E_Direction` ，连上主通道。【把左右摇臂分别放入数组】把数组变量拖入 event graph 并 get ，再拖出结点 `Add` ，类型判断为 Left ，要加入的数组为 LeftFlipers ，并从 array element 获取要加入的元素。Right 同理。
* `InputAction LeftFliper` 就是接收到相关控制键
  * `Pressed` 时， foreachloop 遍历 LeftFliper 数组，对每个 array element 做 fliper up。同理 released 时做 fliper down。
  * 创建 InputAction RightFliper，同理。
* 在开始 begin 时调用一下 FindAllFlipers。
## 添加 **`Game Mode Base 类`**
* 有了 Controller 后还无法使用，需要创建自定义的 Game Mode Base 。
* 创建蓝图类-GameModeBase PinBallGameMode
  * `启用 BP_PinBallController `：在 details 中更改 player controller class 为自定义的 BP_PinBallController
* `启用 PinBallGameMode` ：在主界面 `worldsettings` 中（details 旁边，或window-worldsettings），把 `GameMode Override` 从 None 改为 PinBallGameMode 。
## 添加音效
* 类似 Bumper ，添加 PinBall_FliperLeft/Right ，左右由于录制时定义不一样所以倒一下。
* 创建 Cue ：根据两个 WAV 分别创建各自的 Cue。
* `使用音效` ：回到 BP_Fliper
  * 在 Fliper Up 事件发生的时候 `spawn sound attached`，输入只能选一个声音，因此添加结点 `select` 连到 sound， attached to component 把组件中的 Fliper 拖过来。
  * select 中，输入 index 为 FliperType ，左右分别选对应 Cue 。
* `调整音量大小`：cue - Detail - Sound - `Volume Multiplier`

# <i class="fa fa-star"></i> 任务八：制作Plunger（小球激发装置）
## 区域搭建
* 同样几何体编辑，把右侧墙往外拉 100 * 3 格
* 把拉出来的部分也挖一条沟
* 几何体编辑器中有 `Edit` 模式，做基本变形。 `extrude` 可以扩展新格子。
* 界面右上角可以切四窗口三视图。
* 小球沿发射轨道滑的时候可能飞出的问题
  * ① 把小球压向面板的力加大
  * ② 在上空盖个隐形板
  * ③ 把轨道做成倾斜的？
## 导入 Plunger
* `SM_Plunger.FBX`
* 加 simple box 碰撞体，用金属材质
## 创建蓝图类-actor BP_Plunger
* 添加组件 static mesh Plunger，并对应到 SM_Plunger
## **Event Graph：分析 Plunger 功能**
### **1° 充能 Charge**
* 时间函数曲线：能量在按下后一段时间内慢慢增强到最大，沿时间曲线变化，所以需要 `timeline`，并添加 float tracks，增加两个点用于插值，加完把点 auto 一下变平缓一些。
* 输出通道 update -> `SetRelativeLocation` ，new location 用 lerp(vector) ，Alpha 输入即 ChargeTimeLine 输出，此设定当 Alpha 为 $1$ 时 $Y=150$。

### **2° 释放 Release**
* S+鼠标左键，生成结点 `Sequence` ，串行执行， `Then 0` 接到 ChargeTimeLine 的 Stop 输入，把 Charge 的单独线程停掉。
* `Then 1` 直接 `move component to` 初始位置，component 输入为 Plunger

## 添加 Plunger 到场景
* edit -> project settings -> engine -> input -> action mappings
  * 添加 Charge - Space Bar
* 拖个 BP_Plunger 到场景，调整大小和位置
  * Scale 那些三维量，右侧锁住，可以三个量一起调。

## **添加对 Plunger 的控制**
* 回到 BP_PinBallController 中
* 变量设置及赋值：与摇臂的控制类似，先添加 custom event - FindPlunger，添加变量 Plunger，类型为 BP_Plunger，对 FindPlunger 用 get all actors of class 输入 BP_Plunger。然后把找到的 Plunger 赋值给变量，由于 Plunger 只是单个变量，所以直接 set 。但对于 `get all actors of class` 而言，`输出总是数组`，所以还是要 get 一下，虽然只能 get 一个下标为 0 的。
* 设置对输入的反馈响应：添加 `InputAction Charge`，Pressed 的时候调用 Plunger 的 Charge ，Release 的时候调用 Plunger 的 Release 。
* 注意回到 Begin 的地方调用 `FindPlunger`。


# <i class="fa fa-star"></i> 任务九：小球的死亡和绑定死亡事件
## 声音失效
* 检查 Cue 里输入的 WAV 是否变成空了。

## 小球飞出发射轨道问题（加盖子）
* 创建蓝图类-actor BP_Cover
* 添加组件 Box Collision
* 大小设为 $3800\times3800\times32$
* 把 detail 中 collision presets 从 `OverlapAllDynamic` （能被穿过及触发 event graph 中 overlap 事件）改为 `BlockAllDynamic`
* 最后盖到场景上方

## 自动生成小球
* 用 Plunger 为位置参照，生成小球
* 在 BP_Plunger 中
  * 添加变量 SpawnLocation 作为小球自动生成位置，类型 vector ，设为编辑器可视后勾选 show 3D widget（在场景中生成对应可视位置框）。
  * 到场景中选中位置框，拖动设定小球生成位置点。
  * 此时在 detail 显示的是对 Plunger 的`相对位置`
* **`控制小球的生成`**
  * Controller 是控制 Plunger、Fliper 等的控制器（在场景中已有的物体？），GameMode 则是对整个游戏的框架控制，小球生成是对整个游戏逻辑而言，所以设在 GameMode
  * 在 GameMode 的 event graph 中创建 custom event - SpawnBall
  * 拉出结点 `SpawnActorFromClass` ，输入 BP_PinBall 类型
  * 确定小球生成位置：`Get All Actors of Class` 获取 Plunger，输出 `get` 一下，再 `get Spawn Location`，接到 `SpawnActorFromClass` 的 `SpawnTransform` 展开出的 Location。
  * 此时接入的是相对 Plunger 位置，而所需要的是场景中的世界位置，是绝对位置。
  * （尝试了简单加上 Plunger 的位置再接入，好像不行啊2333）【？】
* **`相对位置转世界坐标`**
  * 在 BP_Plunger 中左侧新建 `Functions` - GetSpawnLocationWorld
  * 可以拉出结点 `Return Node` ，添加 output - WorldSpawnLocation ，类型选择为 vector
  * 把 `Spawn Location` 通过 `Transform Location` 加上 `GetActorTransform` 转换成世界坐标
  * 然后将 GameMode 中的简单获取 BP_Plunger.SpawnLocation 改成调用 BP_Plunger.GetSpawnLocationWorld
  * 问题：执行线接口不够。由于 GetSpawnLocationWorld 中`没有对数据的修改`，可以把它设置为`纯函数`。这样执行线接口就无了，可以用于提取数据。

## 小球死亡
* 创建蓝图类-actor BP_DeadArea
* 添加组件 Box Collision
* 当小球进入该 Box Collision 区域，判断是否小球，是则让它死
* event graph
  * ActorBeginOverlap 进入区域时触发
  * `判断是否为小球`： `cast to BP_PinBall`，从 `As BP_PinBall` 确认是小球后，`DestroyActor`

## 给小球收尸及复活
* 在 GameMode 中生成的小球，可从其 `ReturnValue` 中获取小球实例的引用 `References` 并对其做操作。
* 从 `ReturnValue` 拉出结点 `Bind Event to OnDestroy` ，绑定一个事件到这个小球被销毁的时候触发
  * 执行线相连
  * 输入 Target 即死的小球的引用
  * 输入 Event 即小球死的时候要触发的事件
    * 要触发的其实就是初始生成小球的 custom event - SpawnBall
    * 但是 custom event 不能直接从这拉线过去
    * 所以在这里建立一个中介 custom event - OnBallDestroy，并通过这个 custom event 调用 SpawnBall
* 不想立刻生成新的小球可以 delay 一下

## 给小球增加滚动声音
* 导入 .WAV：PinBall_Rolling01.WAV
* 根据 .WAV 生成 Cue
* 在 Cue 里 WAV 的 detail 中勾选 Looping 设置`循环播放`
* 在 BP_PinBall 中
  * 添加组件 component - `Audio`
  * 在 `Audio` 的 detail 中选择 cue
  * 此时不管小球动不动都会有声音
* **`设置只有小球运动时才发出声音`**
  * 给 BP_PinBall 的 tick 事件加 `sequence`，一条连向原来的 add impulse，另一条连向下面的对 `Audio` 的 `set` 执行线
  * 把 `Audio` 拖入 event graph，`set volume multiplier` 设置音量，`set pitch multiplier` 设置音调，通过模拟音量和音调来模仿小球用不同速度滚动的声音。
  * `把小球速度映射到线性小区间`：`get velocity(vector)` 获取小球的速度，`VectorLength` 取速度的模，`float/float` 除以 $2000$ 映射到小区间，再取 `Clamp (float)` 限制上下界，最后把 `return value` 连到音量和音调的 set 输入。（此处音量设 0.0-1.2，音调设 0.9-1.1）

# <i class="fa fa-star"></i> 任务十：撞击板制作 Part A
## 导入模型、设置材质
* 导入模型 `SM_PostHalf.FBX` （撞击板两端柱子，post此处为木桩的意思），导入选项勾选 auto generate collision
  * 进入静态网格编辑器，材质插槽那点 highlight 可以高亮选中部位
* 导入模型 `SM_BandExtender.FBX` （撞击板中间绳子），同样 auto generate collision

## 拼接模型
* 创建蓝图类-actor BP_Post
* **`关于 BandExtender 的形变量`**
  * 添加组件 component - static mesh - Post1，选择 static mesh 为 posthalf
  * 添加 bandextender 和 post2 ，可以发现 bandextender 和 posthalf 模型是校准过的，当两者都为 (0,0,0) 初始值时正好贴合。
  * 而另一端 post2 需要旋转180度，然后 $x$ 相对 post1 多远，绳子的 $scale_x$ 形变就是多少倍。
* **`动态添加另一个木桩`**
  * 在 BP_Post 中添加变量 Post2Location，类型为 vector，设可视并编译，show 3D widget，调整位置
  * 在 construction script 中 `add static mesh component` ，将其 return value `promote to variable` 把返回值生成为变量，重命名为 Post2。输入的 relative transform 可以拉出结点 `Make Transform` ，再把 Post2Location 拉到 Location
  * 此时添加完了 component ，但是还要对 component `set static mesh` 设置为 SM_PostHalf
* **`使两个木桩拼接处相对`**
  * 在 construction script 中设置相对位置
  * get Post1 并 `Set Relative Rotation`，使用 `Find Look At Rotation` 设置起点为 Post1Location ( get post1 relative location) ，终点为 Post2Location。
  * 同理，在另一木桩设置的 Make Transform 中给 Rotation 用 `Find Look At Rotation` 设置相反的起点与终点。
* **`添加绳子`**
  * 执行线顺下去，类似动态添加另一个木桩， `add static mesh component` ，设置 static mesh 的时候可以在结点里 set ，也可以选中 add 结点在 detail 里直接选。
  * 绳子的初始 transform 直接 get post1 的 transform 就可以贴合生成。
* **`设置绳子的形变`**
  * `set Relative Scale 3D` ，由于已经尝试过，scale 只需要 $scale_x$ 改变即可，因此从 `Post1.GetRelativeTransform` 的 return value `break transform` 分成 Location、Rotation、Scale ，再把 Scale split 成 $scale_x、scale_y、scale_z$ ，把后两者直接连到 `Set Relative Scale 3D`。
  * **`Scale_x的计算`**： 
    $$(Post1.Location() - Post2.Location()).Length() \div 100$$

# <i class="fa fa-star"></i> 任务十一：完成制作撞击板 Part B
## 准备工作
* 导入模型 SM_DropTarget.FBX 并修改材质
* 创建蓝图类 BP_DropTarget
  * 添加组件 static mesh component 设置 static mesh 为 SM_DropTarget
* **`为板添加文字`**
  * 添加子物体组件 `TextRender` DropText
  * 在 detail 中设置大小、颜色、要显示的字符串，并调整位置

## 功能设定
* **`撞击`**
  * 建立 custom event Drop事件
  * 板子被撞击时下落：一步到位，不需要过程。因此使用 `Move Component To` 设 Location 到 $z=-110$ ，Target 为 DropTarget。
  * 添加声音：执行线连出 `Spawn Sound At Location` ，声音用 Cue_Bumper 。 Location 则 `Get Drop Target` 后再 `Get World Location` 获取其在世界坐标系下的位置。
* **`复原`**
  * 建立 custom event ResetDrop事件
  * `Move Component To` ，复原到 $0$
* **`事件的触发`**
  * 在 DropTarget 的 detail 中， Collision 勾选 `Simulation Generate Hit Events`
  * 添加事件 `Event Hit` ，对应该选项，碰撞体被碰到的时候就会触发该事件。
  * `设定触发事件只执行一次`：这个选项会使碰撞体只要被接触到就一直执行 event hit ，为了避免这个问题，可以在 hit 时先用 `set collision enabled` 把选项禁用 `No Collision` ，执行完触发事件后再 `set collision enabled` 设为 `Collision Enabled`。

## **`【蓝图子类】把撞击板组合到木桩绳上`**
* 从 BP_Post 创建蓝图子类 Child Blueprint Class - BP_DropTargetSet
  * 进入子类编辑器右上角会显示父类名称
  * event graph 都会先执行父类相应操作
  * 左下点 search 旁边的眼睛可以 show inherited variables 显示继承来的变量
* 添加变量 String PostString; 设为可视，编译并设显示的字符串。
* `考虑板子之间的间隔`
  * 设绳子一端 A 到第一块板子中心距离、每两个板子中心间距、最后一块板子中心到绳子另一端 B 的距离，各为一段 $L$ 。绳长 $l$ ，板子数量 $C$ 。
  * 则有每一段长度为 
    $$ L = \frac{l}{C+1} $$
  * 因此板子中心位置，下标 $index$ 从 $0$ 开始，应有
    $$ Location = L\ *\ (\ index + 1\ ) $$
### BP_DropTargetSet 的 Construction Script 中
* 因为小写的显示难调，先全部 upper 成大写：在 construction script 中 `Get Post String().To Upper()` ，再 `Set Post String`。
* 从 `Set` 的返回值 `Get Character Array from String` ，返回值为字符数组，因此再拉出结点 `ForEachLoop` ，从 `LoopBody` 拉出结点写循环体。
* `循环体：为每个字符创建一块撞击板`
  * **`创建板`**：此处也要添加组件，但是要添加之前创建的 BP_DropTarget ，而不是 static mesh ，因此使用 `Add Child Actor Component` ，设其 Class 为 BP_DropTarget 。 split 其 transform ，开始按之前的考虑算出其 Location。
  * 绳子长度 $l$ ：  
    `(Post1.RelativeLocation() - Post2.RelativeLocation()).vectorLength()`
  * 可以在结点上设置 Toggle Comment Bubble 打注释
  * 板子数量 $C$ ：从 `Get Character Array from String` 的返回值即字符数组求其数组长度 `Length()`
  * 板子下标 $index$ ：从 `ForEachLoop` 可以获取 `ArrayIndex` 。
  * 此时能求出的 $Location$ 是一个浮点值，在 Post1 到 Post2 这个射线段上的位置比例。因此再用 Post1 到 Post2 方向的单位向量，乘上 $Location$ 值即为所需要的具体位置。
  * `get Post1().Get Forward Vector()` 再乘上上述浮点值即可。【？Look At：那玩意是 rotation 来着这里用不了】
  * **`把板子拉到绳子外`**：此时板子在两根绳子中间，因此再 `Get Post1.Get Right Vector() * float` 加上一个向右偏移量，此处 $float = 30$ 合适。
  * **`把板子上的初始字符改成 PostString 对应字符`**：`Add Child Actor Component` 给出的返回值为 `Child Actor Component` ，从返回值拉出结点 `Get Child Actor` 才能获取到实际的 Actor ，然后转换类型 `Cast to BP_DropTarget` 转换为板子。回忆之前设定的初始值是在 BP_DropTarget 中给 DropTarget 创建了显示字符的子组件 DropText 。所以从 `As BP_DropTarget` 拉出结点 `GetDropText()` 获取子组件， `set` 它的值，而这个值就从 `ForEachLoop` 获取 array element。
  * **`设置板子朝向`**：拉动木桩端的时候，板子一直朝着原来的方向，会被绳子穿模，所以要设下板子朝向。即创建的时候设置一下 Rotation ，用 `Post1.GetWorldRotation()` 即可。
### 实现板子全撞掉之后恢复板子
* 在 BP_DropTargetSet 中新建变量 TargetCounter(integer)
* 从字符数组中获取初始值
### BP_DropTarget 的 **`Event Dispatchers：与子类的通信`** 
* 新建 Event Dispatcher - OnTargetDrop
* 在触发 Event Hit 并 Drop 完之后，`Call OnTargetDrop` ，发出一条信息，让整个系统知道这个事件发生了。
### 在 BP_DropTargetSet 的 construction script 中接收 `Event Dispatcher - OnTargetDrop`
* Drop 事件对应到每个 DropTarget 板实例，因此是在创建之后，用 `Cast To BP_DropTarget` 得到的具体一块板，把这块板实例 **绑定到事件 `Bind Event to OnTargetDrop`**（类似之前绑定小球的销毁，只是销毁是内置的 destroy ，此处自己新建了事件）
* 然后接上执行线
### 在 BP_DropTargetSet 的 event graph 中处理接收到信号后的流程
* 新建 custom event - TargetDropProcess
* 把 TargetCounter 变量 -1 （可以直接用 `--` ）
* B+鼠标左键，生成结点 `Branch` （即 `if` ）
  * 判断条件 condition 即 `TargetCounter--` 后的值 `<= 0`
  * 条件成立后要遍历板子，每块设为初始值，因此发现在 construction 时还要添加数组变量，记录创建的每个板子，存在数组里。然后获取板子数组，对每个板子元素 reset 。
* 重置 TargetCounter ： set 为 DropTargets 数组长度。
### 回到 BP_DropTargetSet 的 construction ，绑定事件到 create event 并选择 TargetDropProcess
### 通信流程总结
* 板子 Drop 后，通过 `Call OnTargetDrop` 发出消息。
* 由于在创建每块板子的时候为其绑定了这个消息，接收到之后主动创建事件触发，调用 `TargetDropProcess` 进行处理。
* 最后把 TargetCounter 也置为初始值，全部复原。
### 【？】Debug
* 发现 TargetCounter 初始是 0 ，执行线没连。
* 重复撞击已经掉下的板子 TargetCounter 瞎几把跳
  * 在 Call OnTargetDrop 前加了个 Branch ， drop 前存个量判断撞的时候是否在原位，但是还是瞎几把跳。
  * frame skip 后发现：逻辑其实是对的，但是在撞到最后一块板的时候，它还没 Drop 完， TargetCounter 已经减掉了，前面的板就恢复了，然后再把最后一块板撞掉的。
  * 在 drop 的调用后面 delay 了个 0.2 等板撞掉，然后发现其实是撞完了恢复了以后又多撞了最后一块一下，行吧。

# <i class="fa fa-star"></i> 任务十二：三角撞击板制作
## 准备工作
* 导入模型 SM_SlingBandMT.FBX ，不自动生成碰撞体，并设置顶和柱子的材质
* 创建材质 M_SlingBand 作为绳子的材质
  * 颜色调白色
  * 粗糙度 0.4
  * **`World Position Offset`**：使用 `staticMeshMorphTargets` 获取模型在 3DMAX 编辑时设定的 `Morph` 量，存储的一些点的位置变化。用 `Lerp` 插值后使用到 `World Position Offset` 上，输入的 Alpha 设为 ScalarParameter - MorphPercent ，后续可在蓝图中修改。
* 给模型设置碰撞体
  * apply 一下计算一个 simple collision
  * 把绳子可弯曲的部分碰撞体删掉，之后在蓝图里手加。（涉及到使用 hit event 事件还是 overlap 事件）
## 功能设定
* 新建蓝图类-actor BP_Sling
* 添加组件 static mesh component - BP_SlingBandMT 设为 root
  * 添加子组件 capsule collision - Collision
  * 确认 collision 的 collision presets 中 overlap 勾选
* `小球撞击，绳子反弹`
  * event graph - overlap 事件： `cast to BP_PinBall` 判断是否来自小球的撞击，是小球则 `add impulse` 反弹小球。此处调整 capsule collision ，将 Location 的红轴转向朝外，即 $L_x$ 正向朝外。输入给 `add impulse` 的力，方向就可以使用 `collision.GetForwardVector()` ，乘上 $float=2500$ 。勾选 `vel change` 忽视物体重量施加绝对力。
* **`绳子发生形变运动`**
  * 是一个过程动作，因此要 `TimeLine` - SlingTimeLine ，注意 play from start 。
  * add float truck - MorphAlpha ，Shift+鼠标左键或鼠标右键创建点，创建 (0, 0) 、 (0.12, 1) 、 (0.25, 0)，然后每个点 auto 一下。
  * 在 TimeLine 过程中 `Update`：从 `static mesh component - Sling` 拉出结点 `Set Scalar Parameter Value on Materials` ， Parameter Name = MorphPercent ，Parameter Value = MorphAlpha ，连上执行线。
* 弱鸡 debug ：一开始没反应，嗯，因为执行线又忘记连了一段 orzzz... :)

# <i class="fa fa-star"></i> 任务十三：物理约束和单向门
## 物理约束实验
* 创建蓝图类 - actor BP_Test
* 添加组件 cube - Cube1 （内置的 static mesh ）
  * Ctrl+W 复制出 Cube2
  * 把 Cube1 上拉一段距离
* 添加组件 **`PhysicsConstraint`**
  * 拖到两个 Cube 中间
  * detail 中 constraint 里设置 component 1 & 2 后会有红&蓝线连接两个 component
* 给 Cube2 勾选 simulate physics
* 到场景中实验：可以选中 CameraActor 并把 details 中 `Auto Player Activation` 改回 default 便于实验。此时 play 并旋转 Cube1 ，Cube2 会在下面以 constraint 为钉子瞎几把晃。
* 回到 BP_Test ，constraint 的 detail 中 `Angular Limits` 可以设定限制的旋转方向及限制角度，角度的范围值为设定值的两倍（含正负）。

## 单向门 - 准备工作
* 导入模型 门框SM_LBracket.FBX、门框顶SM_BracketTop.FBX、门板SM_SpinnerTile.FBX，自动生成碰撞体
* 新建蓝图类-actor BP_Door
* 添加组件：门框 static mesh - LBracket
  * Ctrl+W 复制
  * Location 分别设置为 -100、100
  * Location = 100 的转 180 度
  * 同时选中两个，设 $Scale_z = 2$ ，拉高
* 添加组件：门框顶 static mesh - BracketTop
  * Location = (-100, 0, 100)
  * $Scale_x$ = 2
* 添加组件：门上活动杆？ cylinder （内置圆柱体）
  * Scale = (0.3, 0.3, 1.8)
  * 位置大约调在顶的下面即可
  * 材质调金属
* 添加组件：门板 static mesh - SpinnerTile
  * 重命名为 Door
  * Location = (0, 0, 100)
  * $Scale_z$ = 1.2

## 单向门 - 功能设定
* 添加组件： physics constraint
  * 把位置设到 cylinder 上，可以先 attach 为 cylinder 的子组件，把 Transform  的前两个量重置到与 cylinder 相同（scale 调了后会？？？拖出去后还是要再重置一下），再拖出来
  * Component 1 & 2 分别为 cylinder 和 door
  * Angular Limits 把三个都 lock 住，看下哪个能让门正常前后转就 limit 哪个
  * 此时是双向门，两边都能转
  * `把门调成只能单向转`：`Angular Rotation Offset` 可以把正负范围 [-limit, limit] 转调整到任意区间。
* 添加组件： Arrow `提示自己门的开启方向`
  * 让它指向门的旋转范围方向
  * 仅编辑时可见
* `Angular Limits` 下的 `Swing Limits` - `Soft Constraint` ：是否限死旋转范围，勾选的话旋转到范围边界还可以挣扎一下。
* Debug 
  * 门不动，忘记让门 simulate physics 了。
  * 【？】 play 以后门老歪……大概是模型拼的时候出问题了？下次复盘一下，脑子疼先睡了：应该是 cylinder 歪了，重新组了一下这三个玩意，门不歪了
  * 但是门还是乱抖 orz...
  * 瞎几把调了半天 constraint ，但是门放在面板里还是乱几把抖，把它抬到天上就稳定了！！！往上抬到一定高度就稳定了！！！它有病病！！！没有东西影响它啊？！？！？！
  * 把死亡区域变窄，天上的透明大盖子疯狂往上抬以后……从天上慢慢把它搬下去，正常了：）……？？？什么鬼东西嘤嘤嘤

# <i class="fa fa-star"></i> 任务十四：粒子效果的制作
## 准备工作
* `项目管理`：创建 Content/Assets/Particles/
* 在 Particles/ 下创建 `Particle System` - P_Bumper
* `粒子系统编辑器`
  * 预览窗口、emitters粒子发射器（有生命周期、速度等选项，选中可在 detail 里做细调）、detail 、 curve editor

## 简单的粒子制作（给 Bumper 撞击时加一圈散射粒子）
* 基本编辑
  * 删掉 velocity 项
  * 在 emitters 里右键 Location（生成位置）里选 sphere ，在 detail 中去掉 positive z 和 negative z ，勾选 surface only ，产生一个粒子圆环。
  * 勾选 detail 中的 velocity ，圆环动态扩散。
    * 但是速度有点慢，因此在 `velocity scale` 中调整速度。
    * 可以更改粒子生成的密度分布，如 `distribution float uniform` 随机生成。（默认为固定值 float ）然后调整最小最大值。
  * 预览窗口中 Time 选项可以设置预览的速度。
* **`给生成的粒子加贴图`**
  * 在 Particles/ 中创建材质 M_SimpleSpot
  * 创建 **`Particle Color`** 结点并把一通道连到 `Emissive Color`
  * 创建 **`RadialGradientExponential`** （内置生成的圆球），连到 Multiply 的 B 输入， Particle Color 的 Alpha 通道连到 A 输入，输出连到根结点的 `Opacity` （此时为灰）
  * 调整根结点 M_SimpleSpot 的 detail 中 Material->`Blend Mode` 为 **`Translucent`** ，启用 opacity
  * 同时将其 Material->`Shading Model` 调整为 `Unlit` 不压缩
  * 勾选 Usage->`Used with Particle Sprites` 以及 `Used with Static Lighting` （用于粒子、静态光照下）
  * 回到粒子编辑器，在 Emitters 的 Required 中更改材质为 M_SimpleSpot
* `调整粒子颜色`
  * Emitters - Color Over Life
  * Detail - Color Over Life - `Distribution - Constant Curve - Points - 0 & 1`
  * 其中 Point 0 的 in val = 0 指在生命周期的 $0\%$ 时刻， out val 处可设 RGB ，由于材质中连了 emissive 自发光，所以数值越大越耀眼。这里可设 （50, 10, 0.1）
* `把圆球调整为长条溅射火星`
  * Required - `Screen Alignment` 屏幕对齐。默认为 `PSA Square` ，即圆球贴图（实际从侧面看是小纸片）总是正对相机。改为 `PSA Velocity` 总是正对速度。
  * Initial Size - Start Size - Distribution - Max 调整为 (15, 60, 25) ， Min 调整为 (5, 30, 25)
* `让火星不只在圆环平面内溅射`
  * Emitters 添加属性 `Velocity - Initial Velocity`
  * Initial Velocity - Start Velocity - Max (0, 0, 400) 、 Min (0, 0, -400)
* `调整火星溅射范围幅度`
  * Emitters - `Lifetime`
  * Lifetime - Distribution - Min = 0.3、 Max = 1.2
* `调整火星速度`
  * Emitters - Sphere
  * Sphere - Velocity Scale - Min = 500、 Max = 1400
  * Sphere - `Start Radius` - Distribution - Constant = 2.0 （起始半径，即粒子出生点的随机范围）
* **`整体优化`**
  * Emitters - Spawn - `Rate` - Distribution - Constant = `粒子数量` ，可以发现有上限值
  * 默认粒子系统用 CPU 干活，在 Emitters - Required 上方空白处右键 `TypeData` - `New GPU Sprites`
  * 工具栏上 Bounds - Set Fixed Bounds
  * 然后就可以疯狂调大粒子数量（……
  * 不过这里其实要先令 Constant = 0
* `撞击时溅射火光`
  * Emitters - Spawn - `Burst`
  * 添加 `Burst List` 爆炸列表，0 - Count = 600 ，一轮仅生成一次 600 个
* `溅射一次后停止`
  * Emitters - Required
  * Required - `Duration - Emitter Loops`
    * Emitter Loops = 0 时无限循环
    * 所以令其 = 1
* **`把粒子系统应用到 Bumper `**
  * BP_Bumper 的 event graph 中，产生声音 spawn sound attached 之后，`Spawn Emitter At Location` 使用粒子效果， Location 即 BumperBase.WorldLocation()

# <i class="fa fa-star"></i> 任务十五：晃动桌子让小球偏移
## 准备工作
* edit - project settings - engine - input
  * 添加 actionmapping
  * TiltLeft - left (keyboard)
  * TiltRight - Right (keyboard)
## 功能设定
* 同样是对物体的控制，所以进入 BP_PinBallController
* 新建两个结点 `InputAction TiltLeft&Right` ，当按下按键会触发对应事件
* 新建函数 Function - Tilt
  * 让事件结点去调用 Tilt() 函数
  * 为了区别触发的是哪个事件，给 Tilt() 新增 input - Direction (E_Direction类型)
* **`晃动桌子 - 小球的反应`**
  * 先获取小球： `Get All Actorc Of Class` （注意是 get all ）， 输入 Class = BP_PinBall 。在 out actors 处先 **`检查输出数组是否为空，防止空指针`**（比如小球死与复活的间隙），即 check length >= 1 ，branch true 时 ForEachLoop （便于如果要扩展小球数量）。
  * 然后循环体中写对任意小球要做的行为。
  * 给小球施加力： `Add impulse` ，根据左右的不同施加不同方向的力，所以拉出结点 `select` ，而方向从调用处的 Direction 获取。这里用 Left = (0, -500, 0) ，Right = (0, 500, 0) 。最后勾选 `vel change` 施加绝对力。`由于这里不是每帧执行，而是根据键盘输入触发的事件，所以不用考虑 *delta time。`
* **`晃动桌子 - 镜头震动`**
  * 当所有球的力施加完以后震一下镜头：所以从 ForEachLoop 的 Completed 拉出结点 **`Client Play Camera Shake`** 。
  * **`Client Play Camera Shake`** 的输入需要一个 `Camera Shake Class` ，所以到 Content/BluePrints/ 创建 蓝图类 - camera shake PinBallCamShake 。进入设置 `Oscillation` - Duration 晃动的持续时间，此设 0.25 。下面的 in time & out time 是进入晃动和离开晃动的缓冲时间。下面的 Rot Oscillation 是旋转角度。此设 `Loc Oscillation` 的 Y 轴，值 Amplitude = 1000 ，次数 Frequency = 1 ，每次都从中心震 Initial Offset = Zero 。
  * 回到 BP_PinBallController 中输入该类。
  * `Play Space` 表示以哪个坐标系震动。在主界面编辑的 scale 右边，可以切换模型坐标系和世界坐标系。然后还可以用 `User Defined` 坐标系。
  * 此处 `User Defined` 后仍然 `select` ，根据 Direction 的不同，设定不同的值。
  * `Get Player Camera Manager` 再 `Get Camera Rotation` ，连到 Left 。对于 Right ，即将 Left 的输入再旋转 180 度，因此 `combineRotation` (0, 0, 180) ，连到 Right 。（这个值可以回到主界面看一下怎么转）
* 震动的幅度等，都可以在 `Camera Shake Class` 里多调参（……
* **`限制晃动的次数`**
  * 这是游戏玩法上的设置，所以在 GameMode 里搞：添加变量 TiltCount (int) 。
  * 实际用到，又是在想要 Tilt() 晃动的时候去做判断，所以再去 Controller 里面用。
  * （感觉 GameMode 有点像是全局区一样的感觉？）
  * 在 `Tilt()` 开始的地方加上对次数的判断：先 `Get Game Mode` 然后 `Cast To PinBallGameMode` 再拖出结点 `TiltCount` 来获取次数变量，做判断加 branch 。可以把 `cast to` 设为 pure 去掉执行线端口。
  * 在 `Tilt()` 结束的地方加上对计数器的更改：`ForEachLoop Completed` 后将其 `--`。
  * 小球重生时将计数器重置为初始值：在 GameMode 中 `SpawnBall` 的开始处 set 一下 TiltCount ，可以直接在结点上设置，也可以 `Get Class Defaults` 获取其默认值。

# <i class="fa fa-star"></i> 任务十六：弹球桌贴图与打包与总结
## 桌子贴图
* 导入 Texture T_Fibers.tga
* 创建材质 M_Floor
  * 直接把材质模型 T_Fibers 拖到材质编辑器里面可以直接生成结点，一通道连 Base Color 。
  * 预览调成方块。
* `调整材质成类似木地板的颜色`
  * 将材质模型结点一通道与 color (vector) 做 `融合 Multiply` ，color 连 A ，材质模型连 B 。输出到 Base Color ，然后调 color 的颜色。
* `把黑色条纹变淡`
  * 融合后再线性插值 lerp 一下，在主色调 color 与融合后的颜色 Multiply 输出，两个颜色之间作插值，插值结果输出到 Base Color 。
  * 调整 lerp 的 const alpha = 0.7 。
* `让纹理上的线条分布变稀疏`
  * 材质模型拉出的结点 `Texture Sample` 的 `UVs` 输入，可以输入 `TextureCoordinate` 控制贴图坐标。
  * `U/V Tiling` 表示单位面积上，横纵坐标放了多少贴图。
  * 总是要改两个值比较麻烦，可以连个 Multiply 然后改 Multiply 的 constant 。就是把 TexCoord 结点里面所有的量都 *constant 。
* `纹理放到桌上方向不对`：把桌子转一下。注意是转 surface properties ，别把桌子转了傻崽（……
* `使纹理横纵交错`
  * 在 Multiply 后加个 `Swizzle` ，连二维的通道输入输出，再连到另一个相同的 Texture Sample UVs 输入。
  * 把两个 Texture Sample 融合 Multiply ，输出到 lerp 前的融合里。
* `使横纵纹理清晰度不同`
  * 在横向纹理与纵向融合之前，把横向 lerp 一下。
* 其它属性： Metallic = 0 ， Roughness = 0.75 。
* 然后调调调，调完去主界面选中所有地板，把材质拖进去。
* `发射通道处分割的几个地方纹理差异大`
  * 选中所有地板，在 detail 的 `Geometry` 里选 `Alignment` 为 `Align Surface Planar Floor` 地面对齐。
* 墙壁颜色
  * 选中所有顶面，在 detail - Geometry - select 选 `Select All Adjacent Surfaces` 获取所有相邻面。
  * 然后拖材质。
* 整完以后在工具栏 `Build` 一下就能去除场景中的 Preview 水印（……

## 打包
* File - package project - windows 但直接这样会有问题（
* 补充：`把场景中自动出来的 Default Pawn 去掉`
  * world settings - Game Mode
  * Default Pawn Class 设为 None
### **打包配置**
* 所以先要去 windows 下的 packaging settings
  * 设置打包的版本 Project - `Build Configuration`
    * 在主界面编辑的时候按 `~` 可以调出控制台
    * 当打包的版本为 Development 时保留控制台， Shipping 去掉控制台
  * 设置打包的目录 Project - `Staging Directory`
  * 设置打包的内容 Project - `Full Rebuild` 把项目所有资源内容都打包，不勾选则自动识别有需要的资源内容
  * `Blueprints - Blueprint Nativization Method`
    * Inclusive 把蓝图内容都转成 C++ ，最终执行 C++ 代码，提升游戏运行效率
  * `Packaging（展开） - List of maps to include in a packaged build`
    * 选择打包的地图，如果有多个地图，可以暂时将一些保留在本地不打包
    * 将需要打包的 .umap 添加进该选项
* 在设置里 Project - Maps & Modes
  * Default Maps - Game Default Map 设为 MainLevel
* 最后保存一下 file - save all levels
* 可以打包了！！！
### 打包后生成的 C++ 代码位置
* 首先查到了是在`原项目目录`里面
* 其次好像每个版本的位置不一样吧……
* 目前 4.24 乱摸摸到了  
`<原工程目录>\`
`Intermediate\Plugins\NativizedAssets\Windows\Game\Source\NativizedAssets\Private`
* 但是生成的 Cpp 代码一堆下划线没有参考价值啊 orz

# 常用技巧
* 打印某个量：主通道拉出结点 `print string` ，把需要打印的量连到结点。

<i class="fa fa-star"></i>
<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->