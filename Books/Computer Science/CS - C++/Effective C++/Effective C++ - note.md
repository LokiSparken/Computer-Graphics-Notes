> # Effective C++
> * Author - Scott Meyers
> * Translator - 侯捷

目录

<!-- TOC -->

* [Chapter 0 - 导读](#chapter-0---导读)
  * [声明式 Declaration](#声明式-declaration)
  * [签名式 Signature](#签名式-signature)
  * [定义式 Definition](#定义式-definition)
  * [初始化 Initialization](#初始化-initialization)
  * [术语 Terminology](#术语-terminology)
  * [本书习惯 & 其它相关事项](#本书习惯--其它相关事项)
* [Chapter 1 - 习惯 C++](#chapter-1---习惯-c)
  * [Item 1 - 把 C++ 视为 C & 面向对象 & 模板 & STL 四个子语言](#item-1---把-c-视为-c--面向对象--模板--stl-四个子语言)
  * [Item 2 - 以 const, enum, inline（编译器）替换 #define（预处理器）](#item-2---以-const-enum-inline编译器替换-define预处理器)
  * [Item 3 - Use const whenever possible](#item-3---use-const-whenever-possible)
  * [Item 4 - Make sure that objects are initialized before they're used](#item-4---make-sure-that-objects-are-initialized-before-theyre-used)
* [Chapter 2 - Constructors, Destructors, and Assignment Operators 构造/析构/赋值运算](#chapter-2---constructors-destructors-and-assignment-operators-构造析构赋值运算)
* [Chapter 3 - Resource Management 资源管理](#chapter-3---resource-management-资源管理)
* [Chapter 4 - Designs and Declarations 设计与声明](#chapter-4---designs-and-declarations-设计与声明)
  * [Item 18 - Make interfaces easy to use correctly and hard to use incorrectly](#item-18---make-interfaces-easy-to-use-correctly-and-hard-to-use-incorrectly)
  * [Item 19 - Treat class design as type design](#item-19---treat-class-design-as-type-design)
  * [Item 20 - 尽量用 const & 代替传值](#item-20---尽量用-const--代替传值)
  * [Item 21 - Don't try to return a reference when you must return an object](#item-21---dont-try-to-return-a-reference-when-you-must-return-an-object)
  * [Item 22 - Declare data members private](#item-22---declare-data-members-private)
  * [Item 23 - Prefer non-member non-friend functions to member functions](#item-23---prefer-non-member-non-friend-functions-to-member-functions)
  * [Item 24 - Declare non-member functions when type conversions should apply to all parameters](#item-24---declare-non-member-functions-when-type-conversions-should-apply-to-all-parameters)
  * [Item 25 - Consider support for a non-throwing swap](#item-25---consider-support-for-a-non-throwing-swap)
* [Chapter 5 - Implementations 实现](#chapter-5---implementations-实现)
* [Chapter 6 - Inheritance and Object-Oriented Design 继承与面向对象设计](#chapter-6---inheritance-and-object-oriented-design-继承与面向对象设计)
* [Chapter 7 - Templates and Generic Programming 模板与泛型编程](#chapter-7---templates-and-generic-programming-模板与泛型编程)
* [Chapter 8 - Customizing new and delete 定制 new 和 delete](#chapter-8---customizing-new-and-delete-定制-new-和-delete)
* [Chapter 9 - Miscellany 杂项讨论](#chapter-9---miscellany-杂项讨论)

<!-- /TOC -->

## Chapter 0 - 导读

### 声明式 Declaration
* C++ 中继承自 C 的符号可能存在于 global 作用域或命名空间 std 内
* size_t：一个 typedef，C++ 的一种 unsigned 计数类型
  * char*-based 字符串内字符个数
  * STL 容器内的元素个数
  * vector/deque/string 的 operator[] 可接受参数类型

### 签名式 Signature
* signature 即函数的 declaration，包含：
  * `return type`
  * `parameters`
* C++ 官方定义的 signature 不包含 return type

### 定义式 Definition
* 区分
    ```cpp
    extern int x;   // 声明式
    int x;          // 定义式，此时分配内存
    ```

### 初始化 Initialization
* 构造函数（default 构造函数）
  * 可以给构造函数加 explicit 以阻止隐式类型转换（Implicit type conversions）
  * 即：禁止编译器执行 **`非预期`** 的类型转换
  * 显式（手动）类型转换仍可用
  * （default 构造函数）应“无参”或“都有缺省值”
* copy 构造函数 & copy assignment 操作符
  ```cpp
  class Widget
  {
      Widget();
      Widget(const Widget &rhs);
      Widget &operator=(const Widget &rhs); // copy assignment operator
  };
  ```
  * 注意区分调用的是哪个（有无定义出一个新对象）
    ```cpp
    ClassName a = b;    // copy 构造
    a = b;              // copy assignment 操作符
    ```
* copy 构造函数
  * 决定了一个 object 如何 passed by value（如函数传参时）（但自定义类型最好使用 Pass-by-reference-to const：[Item 20](#item-20---prefer-pass-by-reference-to-const-to-pass-by-value)）

### 术语 Terminology
* 标准模板库 STL（Standard Template Library）
  * 大部分以函数对象（function objects）实现
  * 实现方式：为 class 重载 `operator()` （function call 操作符）
* 典型的 undefined behavior：
  * 对 NULL 指针取值（dereferencing）
  * 数组越界
* 接口 Interface
  * Java/.NET 等中有相应语言元素
  * cpp 中一般指
    * 函数的 signature
    * class 的可访问元素（public/protected/private 接口）
    * 针对某 template 类型参数需为有效的一个表达式【？】
* 客户 client：即使用者
  * 鉴于自己的 * 山一般只有自己用，所以为了善待自己，要好好设计接口呢 :)

### 本书习惯 & 其它相关事项
* 本书习惯
  * 仅当 templates 与相应 functions/classes 机制有区别时点出
  * ctor、dtor 构造/析构函数的缩写
  * 命名习惯 Naming Conventions
    * lhs/rhs：left-hand/right-hand side
    * class Widget 示例名，无意义
    * `p*` - 指向 `*` 的指针
    * `r*` - 对 `*` 的 reference
    * `mf` - 成员函数
* 关于线程 Threading Consideration
  * cpp 对并发（concurrency）没有概念
  * 条件中仅对线程安全性（thread safety）作基本提示，具体使用请在实际体验线程问题后重新评估相应条款哟w
* TR1（Technical Report 1）
  * 描述加入 C++ 标准程序库的新功能的规范
  * 以 class/function templates 形式体现
  * 组件位于命名空间 std::tr1
* Boost 组织
  * boost.org
  * C++ 标准库功能实验场

## Chapter 1 - 习惯 C++
### Item 1 - 把 C++ 视为 C & 面向对象 & 模板 & STL 四个子语言
* C++ 已是一个多重泛型编程语言（multiparadigm programming language），其支持
  * 过程形式 procedural
  * 面向对象形式 object-oriented
  * 函数形式 functional
  * 泛型形式 generic
  * 元编程形式 metaprogramming
* 将 C++ 视为由相关语言组成的联邦而非单一语言
  * 在该联邦的某个次语言（sublanguage）中，有简单通用的守则
  * 组成 C++ 的四种次语言
    * C
    * Object-Oriented C++
    * Template C++：泛型编程 generic programming 部分，延伸出新的编程范型 programming paradigm - 模板元编程 TMP（Template MetaProgramming）
    * STL
* 参数传递方式的选择
  * 内置类型：pass-by-value 优于 pass-by-ref.（[Item 20](#item-20---prefer-pass-by-reference-to-const-to-pass-by-value)）
  * Object-Oriented C++ 自定义类型：pass-by-ref.-to-const
  * Template C++：const &
  * STL：迭代器、函数对象由于基于 C 指针，传值更好

### Item 2 - 以 const, enum, inline（编译器）替换 #define（预处理器）
* `#define` 的问题：e.g. `#define RATIO 1.653` 则 RATIO 在编译器处理源码前已被预处理器替换为值 1.653
  * RATIO 未进入编译器的符号表（symbol table），所以编译错误信息只能给出值 1.653。不清楚这个量是干嘛的情况下，trace 它的来源可能导致额外工作量。（对符号调试器 symbolic debugger 有相同的问题）
  * 直接 `#define` 可能导致代码相当于直接在多处使用了值 1.653，使编译所得目标代码 object code 里有多份 1.653 这个值
  * 较好的方案：以常量替换 `const double Ratio = 1.653;`
* 关于 const 指针注意区分：
  * 常量指针
  * 指向常量的指针
* class 专属的常量成员
  * 为了将其作用域（scope）限制在 class 内，要让它成为 class 的一个 member
  * 为了保证该常量对所有该 class 类型只有一份：static

### Item 3 - Use const whenever possible
### Item 4 - Make sure that objects are initialized before they're used

## Chapter 2 - Constructors, Destructors, and Assignment Operators 构造/析构/赋值运算

## Chapter 3 - Resource Management 资源管理

## Chapter 4 - Designs and Declarations 设计与声明
### Item 18 - Make interfaces easy to use correctly and hard to use incorrectly
### Item 19 - Treat class design as type design
### Item 20 - 尽量用 const & 代替传值
* 缺省情况下 C++ 以 by value 传递对象至函数：是实际实参的副本，返回值同理，`由 copy 构造函数给出`
  * 传对象用 const & 较好
  * const：对用户友好，保证内部不对其做修改
  * **`避免对象切割（slicing）问题`**：通过 by value 传子类对象给需要父类对象的参数时，会把子类特性切了（应该是隐式转换了？）。如调 virtual function 时调到的是 Father::function() 版本而非 Derived::function()
* “较小”的对象也并不意味 pass-by-value（copy 构造）的代价小，原因：
  * copy 指针意味着 copy 指针所指的每一样东西
  * 编译器对内置类型和自定义类型的处理可能不同（即使底层表述 underlying representation 相同）
    * e.g. 某对象只含一个 double，但由于其为自定义类型，不会被编译器放进寄存器。如果是裸内置类型 double 就会被放入寄存器。
    * 此时以 by reference 方式传递对象，由于 reference 常以指针实现，所以这个底层的指针可以被编译器放入寄存器。
    * 总之不同的底层处理方式也会导致最终效率不同。
  * 该对象也可能在将来修改后“变大”，并且如果包含如 string 的成员，不同的 STL 库实现版本，其大小也不一样
* 小结：`built-in types、STL iterator、function object types 传值，其余传引用。`

### Item 21 - Don't try to return a reference when you must return an object
### Item 22 - Declare data members private
### Item 23 - Prefer non-member non-friend functions to member functions
### Item 24 - Declare non-member functions when type conversions should apply to all parameters
### Item 25 - Consider support for a non-throwing swap

## Chapter 5 - Implementations 实现
## Chapter 6 - Inheritance and Object-Oriented Design 继承与面向对象设计
## Chapter 7 - Templates and Generic Programming 模板与泛型编程
## Chapter 8 - Customizing new and delete 定制 new 和 delete
## Chapter 9 - Miscellany 杂项讨论
