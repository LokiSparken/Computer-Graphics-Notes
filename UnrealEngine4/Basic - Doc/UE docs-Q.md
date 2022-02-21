> # Unreal Engine Doc Questions

**Content**

<!-- TOC -->

* [range replacement](#range-replacement)
* [UObject 等 Gameplay 核心基类概念及其关联](#uobject-等-gameplay-核心基类概念及其关联)
  * [UCLASS](#uclass)
* [模块编译](#模块编译)
* [委托](#委托)
* [Editor & Slate](#editor--slate)

<!-- /TOC -->

## range replacement

（为容器提供的 range for 基础）如何实现？

## UObject 等 Gameplay 核心基类概念及其关联
### UCLASS
* 说明符与元数据声明格式

    ```cpp
    UCLASS([specifier1=setting1, ...], [meta(key1="value1", ...)])
    class ClassName { };

    UFUNCTION([specifier1=setting1, ...], [meta(key1="value1", ...)])
    ```
* 超类在其构建函数中创建名为"SomeComponent"和"SomeOtherComponent"的子对象，但由于 FObjectInitializer 的原因，该操作将不会执行。

    ```cpp
    AUDKEmitterPool::AUDKEmitterPool(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("SomeComponent")).DoNotCreateDefaultSubobject(TEXT("SomeOtherComponent")))
    {
        // 在此处初始化 CDO 属性。
    }
    ```
* 将线程从面向过程转为面向对象的问题（thunk）
  * 
* 

## 模块编译


## 委托

## Editor & Slate


