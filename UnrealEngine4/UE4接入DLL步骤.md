# 以插件方式集成
## 项目中新建插件
* 新建插件 - 第三方库
* 修改插件代码目录下的脚本文件 `.build.cs`
```cpp
using UnrealBuildTool;

// 得到当前路径
private string ModulePath
{
	get { return ModuleDirectory; }
}

// 得到ThirdParty文件夹的路径
private string ThirdPartyPath
{
	get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
}
```
* 为工程添加include第三方库的头文件路径
```cpp
public class GeoSOTService : ModuleRules
{
	public GeoSOTService(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
                Path.Combine(ThirdPartyPath, "GeoSOTService"),
            }
			);
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
                Path.Combine(ThirdPartyPath, "GeoSOTService"),
            }
			);
		
		// ...

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...
                "Projects",		// 为了在StartupModule中使用PluginManager找到插件所在路径
            }
			);
	}
}

```

## 链接动态DLL
* 进入插件代码 `.cpp` 中启动模块 `StartupModule`
```cpp

```
* 

# 直接加载DLL库

## dll文件复制到引擎或工程的Plugins目录

## 在工程中加入dll
* 创建UE4项目的新C++类 `DLLInvokeTest`
  * New C++ Class
  * 父类使用Blueprint Function Library
* 【暂不用】在工程中加入DLL相关头文件
  * 头文件复制到工程目录（如 `Source/GeoSOTService`）
  * 设置VS项目属性 -> VC++目录 -> 包含目录 -> 添加 `Source/GeoSOTService` 完整路径
  * 在工程中添加已有项，选择相关头文件
  * `原本是为了解决“需引入的DLL库函数返回值为自定义类型”问题`
* 在 `DLLInvokeTest.h` 中
```cpp
UCLASS()
class DLLTEST_API UDLLInvokeTest : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UDLLInvokeTest();

	// 声明导入DLL的函数
	UFUNCTION(BlueprintCallable, Category = "MyDllInvokeTest")
		static bool importDll(FString folder, FString name);
	
	// 声明引用DLL库中具体函数的方法
	UFUNCTION(BlueprintCallable, Category = "MyDllInvokeTest")
		static bool importMethodGetCircleAreaFromDll();

    // 声明从DLL引入后的可调用函数
	UFUNCTION(BlueprintCallable, Category = "MyDllInvokeTest")
		static float getCircleArea(float radius);

    // 对DLL库中所有函数做类似声明
};
```
* 在 `DLLInvokeTest.cpp` 中
```cpp
#include "DLLInvokeTest.h"
#include "Runtime/Core/Public/Misc/Paths.h"		// using FPaths
#include "Runtime/Core/Public/HoloLens/HoloLensPlatformProcess.h"	// using FPlatformProcess

// 1. 声明用于存储相应DLL函数的方法：typedef <FunctionType>(*_<FunctionName>)(<ParamList>)
typedef float(*_getCircleArea)(float radius);
// 对所有DLL中的函数做类似声明

// 2. 导入DLL库
void *dllHandle;
bool UDLLInvokeTest::importDll(FString folder, FString name)
{
	// *FPaths::GamePluginsDir()为项目插件目录，若使用引擎目录则为EnginePluginsDir()
	FString filePath = *FPaths::GamePluginsDir() + folder + "/" + name;

	if (FPaths::FileExists(filePath))
	{
		// 获取DLL库
		dllHandle = FPlatformProcess::GetDllHandle(*filePath);
		if (dllHandle != NULL)
		{
			return true;
		}
	}
	return false;
}

// 3. 从DLL库中引入具体的函数
_getCircleArea m_getCircleAreaFromDll;   // 创建实例
bool UDLLInvokeTest::importMethodGetCircleAreaFromDll()
{
	if (dllHandle != NULL)
	{
		m_getCircleAreaFromDll = NULL;
		FString procName = "getCircleArea";	// DLL库中的对应函数名，【必须严格对应】
		m_getCircleAreaFromDll = (_getCircleArea)FPlatformProcess::GetDllExport(dllHandle, *procName);  // 获取函数
		if (m_getCircleAreaFromDll != NULL)
		{
			return true;
		}
	}
	return false;
}

// 4. 供调用的接口
float UDLLInvokeTest::getCircleArea(float radius)
{
	if (m_getCircleAreaFromDll != NULL)
	{
		float out = m_getCircleAreaFromDll(radius); // 调用
		UE_LOG(LogTemp, Warning, TEXT("Successly call method <getCircleAreaFromDll> from DLL library."));
		return out;	// 返回给UE
	}
	UE_LOG(LogTemp, Warning, TEXT("Failed to call method <getCircleAreaFromDll> from DLL library."));
	return 1.0f;
}

// 在该类构造期间导入DLL库及相关函数
UDLLInvokeTest::UDLLInvokeTest()
{
	// 调用DLL库的导入
	if (importDll("DLL", "DLLProducer1.dll"))
	{
		UE_LOG(LogTemp, Warning, TEXT("DLL load ok."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DLL load failed."));
	}
	// 调用函数导入
	if (importMethodGetCircleAreaFromDll())
	{
		UE_LOG(LogTemp, Warning, TEXT("method <getCircleArea> load ok."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("method <getCircleArea> load failed."));
	}
}

```

## 踩坑
* 打印信息到屏幕
    ```cpp
    #include "Runtime/Engine/Public/EngineGlobals.h"
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(...);
    }
    ```
* 获取打包后的文件 WinNoEditor 目录
  * `FPaths::ConvertRelativePathToFull(FPaths::RootDir())`
* `TSet`
  * `TSet<FString> set;`
  * `set.Contains(...);`
  * `set.Add(...);`

## 调用dll中的函数


# 自建简单DLL库示例
## VS2017创建新项目
* 创建 `Windows 控制台应用程序 ConsoleApplication - DLLProducer1`
* 修改项目配置属性
  * 平台：`x64`
  * 项目 - 属性 - 配置属性 - 常规 - 配置类型：`dll`
* 创建头文件、源文件 `DLLProducer1.h`、`DLLProducer1.cpp`
```cpp
// .h
#pragma once
#define DLL_EXPORT __declspec(dllexport)
#ifdef __cplusplus
extern "C"
{
	#endif	
		float DLL_EXPORT getCircleArea(float radius);
	#ifdef __cplusplus

}

#endif
```

```cpp
// .cpp
#include "DLLProducer1.h"

float DLL_EXPORT getCircleArea(float radius)
{
	return (3.14 * (radius * radius));
}
```

* F7编译，在 x64 目录下得到 `.dll`

## 自定义类
* 项目配置同上
* 头文件、源文件
```cpp
// .h
#pragma once

#define DLL_EXPORT __declspec(dllexport)
#ifdef __cplusplus

extern "C"
{
#endif 
	double DLL_EXPORT getCircleArea(double radius);

	class DLLWithClass
	{
	public:
		int returnANumber(int number);
	};
#ifdef __cplusplus
}

#endif
```

```cpp
// .cpp
#include "DLLProducer2.h"

double DLL_EXPORT getCircleArea(double radius)
{
	return 3.14 * radius * radius;
}

int DLLWithClass::returnANumber(int number)
{
	return number;
}
```
* 测试进度：可在UE4中获取dll句柄



