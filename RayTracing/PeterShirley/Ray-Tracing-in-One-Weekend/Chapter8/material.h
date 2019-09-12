#ifndef MATERIAL
#define MATERIAL

#include "ray.h"
#include "hitable.h"

// 随机返回一个在单位球内的点坐标
vec3 random_in_unit_sphere()
{
    // 函数内假设球心在原点(0, 0, 0)即可，外面调用处加上球心坐标的偏移
    vec3 p;
    do
    {   // [0, 1]*2 => [0, 2] -1 = [-1, 1]
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0); // 点积>=1不在单位球内，继续生成
    return p;
}

/*
    求光滑表面的镜面反射向量。
    作图，易知：反射向量R = 入射向量I + 2*入射向量在法向上的投影S，求投影并由单位向量化简可得。
    结论：R = I - 2dot(I,N)N
*/
vec3 reflect(const vec3 &I, const vec3 &N)
{
    return I - 2*dot(I,N)*N;
}

/*
    材质类。
    1. 产生散射光线（或是吸收了多少入射光）
    2. 如果发生了散射，那么光线衰减了多少
*/
class material
{
public:
    /*
        散射函数。
        参数：入射光，命中时的量记录，衰减，散射后的光线
    */
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

/*
    Lambertian reflectance，不光滑表面材质的漫反射处理。
*/
class lambertian : public material
{
public:
    lambertian(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere(); // 散射方向随机
        scattered = ray(rec.p, target - rec.p); // 散射后的光线
        attenuation = albedo;   // 衰减，控制散射后光线强度
        return true; // 发生散射
    }

    vec3 albedo;    // 材质特性：吸收多少入射光
};

/*
    光滑表面材质，只反射光线。
*/
class metal : public material
{
public:
    metal(const vec3 &a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);    // 发生反射
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());  // 生成反射后光线，并加上一定的偏差值
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;  // 反射角的范围是[0, 90)即点积大于零
    }

    vec3 albedo;    // 材质特性：吸收多少入射光
    float fuzz;     // 给反射光施加微量偏移，限制在[0, 1]。0时无偏差。数值越大偏差越大，效果越模糊。
};

#endif