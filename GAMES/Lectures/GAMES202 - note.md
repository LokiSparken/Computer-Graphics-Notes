> # [GAMES202 Real-Time High Quality Rendering](https://www.bilibili.com/video/BV1YK4y1T7yY)
> * 男神终于又开课辣！！！

<!-- TOC -->

* [Lecture 1 - Introduction and Overview](#lecture-1---introduction-and-overview)
* [Lecture 2 - Recap of CG Basics](#lecture-2---recap-of-cg-basics)
  * [一、流水线回顾](#一流水线回顾)
  * [二、OpenGL](#二opengl)
  * [三、OpenGL Shading Language（GLSL）](#三opengl-shading-languageglsl)
    * [**`Debug`**](#debug)
  * [四、The Rendering Equation](#四the-rendering-equation)
  * [五、Calculus（In Lecture 3）](#五calculusin-lecture-3)
* [Lecture 3 - Shadow Mapping](#lecture-3---shadow-mapping)
  * [Basic technique](#basic-technique)
  * [Variance shadow maps（VSM）](#variance-shadow-mapsvsm)
  * [Moment shadow maps（MSM）](#moment-shadow-mapsmsm)

<!-- /TOC -->

# Lecture 1 - Introduction and Overview
* About Lecture Name
  * Real-Time：Speed > 30FPS（VR/AR > 90FPS）
  * High Quality：时间和质量的 trade off、（至少近似）物理正确
* Lecture Content
  * 阴影和环境光
  * GI
  * PBS
  * 实时光追

# Lecture 2 - Recap of CG Basics
## 一、流水线回顾
* Basic GPU hardware pipeline
* 纹理坐标的 UV 是如何参数化出来的：参数化问题，详见 GAMES102 几何处理

## 二、OpenGL
* OpenGL 渲染流程、相关主要概念及 API 举例
  * VBO
  * 在一个 framebuffer 绘制多个纹理（Multiple Render Target）
  * Vertex Shader：处理顶点属性
  * Fragment Shader：光照与着色计算，`深度测试`（OpenGL 内置/自定义）
  * V/F Shader 的交互：V 将 F 需要的顶点属性输出，由 OpenGL 插值后从 F 输入并使用
  * 一个 pass：一个场景渲染一次
  * Multiple passes：暂存到纹理
* 把 framebuffer 直接渲染到屏幕的问题：上一帧未渲染完（显示器刷新率问题），下一帧开始渲染，由于直接渲到屏幕，会导致撕裂。解决方案：
  * 垂直同步：锁帧，使显示器刷新率和显卡输出帧率匹配
  * 双重缓冲：暂存到某纹理，渲染完毕后交给屏幕。
  * 三重缓冲：双重缓冲在屏幕未刷新，暂存的纹理缓冲也渲染结束时需要等待纹理缓冲被腾出。再加一重更流畅。但显存占用大。（尤其在打开需四倍空间的 AA 处理后）

## 三、OpenGL Shading Language（GLSL）
* Shading Language 历史小姿势
* Shader 使用流程：写 shader 源码、创建 shader、编译、链接到 program
* Vertex Shader 命名：
  * attribute 顶点属性变量，前缀 `a`
  * uniform 全局变量，前缀 `u`
  * varying 待插值量，前缀 `v` （highp 计算精度相关）
### **`Debug`**
* Shader Debug 历史小姿势
* 新 Debug 工具
  * Nsight Graphics（cross platform，NVIDIA GPUs only）
  * RenderDoc（cross platform）（弹幕：可以调试 WebGL，需要从 RenderDoc 启动 Chrome）
* 男神 Debug 小技巧
  * 把值作为颜色输出，使用 color picker 色值提取工具（如 Mac - Digital Color Meter）看值（直播弹幕：RGB 调试法）

## 四、The Rendering Equation
* 实时渲染中对渲染方程的理解
    
    ![](note%20-%20image/GAMES202/1.png)
  * 考虑 visibility
    * 对环境光的理解更直观
    * `考虑某方向的入射光，在当前 shading point 是否可见`
  * 通常 BRDF 与 cosine-weighted BRDF 不作区分
* 实时渲染关注的问题：如何多 one-bounce 间接光照

## 五、Calculus（In Lecture 3）


# Lecture 3 - Shadow Mapping
## Basic technique

## Variance shadow maps（VSM）

## Moment shadow maps（MSM）
