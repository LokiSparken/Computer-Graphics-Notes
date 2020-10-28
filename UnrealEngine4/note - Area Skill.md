# 范围技能区域显示
* 参考：https://www.bilibili.com/video/av20695016

## 资源准备
### 1. 准备好透明底的贴图
### 2. 创建材质 - 技能光圈
* 贴图拉进材质编辑器 `Multiply Particle Color` ，结果作为 自发光颜色
* 同样 Multiply 透明度通道，作为 `不透明度 Opacity`
* Material
  * `Blend Mode = Translucent`
  * `Shading Model = Unlit`
### 3. 创建材质 - 技能中心光点效果
* Material 同理设置
* Multiply 下两项，结果连到 自发光颜色、不透明度
  * Particle Color
  * `RadialGradientExponential`
## 技能光圈 - 粒子系统
* 材质使用刚创建的材质
* 粒子系统编辑器
  * Required
    * Material 应用材质
    * Duration - `Emitter Duration = 0` 多少秒生成一次
  * Spawn
    * Rate - Distribution - `Constant = 0`
    * Rate Scale - Distribution - `Constant = 0`
    * Burst - Burst List 添加元素 - `Count = 1`
  * 不需要 velocity ，删掉
  * Lifetime - Distribution - `Distribution Float Constant - Constant = 0`
  * Color Over Life
    * Alpha Over Life - Distribution - `Distribution Float Constant - Constant = 1` 始终显示
    * 对应材质中添加的 `Particle Color` 结点，Color Over Life - `Distribution = Distribution Vector Constant` - `具体颜色`
  * 右键添加 `Orientation - Locak Axis - Lock Axis Flags = Z`
  * 右键添加 `Size - Initial Size` - Distribution = Distribution Vector Constant - `X = 500`
  * 右键添加 **`Light`** - Brightness Over Life 亮度、Color Scale Over Life 光的颜色、Radius Scale 范围
## 技能中心光点效果
* 在技能光圈的粒子系统编辑器 - 发射器 - 右键 `新建 Particle Sprite Emitter`
* 在 Required - Material 应用相应材质
* Initial Size - Distribution Vector Uniform - `Max = (25, 25, 25)、Min = (10, 10, 10)`
* Color Over Life - Distribution = Constant - 调颜色
* 右键添加 Initial Location - Distribution = Uniform - `Max = (150, 150, 0)、Min = (-150, -150, 0)`

