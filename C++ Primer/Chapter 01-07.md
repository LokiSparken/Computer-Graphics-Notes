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
## 3.6 多维数组
### 使用范围 for 语句处理多维数组
* 使用 auto + range for 的时候，除了最内层，其它循环控制变量都应该是引用类型。
  ```cpp
  int a[5][5] = {{1,2,3,4,5}};
  for (auto &row : a)   // 必须为引用
    for (auto col : a)  // 最内层：需修改时才必须设为引用类型
      read(col)
  ```
* 原因分析
  ```cpp
  auto row = a[0];  // row 是指向 int 类型的指针
  // 因为 a[0] 是 a[0][0] 为首元素的数组名，所以实际上是 a[0][0] 的地址

  auto &row = a[0]; // row 是一个引用，绑定到 a[0] 数组
  // 使用引用，直接绑定名字，就可以避免转化为指针
  ```
  * 验证：可使用 `std::cout << typeid(row).name();` 输出 auto 判定的类型
  * 返回值分别为 `Pi` - 指向 int 类型的指针，`A5_i` 含有 5 个 int 型元素的数组

# <i class="fa fa-star"></i> Chapter 04: 表达式
## 4.1 基础
### 4.1.1 基本概念
* 左值和右值
  * 左值：当对象被用作左值，用的是其`身份（在内存中的位置）`
  * 右值：当对象被用作右值，用的是其`值（内容）`
* 关键字 `decltype` 
  * 若表达式求值结果为左值，得到引用类型
  * 若表达值求值结果为右值，得到指向该右值的指针
### 4.1.3 求值顺序
* 四种明确规定运算对象求值顺序的运算符
  * 逻辑与 `&&`
  * 逻辑或 `||`
  * 条件 `?:`
  * 逗号 `,`
* 对于未指定执行顺序的运算符，若表达式同时修改某对象又使用它，则会产生未定义行为。
  * 如 `<<` 运算符：`cout << i << " " << ++i << endl; // undefined`
  * 例外：改变对象的子表达式内嵌在其它表达式内，如 `*++iterator`



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