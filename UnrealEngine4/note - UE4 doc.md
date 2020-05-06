> # Unreal Engine 4

# 属性 
* 文档：https://docs.unrealengine.com/zh-CN/Programming/UnrealArchitecture/Reference/Properties/index.html
## 声明
* 宏UPROPERTY
  * `UPROPERTY([specifier, specifier, ...], [meta(key=value, key=value, ...)])`  
    `Type VariableName;`
  * 定义变量说明符和元数据。
## 核心数据类型
### 整型
* `int`或`uint`+位大小。（`int8`、`int64`）
* 可作`位掩码`（类似bitset？可见于编辑器下拉框，可自定义标志位名）
  * 声明形式：默认标志位名“Flag 1”、“Flag 2”、……  
    `UPROPERTY(EditAnywhere, Meta = (Bitmask))`  
    `int32 BasicBits;`
  * 自定义标志位名：定义枚举类型  
    `UENUM(Meta = (Bitflags))`  
    `enum class <EnumTypename>`  
    `{`  
    　　`FlagName1, `  
    　　`FlagName2, `  
    　　`...`
    `};`  
    在定义位掩码时引用该枚举类型。  
    `UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "<EnumTypename>"))`  
    `int32 <BitmaskTypeName>;`
### 浮点
* 标准C++浮点类型。
### 布尔
* C++的bool类型或位域。  
`uint32 test1 :1;`  
`bool test2;`
### 字符串
* UE4支持的三种核心类型字符串

    类型 | 说明
    ---- | ----
    FString | 动态字符数组
    FName   | 全局字符串表中不可变&不区分大小写的字符串的引用
    FText   | 本地化字符串相关

* 更详细的总览文档：https://docs.unrealengine.com/zh-CN/Programming/UnrealArchitecture/StringHandling/index.html

## 属性说明符 & 元数据说明符
* 见属性文档末尾：https://docs.unrealengine.com/zh-CN/Programming/UnrealArchitecture/Reference/Properties/index.html

# 
