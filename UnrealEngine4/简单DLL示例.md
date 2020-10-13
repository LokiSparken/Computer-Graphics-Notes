# 自建简单DLL库示例
## VS2017创建新项目
* 创建`Windows控制台应用程序ConsoleApplication - MyLib`
* 修改项目配置属性
  * 平台 `x64`
  * 项目 - 属性 - 配置属性 - 常规 - 配置类型改为 `dll`
* 创建头文件、源文件`Mylib.h`、`Mylib.cpp`
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
#include "MyDllTest.h"

float DLL_EXPORT getCircleArea(float radius)
{
	return (3.14 * (radius * radius));
}
```

* F7编译得到 `.dll`
* 测试进度：可在UE4中获取句柄，导入函数，成功调用函数

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

