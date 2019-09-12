#ifndef HITABLE
#define HITABLE

#include "ray.h"

class material;  // 声明有一个material类

// 光线命中物体时获取的信息
struct hit_record
{
    float t;        // （对球？）所求得参数，距离t
    vec3 p;         // 命中（相交）位置
    vec3 normal;    // 命中位置的法向

    material *mat_ptr;  // 命中物体的材质
};

class hitable
{
public:
    // 接受光线的命中、参数有效范围、命中时获取的信息
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const = 0;
    // =0纯虚函数，继承类必须实现同名函数。
    // const常量成员函数，不允许修改类的数据成员
};

#endif