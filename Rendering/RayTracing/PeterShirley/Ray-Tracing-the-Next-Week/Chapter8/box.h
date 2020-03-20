#ifndef BOXH
#define BOXH

#include "rectangle.h"
#include "hittable_list.h"

class box : public hittable
{
public:
    box() {}
    box(const vec3 &p0, const vec3 &p1, material *ptr);
    virtual bool hit(const ray &r, float t0, float t1, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const
    {
        box = aabb(pmin, pmax);
        return true;
    }

    vec3 pmin, pmax;
    hittable *list_ptr;
};

box::box(const vec3 &p0, const vec3 &p1, material *ptr)
{
    pmin = p0, pmax = p1;
    hittable **list = new hittable *[6];

    // 根据一对对顶点坐标生成六个矩形面围成一个长方体
    list[0] = new xy_rect(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr);
    list[1] = new flip_normal(new xy_rect(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    list[2] = new xz_rect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr);
    list[3] = new flip_normal(new xz_rect(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    list[4] = new yz_rect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr);
    list[5] = new flip_normal(new yz_rect(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));

    list_ptr = new hittable_list(list, 6);
}

bool box::hit(const ray &r, float t0, float t1, hit_record &rec) const
{
    return list_ptr->hit(r, t0, t1, rec);
}

#endif