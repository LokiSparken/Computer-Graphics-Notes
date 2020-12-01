#ifndef RECTANGLEH
#define RECTANGLEH

#include "hittable.h"

/* xy平面上，x范围[x0,x1]，y范围[y0,y1]，z=k的一个平面矩形。 */
class xy_rect : public hittable
{
public:
    xy_rect() {}
    xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *mat) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};
    virtual bool hit(const ray &r, float t0, float t1, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const
    {
        box = aabb(vec3(x0, y0, k-0.0001), vec3(x1, y1, k+0.0001));
        return true;
    }

    material *mp;
    float x0, x1, y0, y1, k;
};

// 求光线与该平面矩形是否相交
bool xy_rect::hit(const ray &r, float t0, float t1, hit_record &rec) const
{
    float t = (k-r.origin().z()) / r.direction().z();
    if (t<t0 || t>t1) return false; // 检验参数值是否合理
    float x = r.origin().x() + t*r.direction().x();
    float y = r.origin().y() + t*r.direction().y();
    if (x<x0 || x>x1 || y<y0 || y>y1) return false; // 参数t代入解得x,y并检验是否在矩形坐标范围内
    // 在范围内说明相交
    rec.u = (x-x0)/(x1-x0);
    rec.v = (y-y0)/(y1-y0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0, 0, 1);
    return true;
}

/* 同理有yz和xz平面。 */
class xz_rect : public hittable
{
public:
    xz_rect() {}
    xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {};
    virtual bool hit(const ray &r, float t0, float t1, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const
    {
        box = aabb(vec3(x0, k-0.0001, z0), vec3(x1, k+0.0001, z1));
        return true;
    }

    material *mp;
    float x0, x1, z0, z1, k;
};

bool xz_rect::hit(const ray &r, float t0, float t1, hit_record &rec) const
{
    float t = (k-r.origin().y()) / r.direction().y();
    if (t<t0 || t>t1) return false; // 检验参数值是否合理
    float x = r.origin().x() + t*r.direction().x();
    float z = r.origin().z() + t*r.direction().z();
    if (x<x0 || x>x1 || z<z0 || z>z1) return false; // 参数t代入解得x,z并检验是否在矩形坐标范围内
    // 在范围内说明相交
    rec.u = (x-x0)/(x1-x0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0, 1, 0);
    return true;
}

class yz_rect : public hittable
{
public:
    yz_rect() {}
    yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {};
    virtual bool hit(const ray &r, float t0, float t1, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const
    {
        box = aabb(vec3(k-0.0001, y0, z0), vec3(k+0.0001, y1, z1));
        return true;
    }

    material *mp;
    float y0, y1, z0, z1, k;
};

bool yz_rect::hit(const ray &r, float t0, float t1, hit_record &rec) const
{
    float t = (k-r.origin().x()) / r.direction().x();
    if (t<t0 || t>t1) return false; // 检验参数值是否合理
    float y = r.origin().y() + t*r.direction().y();
    float z = r.origin().z() + t*r.direction().z();
    if (y<y0 || y>y1 || z<z0 || z>z1) return false; // 参数t代入解得y,z并检验是否在矩形坐标范围内
    // 在范围内说明相交
    rec.u = (y-y0)/(y1-y0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(1, 0, 0);
    return true;
}

#endif