# Unreal & HoloLens 开发指北

## 配置需求
* Windows 10 专业版/企业版/教育版：仿真器所需，[家庭版不支持仿真器使用的 Hyper-V](https://docs.microsoft.com/zh-cn/windows/mixed-reality/develop/platform-capabilities-and-apis/using-the-hololens-emulator#hololens-2-emulator-overview)
* VS 2019 Installer Settings
  * .NET 桌面开发
  * 使用 C++ 的桌面开发
  * 通用 Windows 平台开发
    * USB 设备连接性
    * C++ (v142) 通用 Windows 平台工具
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
1. 创建 UE 项目
2. 设置 UE AR 会话
   * AR Session 保存一些世界设置，对齐/遮挡设置等。
3. 启动/停止 AR 会话 - 关卡蓝图
4. 创建玩家对象
5. [打包项目](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/HowTo/PackageApp/index.html)
6. [安装到 HoloLens 2 Emulator](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/QuickStartEmulator/index.html)

## [流式传输](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/QuickStartStreaming/index.html)（无需打包，Device Only？）
### **`1. HoloLens 配置`**
### **`2. `**


## References
1. 基本配置：https://blog.csdn.net/dik_dong/article/details/107688395
   * [MixedRealityToolkit](https://github.com/microsoft/MixedRealityToolkit-Unreal)
   * [Intro to Unreal + MRTK for HoloLens 2](https://channel9.msdn.com/Shows/Mixed-Reality/Intro-to-Unreal--MRTK-for-HoloLens-2)
2. [HoloLens 仿真器的安装与使用](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/QuickStartEmulator/index.html)
3. [HoloLens 面板介绍](https://docs.microsoft.com/zh-cn/windows/mixed-reality/develop/platform-capabilities-and-apis/using-the-hololens-emulator#hololens-2-emulator-overview)
4. [UE for HoloLens 项目打包选项](https://docs.unrealengine.com/en-US/SharingAndReleasing/XRDevelopment/AR/HoloLens/HowTo/PackageApp/index.html)
5. **[Create a HoloLens 2 app with Unreal Engine and Mixed Reality UX Tools | Inside Unreal](https://www.youtube.com/watch?v=u_qR-1DrvMg&t=167s)**