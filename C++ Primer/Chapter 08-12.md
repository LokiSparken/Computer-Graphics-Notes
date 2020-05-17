> # <i class="fa fa-book-open"></i> C++ Primer
> Author: Stanley B. Lippman、Josée Lajoie、Barbara E. Moo  
> Edition: 5th

# <i class="fa fa-star"></i> Chapter 08：

# <i class="fa fa-star"></i> Chapter 09：

# <i class="fa fa-star"></i> Chapter 10：

# <i class="fa fa-star"></i> Chapter 11：

# <i class="fa fa-star"></i> Chapter 12：动态内存
## 12.1 动态内存与智能指针
* C++ 动态内存管理
  * `new` 在动态内存中为对象分配空间并返回一个指向该对象的指针，可选择对其初始化
  * `delete` 接受一个动态对象的指针，销毁对象并释放关联内存
* 动态内存的问题：确保在正确的时间释放内存。
  * 忘记释放内存，导致内存泄漏
  * 在有别的指针引用该内存的情况下释放，会使相关指针变成非法指针
* `智能指针` C++11 提供智能指针，自动释放对象，两种智能指针的区别在于`管理底层指针的方式`
  * `shared_ptr` 允许多个指针指向同一对象
    * 伴随类 `weak_ptr` ，一种弱引用，指向 shared_ptr 所管理的对象
  * `unique_ptr` “独占”指向对象
  * 头文件 "memory.h"

### **Shared_ptr 类**
```cpp
shared_ptr<string> p;

// shared_ptr 和 unique_ptr 都支持的操作
p       // 用作条件判断，不为空则 true
*p      // 获得指向的对象
p.get() // 获得内置指针。使用时要注意，当智能指针释放后，指向的对象消失。
swap(p, q)  // 交换 p 和 q 中的指针
p.swap(q)
```
* `make_shared<T> (args)`
  * 最安全的分配和使用动态内存的方法。
  * 用 args 构造给定类型的对象，不传参则值初始化，返回 shared_ptr 。
    * 对类类型对象，值初始化与默认初始化相同。
    * 对内置类型对象，值初始化有良好定义的值，默认初始化则未定义。
  * 常用 `auto p = make_shared<T> (args)`
* shared_ptr 拷贝和赋值
  * 可以认为 shared_ptr 有一个关联的计数器 —— 引用计数
  * 只要拷贝一个 shared_ptr 计数器就会递增，包括作为参数传递，作为函数返回值
  * 总之就是统计有多少个指针指向特定对象。
  * `计数器为 0 时自动释放管理的对象。`
* shared_ptr 自动销毁管理的对象
  * 释放时调用析构函数。
* shared_ptr 自动释放关联内存
  * 只要有任何 shared_ptr 对象引用一块内存，内存就不会被释放。
  * `所以在容器中重排数据，要记得把不需要的部分 erase ，防止内存的浪费。`
* **`使用动态内存的原因`**
  * 不清楚需要用多少对象：如容器类
  * `不清楚所需对象准确类型`：见第 15 章
  * `在多个对象间共享数据`
* **`使用动态内存让多个对象共享相同的底层数据`**
  * 条件：某个类希望对象的不同拷贝之间共享相同的元素。  
  * 情况：该类有一个对象 A 进入了一个新的作用域，在其中与生存期只在该作用域的对象共享相同元素。离开作用域时，原来的对象生存期结束被销毁，但是 A 仍然要保持有效。

### **直接管理内存**
* 使用 new 动态分配和初始化对象
  * 自由空间分配的内存是无名的，所以 new 不能对其分配的对象命名，只返回指针。
  * `默认情况下，动态分配的对象是默认初始化的。`
    * 默认初始化：由变量类型、位置决定的默认值。
    * 内置类型、组合类型对象的值未定义，类类型对象使用`默认构造函数`初始化。
  * 可以根据 new 的对象类型做各种初始化，但要用 auto 判定指针类型的话，`仅当括号中只有单一初始化器才可行`。（因为要根据初始化器推断类型）
* 动态分配的 const 对象
  * 返回指向 const 的指针
* 内存耗尽
  * 默认情况下，当 new 不能分配所要求的内存空间，会`抛出一个类型为bad_alloc的异常`。
  * 用`定位 new 表达式`向 new 传递额外参数：`new (nothrow) int`
    * 无法分配内存时，不抛出异常，返回空指针。
  * bad_alloc 和 nothrow 定义在头文件 new.h
* 释放动态内存
  * `delete 表达式`
  * 销毁对象并释放对应内存。
* 指针值和 delete
  * `编译器无法识别的情况（未定义行为）`：释放静态对象（并非 new 分配的内存）、多次释放相同指针
  * const 动态对象直接释放，不需要特殊对待
* 动态对象的生存期直到被释放时为止。
* **`手动管理动态内存的问题`**
  * 忘记 delete 
  * 使用已经释放的对象
    * 可以在 delete 后把相关指针置为 nullptr 
    * 但对于多个指针指向同一对象的情况，很难找到所有相关指针去置空，导致很多`空悬指针`
  * 相同内存被多次释放

### **shared_ptr 和 new 结合使用**
* 接受指针参数的指针指针构造函数是 explicit 抑制隐式转换的
  * 普通的指针是`内置指针类型`，到`智能指针类型`之间需要一层转换
  * 所以必须使用直接初始化形式（用括号）
  * `shared_ptr<int> p(new int(666));`
  * 更关键的一种情况：shared_ptr 作为函数返回值时，要 `return shared_ptr<int> (new int(666));`
  * 而且，默认情况下，`用来初始化智能指针的普通指针必须指向动态内存`。
* 定义和改变 shared_ptr 的更多方法
```cpp
shared_ptr<T> p(q)          // p 管理内置指针 q 指向的对象。q 必须指向 new 分配的内存，且能够转换为 T* 类型
shared_ptr<T> p(u)          // p 从 unique_ptr u 接管对象所有权，将 u 置空
shared_ptr<T> P(q, d)       // 接管内置指针 q 指向的对象所有权，q 必须能转为 T* 类型，且 p 使用可调用对象 d 代替 delete
shared_ptr<T> p(p2, d)      // p 是 shared_ptr p2 的拷贝，并用可调用对象 d 代替 delete

p.reset()                   // 当 p 是唯一指向其对象的 shared_ptr ，reset 释放该对象，并将 p 置空
p.reset(q)                  // 同上，但将 p 置为 q
p.reset(q, d)               // 同上，用 d 代替 delete
```
* 不要混合使用普通指针和智能指针
  * 函数传参的时候，隐式转换可以限制传入普通指针。但是调用时也尽量不要显式转换。
  * 如果显式转换了，那么 `shared_ptr 接管对象后，不应再用内置指针访问其管理的内存`。
* `shared_ptr.get()` 返回一个内置指针，指向智能指针管理的对象。
  * 用途：向不能使用智能指针的代码传递一个内置指针。
  * 注意点：  
    ① 要确定使用该内置指针的代码不会 delete 它。  
    ② 永远不要用 get 初始化/赋值另一个智能指针。（否则两个 shared_ptr 相互独立，如计数器都为 1 ，那么一个挂了另一个就失效，而且会多次释放相同内存区域。）
* 其它 shared_ptr 操作
  * `shared_ptr.reset()` 会更新引用计数，需要时释放对象。
  * 通常在改变底层数据之前要考虑是否会影响其它共享指针：
    ```cpp
    if (!p.unique())                  // check 自己是否唯一用户
        p.reset(new string(*p));      // 不是唯一用户，为避免影响别人，开新空间
    *p += newVal;                     // 再修改
    ```

### **智能指针和异常**
* 函数的退出，无论是正常结束还是发生异常，都会销毁局部对象。
  * 智能指针都可以自动释放内存。
  * 在 delete 之前发生异常，手动管理的内存就不会被释放。
* 未良好定义析构函数的类对象，也可用 shared_ptr 做保护。
  * 【？】盲猜：把相关的用于释放资源的函数传给 shared_ptr 代替 delete
* 猜对了！`定义函数作为删除器代替 delete `。
  * `删除器的参数：一个要释放的类对象指针`

### **`智能指针坑集锦`**
* 不用相同内置指针值初始化或 reset 多个智能指针
* 不用 get() 初始化或 reset 其它智能指针
* 不 delete get() 返回的指针
* 用 get() 返回的指针，要小心失效
* 当管理的资源不是 new 分配的内存，要传删除器

### **unique_ptr 类**
* 某个时刻只能有一个 unique_ptr 指向给定对象。
  * 因此不能直接拷贝和赋值。
  * 但可以`转移控制权`：`u(q.release()) 或 u.reset(q)`
* 和 shared_ptr 一样只能直接初始化。
```cpp
unique_ptr<T> u1        // 可指向类型为 T 的空 unique_ptr，调用 delete 释放
unique_ptr<T, D> u2     // 同上，但使用类型为 D 的可调用对象释放
unique_ptr<T, D> u(d)   // 同上，但用类型为 D 的对象 d 代替 delete
u = nullptr             // 释放 u 指向对象，并置空 u
u.release()             // u 放弃控制权并返回指针，再置空 u
u.reset()               // 释放 u 指向对象
u.reset(q)              // 同上，再将 u 指向 q （内置指针）
u.reset(nullptr)        // 同上，但将 u 置空
```
* 当 release 不被用于转移控制权给其它智能指针时
  * `p.release()` 释放了控制权但没有释放内存，空间没指针能访问了，危！
  * `auto p2 = p.release()` 给了普通内置指针，要记得 delete
* unique_ptr 拷贝限制的例外：可以拷贝或赋值将要被销毁的 unique_ptr
    ```cpp
    unique_ptr<int> clone(int p)
    {
        return unique_ptr<int> (new int(p));
    }
    unique_ptr<int> clone(int p)
    {
        unique_ptr<int> ret(new int(p));
        // ...
        return ret;
    }
    ```
  * 此时编译器执行移动构造函数。C++ Primer CN 5th p473
* 向 unique_ptr 传递删除器
  * 与 shared_ptr 方式不同。
  * 编译时绑定删除器，避免间接调用删除器，提升效率。
  * 所以在创建或 reset 传递删除器的时候要给它指定类型。

### **weak_ptr**



## 12.2 动态数组







<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->