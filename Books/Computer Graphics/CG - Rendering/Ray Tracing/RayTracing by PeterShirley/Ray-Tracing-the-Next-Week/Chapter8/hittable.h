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

bool translate::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
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

class rotate_y : public hittable
{
public:
    rotate_y(hittable *p, float angle);
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const
    {
        box = bbox;
        return hasbox;
    }

    hittable *ptr;
    float sin_theta, cos_theta;
    bool hasbox;
    aabb bbox;
};

// 绕Y轴旋转，传入原物体和要旋转的角度
rotate_y::rotate_y(hittable *p, float angle) : ptr(p)
{
    float radians = (M_PI / 180.0) * angle;     // 转弧度
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);     // 获取原物体是否有包围盒（不存在没包围盒的？）

    // 更新包围盒大小
    vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
    vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
            {
                // 枚举包围盒xyz上各取最大最小值的八种情况
                float x = i*bbox.max().x() + (1-i)*bbox.min().x();
                float y = j*bbox.max().y() + (1-j)*bbox.min().y();
                float z = k*bbox.max().z() + (1-k)*bbox.min().z();

                // 由推的公式得新的xz坐标
                float newx = cos_theta*x + sin_theta*z;
                float newz = -sin_theta*x + cos_theta*z;

                // 检查并更新包围盒每一维的范围
                vec3 checker(newx, y, newz);
                for (int c = 0; c < 3; ++c)
                {
                    if (checker[c] > max[c]) max[c] = checker[c];
                    if (checker[c] < min[c]) min[c] = checker[c];
                }
            }
    bbox = aabb(min, max);  // 更新包围盒
}

bool rotate_y::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    // 把追踪的光线发射点和方向都绕Y轴作逆变换，即旋转-theta
    vec3 origin = r.origin(), direction = r.direction();
    origin[0] = cos_theta*r.origin()[0] - sin_theta*r.origin()[2];
    origin[2] = sin_theta*r.origin()[0] + cos_theta*r.origin()[2];
    direction[0] = cos_theta*r.direction()[0] - sin_theta*r.direction()[2];
    direction[2] = sin_theta*r.direction()[0] + cos_theta*r.direction()[2];
    ray rotated_r(origin, direction, r.time());
    
    if (ptr->hit(rotated_r, tmin, tmax, rec))
    {
        // 所得命中点坐标和法线再绕Y轴旋转theta
        vec3 p = rec.p, normal = rec.normal;
        p[0] = cos_theta*rec.p[0] + sin_theta*rec.p[2];
        p[2] = -sin_theta*rec.p[0] + cos_theta*rec.p[2];
        normal[0] = cos_theta*rec.normal[0] + sin_theta*rec.normal[2];
        normal[2] = -sin_theta*rec.normal[0] + cos_theta*rec.normal[2];
        rec.p = p, rec.normal = normal;
        return true;
    }
    return false;
}

#endif