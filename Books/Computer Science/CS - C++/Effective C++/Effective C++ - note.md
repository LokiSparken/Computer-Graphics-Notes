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
* [Chapter 1 - Accustoming Yourself to C++ 让自己习惯 C++](#chapter-1---accustoming-yourself-to-c-让自己习惯-c)
  * [Item 1 - View C++ as a federation of languages](#item-1---view-c-as-a-federation-of-languages)
  * [Item 2 - Prefer consts, enums, and inlines to #defines](#item-2---prefer-consts-enums-and-inlines-to-defines)
  * [Item 3 - Use const whenever possible](#item-3---use-const-whenever-possible)
  * [Item 4 - Make sure that objects are initialized before they're used](#item-4---make-sure-that-objects-are-initialized-before-theyre-used)
* [Chapter 2 - Constructors, Destructors, and Assignment Operators 构造/析构/赋值运算](#chapter-2---constructors-destructors-and-assignment-operators-构造析构赋值运算)
* [Chapter 3 - Resource Management 资源管理](#chapter-3---resource-management-资源管理)
* [Chapter 4 - Designs and Declarations 设计与声明](#chapter-4---designs-and-declarations-设计与声明)
  * [Item 18 - Make interfaces easy to use correctly and hard to use incorrectly](#item-18---make-interfaces-easy-to-use-correctly-and-hard-to-use-incorrectly)
  * [Item 19 - Treat class design as type design](#item-19---treat-class-design-as-type-design)
  * [Item 20 - Prefer pass-by-reference-to-const to pass-by-value](#item-20---prefer-pass-by-reference-to-const-to-pass-by-value)
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

## Chapter 1 - Accustoming Yourself to C++ 让自己习惯 C++
### Item 1 - View C++ as a federation of languages
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

### Item 2 - Prefer consts, enums, and inlines to #defines
### Item 3 - Use const whenever possible
### Item 4 - Make sure that objects are initialized before they're used

## Chapter 2 - Constructors, Destructors, and Assignment Operators 构造/析构/赋值运算

## Chapter 3 - Resource Management 资源管理

## Chapter 4 - Designs and Declarations 设计与声明
### Item 18 - Make interfaces easy to use correctly and hard to use incorrectly
### Item 19 - Treat class design as type design
### Item 20 - Prefer pass-by-reference-to-const to pass-by-value
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
