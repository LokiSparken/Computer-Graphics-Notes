> # <i class="fa fa-book-open"></i> C++ Primer
> Author: Stanley B. Lippman、Josée Lajoie、Barbara E. Moo  
> Edition: 5th

# <i class="fa fa-star"></i> Chapter 01: 开始
## 函数
* 操作系统通过调用`main`函数来运行 C++ 程序。
  * `main`函数的返回类型必须为`int`，用来指示状态。
  * `main`返回 $0$ 表示成功，非 $0$ 返回值含义由系统定义，通常用来指出错误类型。
* 函数定义包含的四部分
  * 返回类型 return type
  * 函数名 function name
  * 形参列表 parameter list（允许为空）
  * 函数体 function body
* 类型：一种类型不仅定义了数据元素的内容，还定义了这类数据上可以进行的运算。

## 编译运行
* 命令行编译（GNU）
  * g++ [options] filename.cpp
  * 常用编译参数 options
    * 指定生成的可执行文件名：-o outfilename（不指定时默认为a.exe/a.out）
    * 指定版本：-std=c++11
    * 警告相关：-Wall打开警告、-w关闭、-v列出编译步骤
    * 优化：-O0不做优化、-O、-O1、-O2、-O3
  * 编译生成.exe/.out
  * 运行
    * Windows: filename
    * Unix: ./filename.out
  * 访问`main`的返回值
    * Windows: echo %ERRORLEVEL%（适用于 cmd ，不适用于PowerShell）
    * Unix: echo $?

## 


# <i class="fa fa-star"></i> Chapter 02: 变量和基本类型
## const 限定符
### 字面值类型
* 常量表达式的值要在编译时计算，因此声明`constexpr`的类型需要限定：只能是字面值类型。
* 字面值类型
  * 算术类型、引用、指针。
  * 字面值常量类
  * 枚举类型
* `constexpr`指针初始值：`nullptr`、$0$ 、指向固定地址对象
  * 定义于函数体外的对象地址固定不变，可用
  * 函数定义的有效范围超出函数本身的变量，可用

## 处理类型
### 类型别名 typedef、using
* `typedef <type> <new_type_name>;` 且可以连锁
* `using <new_type_name> = <type>;` C++11新标准
* 注意对指针起类型别名后，在别名前加`const`是修饰指针，而不是指向常量类型
  ```cpp
  typedef char* pstring;      // pstring是char*的类型别名
  const pstring cstr = 0;     // cstr是指向char的常量指针
  const char *cstr = 0;       // 错误，cstr是指向const char的指针

  // 所以展开应该写为
  char *const cstr = 0;       // cstr是指向char的常量指针
  ```
### auto
* 
### decltype
* 推断类型而不初始化，编译器分析表达式并得到其类型，不实际计算表达式的值。
* `decltype(<expr>) <val_name> = <init_val>;`

# <i class="fa fa-star"></i> Chapter 03: 字符串、向量和数组

# <i class="fa fa-star"></i> Chapter 04: 表达式

# <i class="fa fa-star"></i> Chapter 05: 语句

# <i class="fa fa-star"></i> Chapter 06: 函数

# <i class="fa fa-star"></i> Chapter 07: 类


<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->