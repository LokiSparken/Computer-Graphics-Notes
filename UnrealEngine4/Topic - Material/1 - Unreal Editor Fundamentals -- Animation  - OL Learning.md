> # 虚幻引擎编辑器基础——材质
> * https://learn.unrealengine.com/course/3740804?r=False&ts=637420815260625111
> * Author：Luis Cataldi

## 基于物理的渲染介绍
* 商城资源
  * Infinity Blade Collection - Elven Ruin
* 有 PBR 材质之前：可能需要在不同明暗处做多种材质，调整高光模型以贴合环境。
* PBR 简介
  * 官方文档 Documentation Home - Engine Features - Rendering and Graphcis - Materials - Physically Based Materials
  * `有一些材质的参数测量值表`
* Material Parameters 用于定义 PBR 材质的参数
  * Base Color 反射率 Albedo：RGB 色值
  * Roughness 粗糙度：[0 镜面, 1 漫反射]
  * Metallic 金属度：0 非金属 or 1 金属，对应表面类型非传导性 nonmetal or 传导性 metal
  * Specular 高光：默认值 0.5 ，冰水牛奶皮肤等无法用默认值的需改动

## 材质编辑器
* 资源准备
  * 学习 - 蓝图（有强烈光照差别和阴暗处的地图）
  * Starter Content：SM_MatPreviewMesh_02 放入场景
* 创建 Content/Materials - Material - M_MasterMaterial
* 编辑器
  * 工具栏
    * Clean：清除当前未使用的结点
    * 连接器 Connectors：显示/隐藏连线与展开/收拢节点
    * 实时预览 Live Preview：在 viewport 看到结点的运作
    * 数据统计：打开窗口显示材质数量、`通过的着色器`、材质实际触发的指令
    * Preview Nodes：根据不同的着色器选择不同质量的预览
  * 视口
    * 内容浏览器选中模型 - teapot 预览相应模型效果
  * Palette 包含所有表达式节点，分两种类型：`Expressions`、`Functions`

## 第一个材质 1
* 节点 `Constant4Vector` RGBA
  * 取色器顶部 save 色值
  * 右侧滴管`取色`（可取编辑器任意位置颜色）
* **`材质实例 Material Instance`**：在 Material 的基础上更改相应材质参数
  * MI_Metal : M_MasterMaterial
  * 常识：金属表面反射光带相似色调，塑料反白光

## 第一个材质 2
* `LinearInterpolate`(A, B, Alpha)
* TextureSample（hard code）、`TextureSampleParameter2D`（参数化的）
* 开始连线！
  * 加贴图：`MyTexture(TextureSample).R/G/B -> Lerp.Alpha` 
  * Lerp(0.3, 0.9)
  * 强化纹理：`Multiply`(BaseColor, Texture) 
  * 法线贴图，增加表面细节
    * `MyNormal(TextureSampleParameter2D).SampleType = Normal` 采样类型（Color、Normal、Alpha……）
    * MyNormal -> Normal
