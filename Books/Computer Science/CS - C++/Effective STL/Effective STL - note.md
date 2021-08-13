> # Effective STL
> * Author - Scott Meyers

目录

<!-- TOC -->

* [Chapter 0 - 导读](#chapter-0---导读)
* [Chapter 1 - 容器](#chapter-1---容器)
  * [Item 1 - 慎重选择容器类型](#item-1---慎重选择容器类型)
  * [Item 2 - 不要试图编写独立于容器类型的代码](#item-2---不要试图编写独立于容器类型的代码)
  * [Item 3 -](#item-3--)
  * [Item 4 - 调用 empty() 而不是检查 size() 是否为 0](#item-4---调用-empty-而不是检查-size-是否为-0)
  * [Item 5 - 区间成员函数优先于与之对应的单元素成员函数](#item-5---区间成员函数优先于与之对应的单元素成员函数)
  * [Item 6 -](#item-6--)
  * [Item 7 -](#item-7--)
  * [Item 8 -](#item-8--)
  * [Item 9 -](#item-9--)
  * [Item 10 -](#item-10--)
  * [Item 11 -](#item-11--)
  * [Item 12 -](#item-12--)
* [Chapter 2 - vector 和 string](#chapter-2---vector-和-string)
  * [Item 13 -](#item-13--)
  * [Item 14 - 使用 reserve 来避免不必要的重新分配](#item-14---使用-reserve-来避免不必要的重新分配)
  * [Item 15 - 注意 string 实现的多样性](#item-15---注意-string-实现的多样性)
  * [Item 16 -](#item-16--)
  * [Item 17 -](#item-17--)
  * [Item 18 -](#item-18--)
* [Chapter 3 - 关联容器](#chapter-3---关联容器)
  * [Item 19 -](#item-19--)
  * [Item 20 -](#item-20--)
  * [Item 21 -](#item-21--)
  * [Item 22 -](#item-22--)
  * [Item 23 - 考虑用排序的 vector 替代关联容器](#item-23---考虑用排序的-vector-替代关联容器)
  * [Item 24 - map::operator[] 和 map::insert 的效率区别](#item-24---mapoperator-和-mapinsert-的效率区别)
  * [Item 25 - 熟悉非标准的哈希容器](#item-25---熟悉非标准的哈希容器)
* [Chapter 4 - 迭代器](#chapter-4---迭代器)
  * [Item 26 -](#item-26--)
  * [Item 27 -](#item-27--)
  * [Item 28 -](#item-28--)
  * [Item 29 - 对于逐个字符的输入请考虑使用 istreambuf_iterator](#item-29---对于逐个字符的输入请考虑使用-istreambuf_iterator)
* [Chapter 5 - 算法](#chapter-5---算法)
  * [Item 30 -](#item-30--)
  * [Item 31 - 了解各种与排序有关的选择](#item-31---了解各种与排序有关的选择)
  * [Item 32 -](#item-32--)
  * [Item 33 -](#item-33--)
  * [Item 34 -](#item-34--)
  * [Item 35 -](#item-35--)
  * [Item 36 -](#item-36--)
  * [Item 37 -](#item-37--)
* [Chapter 6 - 仿函数、仿函数类、函数与其它](#chapter-6---仿函数仿函数类函数与其它)
  * [Item 38 -](#item-38--)
  * [Item 39 -](#item-39--)
  * [Item 40 -](#item-40--)
  * [Item 41 -](#item-41--)
  * [Item 42 -](#item-42--)
* [Chapter 7 - 在程序中使用 STL](#chapter-7---在程序中使用-stl)
  * [Item 43 -](#item-43--)
  * [Item 44 - 容器的成员函数优先于同名算法](#item-44---容器的成员函数优先于同名算法)
  * [Item 45 -](#item-45--)
  * [Item 46 - 考虑使用函数对象而不是函数作为 STL 算法的参数](#item-46---考虑使用函数对象而不是函数作为-stl-算法的参数)
  * [Item 47 -](#item-47--)
  * [Item 48 -](#item-48--)
  * [Item 49 -](#item-49--)
  * [Item 50 - 熟悉与 STL 相关的 Web 站点](#item-50---熟悉与-stl-相关的-web-站点)

<!-- /TOC -->

## Chapter 0 - 导读
* STL platform：Compiler & STL Implementation
  * 一个特定编译器 + 一个特定的 STL 库的实现
* string 和 wstring：同一模板 basic_string 的实例
  * string & char & char*
  * wstring & wchar_t & wchar_t*
* 标准序列容器：vector、string、deque、list
* 标准关联容器：set、multiset、map、multimap
* 迭代器分类（按所支持的操作）
  * `输入迭代器 input iterator`：只读，在每个被遍历到的位置上只能被读取一次。（istream_iterator）
  * `输出迭代器 output iterator`：只写，在每个被遍历到的位置上只能被写入一次。（ostream_iterator）
  * `前向迭代器 forward iterator`：可对同一个位置重复读写。不支持 `operator--`。（[Item 25 的哈希容器](#item-25---熟悉非标准的哈希容器)、[Item 50 的单向链表容器](#item-50---熟悉与-stl-相关的-web-站点)）
  * `双向迭代器 bidirectional iterator`：同 forward iterator，且同时支持前后移动。**标准关联容器都提供。（包括 list）**
  * `随机访问迭代器 random access iterator`：在 bidirectional iterator 的基础上提供“迭代器算术”。
* `仿函数类 functor class`：重载了函数调用操作符 `operator()` 的类。
  * 其对象实例称为`仿函数 functor` 或`函数对象 function object`
* `绑定器 binder`：指函数 `bind1st` 和 `bind2nd()`
  * C++ 11 中建议使用 `bind()`，更灵活
* `typename`
  * 声明一个模板的形式类型参数（可用 class）
    ```cpp
    template<typename T>
    class Widget{...};
    ```
  * 声明形式类型参数的类型名（只能 typename）
    ```cpp
    template<typename C>
    bool function(const C &param){}
    ```
* 关于时间、空间优化问题的项：
  * [Item 4](#item-4---调用-empty-而不是检查-size-是否为-0)
  * [Item 5](#item-5---区间成员函数优先于与之对应的单元素成员函数)
  * [Item 14](#item-14---使用-reserve-来避免不必要的重新分配)
  * [Item 15](#item-15---注意-string-实现的多样性)
  * [Item 23](#item-23---考虑用排序的-vector-替代关联容器)
  * [Item 24](#item-24---mapoperator-和-mapinsert-的效率区别)
  * [Item 25](#item-25---熟悉非标准的哈希容器)
  * [Item 29](#item-29---对于逐个字符的输入请考虑使用-istreambuf_iterator)
  * [Item 31](#item-31---了解各种与排序有关的选择)
  * [Item 44](#item-44---容器的成员函数优先于同名算法)
  * [Item 46](#item-46---考虑使用函数对象而不是函数作为-stl-算法的参数)

## Chapter 1 - 容器
### Item 1 - 慎重选择容器类型

### Item 2 - 不要试图编写独立于容器类型的代码
### Item 3 - 
### Item 4 - 调用 empty() 而不是检查 size() 是否为 0
### Item 5 - 区间成员函数优先于与之对应的单元素成员函数
### Item 6 - 
### Item 7 - 
### Item 8 - 
### Item 9 - 
### Item 10 - 
### Item 11 - 
### Item 12 - 

## Chapter 2 - vector 和 string
### Item 13 - 
### Item 14 - 使用 reserve 来避免不必要的重新分配
### Item 15 - 注意 string 实现的多样性
### Item 16 - 
### Item 17 - 
### Item 18 - 

## Chapter 3 - 关联容器
### Item 19 - 
### Item 20 - 
### Item 21 - 
### Item 22 - 
### Item 23 - 考虑用排序的 vector 替代关联容器
### Item 24 - map::operator[] 和 map::insert 的效率区别
### Item 25 - 熟悉非标准的哈希容器

## Chapter 4 - 迭代器
### Item 26 - 
### Item 27 - 
### Item 28 - 
### Item 29 - 对于逐个字符的输入请考虑使用 istreambuf_iterator

## Chapter 5 - 算法
### Item 30 - 
### Item 31 - 了解各种与排序有关的选择
### Item 32 - 
### Item 33 - 
### Item 34 - 
### Item 35 - 
### Item 36 - 
### Item 37 - 

## Chapter 6 - 仿函数、仿函数类、函数与其它
### Item 38 - 
### Item 39 - 
### Item 40 - 
### Item 41 - 
### Item 42 - 

## Chapter 7 - 在程序中使用 STL
### Item 43 - 
### Item 44 - 容器的成员函数优先于同名算法
### Item 45 - 
### Item 46 - 考虑使用函数对象而不是函数作为 STL 算法的参数
### Item 47 - 
### Item 48 - 
### Item 49 - 
### Item 50 - 熟悉与 STL 相关的 Web 站点


