> # <i class="fa fa-star"></i> LearnOpenGl
> * URL: learnopengl.com & learnopengl-cn.github.io
> * Notes & Tips

<!-- TOC -->

* [1. Introduction](#1-introduction)
* [Part Ⅰ - Getting started](#part-ⅰ---getting-started)
  * [2. OpenGL](#2-opengl)
    * [扩展](#扩展)
    * [状态机（State Machine）](#状态机state-machine)
    * [对象](#对象)
  * [3. Creating a window](#3-creating-a-window)
    * [Intro: GLFW](#intro-glfw)
    * [Intro: GLAD](#intro-glad)
    * [Settings: Windows10 VS2019 GLFW GLAD 完全配置踩坑结果](#settings-windows10-vs2019-glfw-glad-完全配置踩坑结果)
      * [下载](#下载)
      * [配置目录结构 `folder - oglsettings`](#配置目录结构-folder---oglsettings)
      * [项目配置](#项目配置)
  * [4. Hello Window](#4-hello-window)
  * [窗口创建](#窗口创建)
    * [**GLAD和GLFW头文件**](#glad和glfw头文件)
    * [**main函数：实例化GLFW窗口**](#main函数实例化glfw窗口)
  * [5. Hello Triangle](#5-hello-triangle)
  * [6. Shaders](#6-shaders)
  * [7. Textures](#7-textures)
  * [8. Transformations](#8-transformations)
  * [9. Coordinate Systems](#9-coordinate-systems)
  * [10. Camera](#10-camera)
  * [11. Review](#11-review)
* [Part Ⅱ - Lighting](#part-ⅱ---lighting)
* [Part Ⅲ - Model Loading](#part-ⅲ---model-loading)
* [Part Ⅳ - Advanced OpenGL](#part-ⅳ---advanced-opengl)
* [Part Ⅴ - Advanced Lighting](#part-ⅴ---advanced-lighting)
* [Part Ⅵ - PBR](#part-ⅵ---pbr)
* [Part Ⅶ - In Practice](#part-ⅶ---in-practice)
* [Part Ⅷ - 2D Game](#part-ⅷ---2d-game)
* [To Be Continued...](#to-be-continued)

<!-- /TOC -->

# 1. Introduction

# Part Ⅰ - Getting started
## 2. OpenGL
* OpenGL本身是一个规范（specification）。
  * 规定了每个函数的行为和输出，内部具体实现由OpenGL库的开发者自行决定。
  * 实际OpenGL库开发者多为显卡厂商。
* OpenGL演变
  * 早期的立即渲染模式（Immediate mode，也即固定渲染模式），效率和灵活性低，OpenGL3.2起废弃
  * 核心模式（Core-profile），高灵活性和效率，但需要理解OpenGL运作细节和图形编程

### 扩展
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

### 状态机（State Machine）
* OpenGL是一个状态机
  * 以变量来描述OpenGL当前应该如何运行。
  * OpenGL的状态通常称为OpenGL上下文（context）。
  * 更改OpenGL状态的一般途径：设置选项、操作缓冲，最后使用当前OpenGL上下文来渲染。
  * 如设置当前OpenGL的状态（设置上下文变量），使其作线段或画三角形。
* OpenGL中的函数
  * 状态设置函数（State-changing Function）：改变上下文。
  * 状态使用函数（State-using Function）：根据当前OpenGL的状态执行一些操作。

### 对象
* OpenGL内核：C语言编写的库。
  * 支持多种语言的派生。
  * 但C的一些语言结构不容易被翻译到其它高级语言，因此引入了一些抽象层如“对象”。
* OpenGL中的对象
  * 指一些选项的集合，代表OpenGL状态的一个子集。
  * 如用一个对象代表绘图窗口的设置，则其内有一些成员，用来设置大小和支持的颜色位数等。
* OpenGL的数据类型
  * 其有自己的基本类型，改为语言自带类型可能不造成影响，但用OpenGL自身基本类型更安全。
  * 可以保证在各平台中每一种类型的大小统一。（当然也可以使用其它定宽类型(Fixed-width Type)来实现。）

## 3. Creating a window
### Intro: GLFW
* 一个专门针对OpenGL的C语言库。
  * 提供一些渲染物体所需的最低限度接口。
  * 允许用户创建OpenGL上下文，定义窗口参数以及处理用户的输入。
* 环境搭建 - 下载安装
  * 下载源代码包：https://www.glfw.org/download.html
  * 解压打开源代码包。
  * 下载安装Visual Studio：https://visualstudio.microsoft.com/zh-hans/
  * 下载安装CMake：https://cmake.org/download/
  * CMakeGUI：source code `~/glfw-3.15.3`，where to build `~/glfw-3.15.3/build`新建build作为目标文件夹
  * 用VS打开build下的GLFW.sln，生成解决方案。然后编译的库glfw3.lib出现在src/Debug。
  * 把GLFW默认的`~/include`和编译生成的`glfw3.lib`告知IDE或编译器。
    * 1.把`~/include`文件加到IDE/编译器的`/include`，把`glfw3.lib`加到`/lib`。
    * 2.建立新的包含所有第三方库文件头文件的目录，并在IDE/编译器中指定。
* 环境搭建 - 在Visual Studio中的配置
  * VS创建空项目（Visual C++）。
  * 链接：项目属性-VC++ 目录-把include和.lib路径加到include（包含）和lib（库）目录。【可通过`<GLFW/...>`引用头文件和库文件夹。】
  * 在Linker链接器-Input输入-Additional dependencies附加依赖项添加glfw3.lib。（使GLFW在编译时能被链接器链接）
  * Windows下：最后将opengl32.lib加入连接器设置。（Windows下包含在Microsoft SDK中，安装VS时默认安装）
### Intro: GLAD
* 完成“运行时查询本机显卡相应OpenGL驱动版本的函数地址，并保存在函数指针中供使用”的任务。
    ```cpp
    /* Windows 上手动完成的例子 */

    // 定义函数原型
    typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
    // 找到正确的函数并赋值给函数指针
    GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
    // 现在函数可以被正常调用了
    GLuint buffer;
    glGenBuffers(1, &buffer);
    ```
* GLAD配置步骤
  * GLAD在线生成地址：https://glad.dav1d.de/ 完成选项
    
    项目 | 选项 | 
    --- | --- |
    Language | C/C++
    Specification | OpenGL
    API(gl) | version >3.3
    Profile | Core
    Extensions | 暂时忽略

  * 生成的glad.zip中`include/KHR、glad`加入之前自设的include
  * `src/glad.c`加入项目的源文件（新建其它项目则重新添加）

    ````cpp
    /* 测试配置。 */
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <iostream>
    using namespace std;

    int main()
    {
        cout << "Hello, OpenGL" << endl;
        return 0;
    }
    ````
### Settings: Windows10 VS2019 GLFW GLAD 完全配置踩坑结果
#### 下载
* GLFW：https://www.glfw.org/download.html
  * 选 x64 版本，之后在 VS 的项目属性->配置管理器里把平台改成x64！
* GLAD：https://glad.dav1d.de/
  * API gl Version 3.3（对应 LearnOpenGL 在线教程所用OGL版本）
  * Profile Core
  * √ Gnerate a loader
  * 生成后下载.zip
#### 配置目录结构 `folder - oglsettings`
* `include`
  * glad、KHR (所下载的 glad->include 中内容)
  * GLFW (所下载的 glfw->include 中内容)
* `lib` (所下载的 glfw->lib-vc 对应vs版本中内容，本次配置用的vs2019)
  * glfw3.dll
  * glfw3.lib
  * glfw3dll.lib
* `src`
  * glad.c (所下载的 glad->src 中内容)
#### 项目配置
1. 把 `oglsettings` 放到项目根目录下
2. 项目属性中更改：
   * VC++ 目录：包含目录、库目录，分别添加 oglsettings 中 include 和 lib 路径
   * Linker 链接器->输入：附加依赖项，添加 opengl32.lib、glfw3.lib
3. 项目源文件中引入 glad.c
> `Error: 模块计算机类型“x64”与目标计算机类型“x86”冲突`  
> 解决方案：检查`项目属性->链接器->高级：目标计算机`应为x64，改完清理一下重新生成方案。

## 4. Hello Window
## 窗口创建
### **GLAD和GLFW头文件**
```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```
* `要在包含GLFW的头文件之前包含GLAD的头文件。`
* GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD。
### **main函数：实例化GLFW窗口**
* `glfwInit();	// 初始化GLFW`
* GLFW配置函数
  * `glfwWindowHint(<选项名称>（GLFW_*）, <选项值（整型）>)`
  * 选项和值的说明文档：https://www.glfw.org/docs/latest/window.html#window_hints
* 
* GLAD

## 5. Hello Triangle
## 6. Shaders
## 7. Textures
## 8. Transformations
## 9. Coordinate Systems
## 10. Camera
## 11. Review

# Part Ⅱ - Lighting

# Part Ⅲ - Model Loading

# Part Ⅳ - Advanced OpenGL

# Part Ⅴ - Advanced Lighting

# Part Ⅵ - PBR

# Part Ⅶ - In Practice

# Part Ⅷ - 2D Game

# To Be Continued...

<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->