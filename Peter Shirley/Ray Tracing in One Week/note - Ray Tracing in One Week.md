> # Peter Shirley - Ray Tracing in One Week
# Chapter 0: Overview

# Chapter 1: Output an image 
* .ppm格式：P3 nx*ny 各像素点的RGB
  * 可以直接看颜色效果欸好神奇ovo
* cpp文件输出
```c++
#include <fstream>

int main()
{
    ofstream output;    // 创建ofstream对象
    output.open("filename.ext");    // 关联文本文件

    output << "output some extents to the file.\n" ; // 输出到文件

    output.close(); // 最后关闭文件
}
```
## 小结
    大概就是输出到ppm看下预览吧，输出的图挺好看的，根据比例显示颜色的样子=。=

# Chapter 2: The vec3 class
* `class vec3`: 向量计算和颜色计算
* 复习一手cpp运算符重载
  * `operator[](int pos)`: 下标运算符重载，一般要针对常量对象和非常量对象写一个只读访问的`const T operator[](int pos) const`和一个返回引用的`T &operator[](int pos)`
  * `operator/=(float t)`: 将三次除法转为一次除法加三次乘法。惊了！好有道理，我怎么这么没有优化意识？
  * 感觉`make_unit_vector`和`unit_vector`都是向量单位化吧……就是调用方式不一样？
* 类定义最后`;`忘记加了，会疯狂影响后面定义的函数，瞎调半天QAQ
* ……做测试也太烦了叭=。=……orzzz
## 小结
首先`建立了存储三维空间中向量、点的类vec3`，并且同时也可以用来表示颜色的RGB三色值。对其进行一些基本运算的定义，重载相应的运算符。
主要是加减乘除等。之后是一些向量常用的基本量如模长、对应方向上的单位向量等的获取。最后是点积和叉乘。`叉乘`用矩阵的形式，根据第一行的
代数余子式展开求得新向量。

# Chapter 3: Rays, a simple camera, and background
* 头皮发麻，感觉写的注释比代码多……直接看小结叭QAQ
## 小结
* 根据空间直线的参数方程形式建立`射线类ray`。
* 显示平面的表示方法：平面一角+横纵偏移
* 设定相机/观察者位置到原点(0, 0, 0)
* 生成射线：确定光源、方向向量
* 打印像素点时假装观察者在往这个像素点看，设定需要什么颜色，打出RGB
* 用线性插值把色值范围相应缩放投影到要显示的平面区间
* 线性插值：`blended_value = (1-t)*s + t*e, t∈[0,1]`（我还是更喜欢`s + (e-s)*t`）

# Chapter 4: Adding a sphere

# Word Box
## Chapter 0: Overview
* staple adj. 主要的，基本的 n. 订书钉，基本食物 v. 用订书钉装订
* preach v. 宣讲，说教

## Chapter 1: Output an image

## Chapter 2: The vec3 class
* transparency n. 幻灯片，透明性，显而易见
* suffice v. 足以，足够

## Chapter 3: Rays, a simple camera, and background
* computation n. 计算
* intersect v. 相交，贯穿
* gradient n. 斜率，变化率
* convection n. 对流
* traverse v. 穿过 n. 横越，可横越的地方
* exactness n. 精确，正确
* antialiasing 抗锯齿处理，边缘柔化
* blend v. 混合 n. 混合物
* linear blend/interpolation = lerp 线性插值
* ray n. 射线，少量 v. 照射，发光

## Chapter 4: Adding a sphere
* 


<i class="fa fa-star"></i>
<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->