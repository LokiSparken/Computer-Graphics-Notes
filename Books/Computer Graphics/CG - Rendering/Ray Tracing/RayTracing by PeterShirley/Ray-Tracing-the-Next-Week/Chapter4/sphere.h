#ifndef SPHEREH
#define SPHEREH

#include "hittable.h"

/* 球体类，继承抽象的命中类hittable，必须实现接受光线命中的函数接口。 */
class sphere: public hittable
{
public:
    sphere() {}
    sphere(vec3 cen, float r, material *m): center(cen), radius(r), mat_ptr(m) {};
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;

    vec3 center;    // 球心位置坐标
    float radius;   // 球体半径
    material *mat_ptr;  // 球的材质
};

/* 【功能】生成球体对象的包围盒。 */
bool sphere::bounding_box(float t0, float t1, aabb &box) const
{
    // 球形包围盒的两边界：以圆心为中心，+-半径进行扩展
    box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
    return true;
}

/* 【功能】判断球与光线交点情况。参数值t、交点位置坐标、交点法向存入rec。 */
bool sphere::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    vec3 oc = r.origin() - center;  // A-C
    float a = dot(r.direction(), r.direction());
    float b = dot(r.direction(), oc);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - a*c;   // 二次方程delta
    /* 上式把b设的2提出，加上平方再开根的，和公式里分母2a的2约掉简化计算量。 */

    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;    // 求根，不知道为啥不用上面求好的delta，减少误差吗？
        if (tmin < temp && temp < tmax) // 较小根就符合参数范围
        {
            rec.t = temp;                           // 记录所求参数值t
            rec.p = r.point_at_parameter(rec.t);    // 由点在光线上求得交点位置坐标
            rec.normal = (rec.p - center) / radius; // 法向即交点减球心所得向量，除以长度即球半径
            rec.mat_ptr = mat_ptr;  // 记录命中物体材质
            return true;
        }
        // 若较小根不符合，则考虑较大根，同理记录数据
        temp = (-b + sqrt(discriminant)) / a;
        if (tmin < temp && temp < tmax)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);    // 由点在光线上求得交点位置坐标
            rec.normal = (rec.p - center) / radius; // 法向即交点减球心所得向量，除以长度即球半径
            rec.mat_ptr = mat_ptr;  // 记录命中物体材质
            return true;
        }
    }
    return false;
}

#endif