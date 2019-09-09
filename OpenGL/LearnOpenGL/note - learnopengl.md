> # <i class="fa fa-star"></i> LearnOpenGl
> * URL: learnopengl.com & learnopengl-cn.github.io
> * Notes about the tutorial.
> * Learn about OpenGL 3.3.

# <i class="fa fa-star"></i> Introduction

# <i class="fa fa-star"></i> Getting started
## OpenGL
* OpenGL本身是一个规范（specification）。
  * 规定了每个函数的行为和输出，内部具体实现由OpenGL库的开发者自行决定。
  * 实际OpenGL库开发者多为显卡厂商。
* OpenGL演变
  * 早期的立即渲染模式（Immediate mode，也即固定渲染模式），效率和灵活性低，OpenGL3.2起废弃
  * 核心模式（Core-profile），高灵活性和效率，但需要理解OpenGL运作细节和图形编程

## 扩展
* 显卡公司提出的新特性、渲染上的大优化等，通常以扩展的方式在驱动中实现。
* 不必等待OpenGL新规范面世即可使用，只要简单检查显卡是否支持此扩展。
* 通常，一个扩展受众很广时，将成为未来OpenGL规范的一部分。
* 扩展使用的代码例子：
```cpp
if (GL_ARB_extension_name)
{
    // 使用硬件支持的全新现代特性
}
else
{
    // 不支持此扩展的显卡：用原来的方式完成
}
```

## 状态机（State Machine）
* OpenGL是一个状态机
  * 以变量来描述OpenGL当前应该如何运行。
  * OpenGL的状态通常称为OpenGL上下文（context）。
  * 更改OpenGL状态的一般途径：设置选项、操作缓冲，最后使用当前OpenGL上下文来渲染。
  * 如设置当前OpenGL的状态（设置上下文变量），使其作线段或画三角形。
* OpenGL中的函数
  * 状态设置函数（State-changing Function）：改变上下文。
  * 状态使用函数（State-using Function）：根据当前OpenGL的状态执行一些操作。

## 对象
* OpenGL内核：C语言编写的库。
  * 支持多种语言的派生。
  * 但C的一些语言结构不容易被翻译到其它高级语言，因此引入了一些抽象层如“对象”。
* OpenGL中的对象
  * 指一些选项的集合，代表OpenGL状态的一个子集。
  * 如用一个对象代表绘图窗口的设置，则其内有一些成员，用来设置大小和支持的颜色位数等。
* OpenGL的数据类型
  * 其有自己的基本类型，改为语言自带类型可能不造成影响，但用OpenGL自身基本类型更安全。
  * 可以保证在各平台中每一种类型的大小统一。（当然也可以使用其它定宽类型(Fixed-width Type)来实现。）

# <i class="fa fa-star"></i> Creating a window


<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->