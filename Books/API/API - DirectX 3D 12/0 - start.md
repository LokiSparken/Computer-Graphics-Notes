> # DirectX 12 3D 游戏开发实践（零）：前置任务

# 环境配置
* 显卡支持 D3D12 
* Windows 10
* Visual Studio 2015 及后续版本
  * 龙书使用的是 VS2015
  * 文档推荐使用 VS2019 （包含 D3D12 图形调试工具）

# 项目配置
## 1. VS2019新建Win32项目
* 新建 - 项目 - Windows10桌面向导（Windows Desktop Wizard）
  * `勾选将解决方案和项目放在同一目录中`
  * 否则跑Demo的时候会hr failed in d3dutil.cpp
* 创建时弹出的配置选项
  * 桌面应用程序 (.exe) （Desktop Application (.exe)）
  * 勾选空项目（Empty project）

## 2. 链接DirectX库
```cpp
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
```

## 3. 头文件与源码

## 4. 目标平台设置
* 项目属性 - 配置属性（Configuration Properties） - 常规（General）
* `Windows SDK版本`应设为`10.0`

# 启动！