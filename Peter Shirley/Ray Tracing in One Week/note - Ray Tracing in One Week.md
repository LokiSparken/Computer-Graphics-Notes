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

# Chapter 2: The vec3 class
* `class vec3`: 向量计算和颜色计算
* 复习一手cpp运算符重载
  * `operator[](int pos)`: 下标运算符重载，一般要针对常量对象和非常量对象写一个只读访问的`const T operator[](int pos) const`和一个返回引用的`T &operator[](int pos)`
  * `operator/=(float t)`: 将三次除法转为一次除法加三次乘法。惊了！好有道理，我怎么这么没有优化意识？
  * 感觉`make_unit_vector`和`unit_vector`都是向量单位化吧……就是调用方式不一样？
* 类定义最后`;`忘记加了，会疯狂影响后面定义的函数，瞎调半天QAQ
* ……做测试也太烦了叭=。=……orzzz


# Word Box
## Chapter 0: Overview
* staple adj. 主要的，基本的 n. 订书钉，基本食物 v. 用订书钉装订
* preach v. 宣讲，说教

## Chapter 1: Output an image

## Chapter 2: The vec3 class
* transparency n. 幻灯片，透明性，显而易见
* suffice v. 足以，足够
* 


<i class="fa fa-star"></i>
<!-- 使用FontAwesome -->
<head> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/all.js"></script> 
    <script defer src="https://use.fontawesome.com/releases/v5.0.13/js/v4-shims.js"></script> 
</head> 
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.0.13/css/all.css">

<!-- Sample use: <i class="fa fa-star"></i> -->