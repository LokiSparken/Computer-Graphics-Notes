> # Create a New Global Shader as a Plugin
> * https://docs.unrealengine.com/en-US/ProgrammingAndScripting/Rendering/ShaderInPlugin/QuickStart/index.html

## 创建插件
* 新建 Games 项目 - `Blank & Maximum Quality & No Starter Content`
* 新建插件 - `Blank` - PluginName : Foo

## 插件设置
* Project - Plugins - Foo
  * `1. 新建文件夹 Shaders`
  * `2. 新建文件夹 Shaders/Private`
  * `3. 新建着色器 Shaders/Private/*.usf`
* PluginName.uplugin
  * `"EnabledByDefault" : false`
  * `"Modules":[{"Type" : "Developer", "LoadingPhase" : "PostConfigInit"}]`
* 在 Plugins/Foo/Source/Foo 中
  * `1. 新建文件夹 Classes，复制 Engine/Plugins/Compositing/LensDistortion 中的 LensDistortionAPI.h、LensDistortionBlueprintLibrary.h`
  * `2. 在 Private 下复制 LensDistortionBlueprintLibrary.cpp、LensDistortionRendering.cpp`
  * `3. Generate VS project files`
* 重新打开VS，更改 .h
  * 把 `LensDistortionAPI.h` 中的 `FLensDistortionCameraModel` 改为 `FFooCameraModel`（四处需更改）
  * `LensDistortionBlueprintLibrary.h` 中做相同更改（六处），再改 Category
* 更改 .cpp
  * LensDistortionBlueprintLibrary.cpp
    * `FLensDistortionCameraModel` 改为 `FFooCameraModel`（两处）
    * `ULensDistortionBlueprintLibrary` 改为 `UFooBlueprintLibrary`（四处）
  * LensDistortionRendering.cpp
    * `FLensDistortionCameraModel` 改为 `FFooCameraModel`（六或七，有一个在注释里）
    * IMPLEMENT_SHADER_TYPE `路径指向自己创建的 *.usf`
* 在 Foo/Source 的 Foo.Build.cs 增加依赖
  * `PublicDependencyModuleNames.AddRange` 增加 `"RenderCore", "ShaderCore", "RHI"`
  * `PrivateDependencyModuleNames.AddRange` 删去 `"Slate", "SlateCore"`
* 