#ifndef HITTABLEH
#define HITTABLEH

#include "aabb.h"
#include "const.h"

class material;  // 声明有一个material类

// 光线命中物体时获取的信息
struct hit_record
{
    float u, v;     // 纹理坐标的uv映射
    float t;        // （对球？）所求得参数，距离t
    vec3 p;         // 命中（相交）位置
    vec3 normal;    // 命中位置的法向

    material *mat_ptr;  // 命中物体的材质
};

void get_sphere_uv(const vec3 &p, float &u, float &v)
{
    // 草，公式推出来明明是这个亚子的为什么结果变得很奇怪！
        // 可能是因为，平面贴图是“躺着”的，现在要给它“站起来”，所以要变换一下坐标系
        // 坐标轴换来换去，只有yz互换是比较正常但与贴图呈镜面的
        // 而贴图坐标比例范围[0,1]，所以作者用1去-一下，得到与贴图吻合的表现？……
        // 草，我快看不下去了
    // float phi = atan2(p.z(), p.x());
    // float theta = asin(p.y());
    // u = (phi + M_PI) / (2*M_PI);
    // 作者到底挖了多少大坑不说（
    float phi = atan2(p.z(), p.x());
    float theta = asin(p.y());
    u = 1 - (phi + M_PI) / (2*M_PI);
    v = (theta + M_PI/2) / M_PI;
}

class hittable
{
public:
    // 接受光线的命中、参数有效范围、命中时获取的信息
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const = 0;
    // AABB包围盒派生类所需
    virtual bool bounding_box(float t0, float t1, aabb &box) const = 0;
    // =0纯虚函数，继承类必须实现同名函数。
    // const常量成员函数，不允许修改类的数据成员
};

class flip_normal : public hittable
{
public:
    flip_normal(hittable *p) : ptr(p) {}
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const
    {
        if (ptr->hit(r, tmin, tmax, rec))
        {
            rec.normal = -rec.normal;
            return true;
        }
        else
        {
            return false;
        }
    }
    virtual bool bounding_box(float t0, float t1, aabb &box) const
    {
        return ptr->bounding_box(t0, t1, box);
    }
    
    hittable *ptr;
};

class translate : public hittable
{
public:
    translate(hittable *p, const vec3 &displacement) : ptr(p), offset(displacement) {}
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;

    hittable *ptr;
    vec3 offset;
};

bool translate::hit(const ray &r, float tmin, tmax, hit_record &rec) const
{
    ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (ptr->hit(moved_r, tmin, tmax, rec))
    {
        rec.p += offset;
        return true;
    }
    return false;
}

bool translate::bounding_box(float t0, float t1, aabb &box) const
{
    if (ptr->bounding_box(t0, t1, box))
    {
        box = aabb(box.min() + offset, box.max() + offset);
        return true;
    }
    return false;
}

#endif