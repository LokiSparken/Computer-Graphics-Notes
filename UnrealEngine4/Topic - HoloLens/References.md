> # HoloLens 开发指北

# Unity
* 配置
  * [MRTK-Unity](https://github.com/microsoft/MixedRealityToolkit-Unity)：MRTK 2.4.0、`Unity 2019.4`
* [Unity AR project template](https://docs.unity3d.com/2019.4/Documentation/Manual/xr-template-ar.html)
  * 基本 AR Session 等配置 + Camera
* 功能开发
  * [M$ & Unity 的上手文档也太友好了 8 ！！！](https://docs.microsoft.com/zh-cn/windows/mixed-reality/develop/unity/tutorials/holograms-100)
  * [空间映射](https://docs.microsoft.com/zh-cn/windows/mixed-reality/develop/unity/spatial-mapping-in-unity)
  * [Unity AR Foundation](https://docs.unity3d.com/Packages/com.unity.xr.arfoundation@2.1/manual/index.html)
* 部署
  * [Unity 部署到 HoloLens](https://docs.microsoft.com/zh-cn/azure/remote-rendering/quickstarts/deploy-to-hololens)
  * [HL1 移植到 HL2](https://docs.microsoft.com/en-us/windows/mixed-reality/develop/porting-apps/porting-hl1-hl2)

# Unreal
## 配置需求
* Windows 10 专业版/企业版/教育版：仿真器所需，[家庭版不支持仿真器使用的 Hyper-V](https://docs.microsoft.com/zh-cn/windows/mixed-reality/develop/platform-capabilities-and-apis/using-the-hololens-emulator#hololens-2-emulator-overview)
* VS 2019 Installer Settings
  * .NET 桌面开发
  * 使用 C++ 的桌面开发
  * 通用 Windows 平台开发
    * `USB 设备连接性`
    * **`C++ (v142) 通用 Windows 平台工具`**（【！】不配会导致 UE 项目打包失败）
    * Windows 10 SDK (10.0.18362.0)
    * MSVC v142 - vs 2019 C++ x64/x86 生成工具
* [Unreal](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/HowTo/PackageApp/index.html)
  * 启用插件 `HoloLens`、`Microsoft Windows Mixed Reality`
  * 引擎安装选项勾选 Target Platforms - `HoloLens`
  * 打包设置
    * Project Name
    * Publisher - （Company Name）、（Company Distinguished Name）
    * Packaging - （Signing Certificate）
    * （创建私钥密码）
    * Project Settings - Platforms - HoloLens - `Build for HoloLens Emulation/Device`

## 项目开发
### [Demo Project](https://docs.microsoft.com/en-us/windows/mixed-reality/develop/unreal/tutorials/unreal-uxt-ch1)
1. 创建 UE 项目，设置场景
2. 设置 UE AR 会话：`ARSessionConfig`
   * 放在 `Content` 根目录下。
   * AR Session 保存一些世界设置，对齐/遮挡设置等。
3. 启动/停止 AR 会话 - 关卡蓝图 `Level Blueprint`
   * 保证 AR 会话随关卡启动/停止
4. Blueprint Class - `DefaultPawn`
   * add `Camera` -> RootComponent
5. `Game Mode`
6. ue4 VR Preview Play `Problem：Black Screen`
   * 不连 HL 1  的时候 VR Preview 也能看见东西的 :) （有理由怀疑又是 HL1 的锅啊！！！
   * 【Attention】
     * MRTK-Unreal only for HL2
     * UX Tools only for HL2
     * 【？？？】connect 后只能看见 skybox：SDK？
7. [打包项目](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/HowTo/PackageApp/index.html)
   * 仅对 HL2 
8. [安装部署到 HoloLens 2 Emulator](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/QuickStartEmulator/index.html)

### [UX Tools](https://github.com/microsoft/MixedReality-UXTools-Unreal)（`HoloLens 2 Only`）

### [流式传输](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/QuickStartStreaming/index.html)（Device Only）


## 打包与部署 Tips
* VS 2019 **`通用 Windows 平台开发 - C++ (v142) 通用 Windows 平台工具`**：不安装会导致打包失败
* `打包不支持 HL 1`：does not have an appropriate application package for x86 architecture. https://forums.hololens.com/discussion/694/packaging-and-sideload 
* HL 1 demo - Galaxy Explorer：https://docs.microsoft.com/en-us/windows/mixed-reality/develop/unity/galaxy-explorer
* HL 2 & UE4 `Supported Features`：https://docs.microsoft.com/en-us/windows/mixed-reality/develop/unreal/unreal-development-overview?tabs=ue426%2Cmrtk%2Casa
* 定位问题
  * 没有 GPS：
    * [HoloLens 1 没有 GPS 传感器](https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/gps-on-the-microsoft-hololens-r4497/)
    * [HL 2 也没有](https://www.microsoft.com/en-us/hololens/hardware?SilentAuth=1&wa=wsignin1.0)
  * [空间定位点](https://docs.microsoft.com/zh-cn/windows/mixed-reality/develop/unreal/unreal-spatial-anchors?tabs=426)
  * [空间映射](https://docs.microsoft.com/zh-cn/windows/mixed-reality/develop/unreal/unreal-spatial-mapping)：“`利用空间映射，你可以将对象放置在现实世界的物理表面上。`”

## References
1. 基本配置：https://blog.csdn.net/dik_dong/article/details/107688395
   * [MixedRealityToolkit](https://github.com/microsoft/MixedRealityToolkit-Unreal)
   * [Intro to Unreal + MRTK for HoloLens 2](https://channel9.msdn.com/Shows/Mixed-Reality/Intro-to-Unreal--MRTK-for-HoloLens-2)
2. [HoloLens 仿真器的安装与使用](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/QuickStartEmulator/index.html)
3. [HoloLens 面板介绍](https://docs.microsoft.com/zh-cn/windows/mixed-reality/develop/platform-capabilities-and-apis/using-the-hololens-emulator#hololens-2-emulator-overview)
4. [UE for HoloLens 项目打包选项](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/HowTo/PackageApp/index.html)
5. **[Create a HoloLens 2 app with Unreal Engine and Mixed Reality UX Tools | Inside Unreal](https://www.youtube.com/watch?v=u_qR-1DrvMg&t=167s)**