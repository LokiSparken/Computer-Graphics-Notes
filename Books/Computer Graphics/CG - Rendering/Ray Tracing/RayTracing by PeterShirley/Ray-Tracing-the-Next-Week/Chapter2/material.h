#ifndef MATERIAL
#define MATERIAL

#include "ray.h"
#include "hittable.h"

/*
    求反射系数。
    Schlick's approximation公式。
    参数：cos(入射角)，折射介质的折射系数。
*/
float schlick(float cosine, float ref_idx)
{
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine), 5);
}

/*
    求折射向量。
    参数: 入射光线I，单位法向N（命中时外部传入的法向就是单位的），
         相对折射率n'/n的倒数n/n'（因为讲道理推导的时候用的都是那个相对折射率的倒数来着），要返回的所求折射向量。
    emmmm...下面的计算主要就是公式推出来的，详见note: Chapter 9求折射向量。
*/
bool refract(const vec3 &I, const vec3 &N, float NI_over_NT, vec3 &refracted)
{
    vec3 UI = unit_vector(I); // 入射光线的单位向量
    float dt = dot(UI, N);
    float discriminant = 1.0 - NI_over_NT*NI_over_NT*(1.0-dt*dt);
    if(discriminant > 0)
    {
        refracted = NI_over_NT*(UI - N*dt) - N*sqrt(discriminant);
        return true;
    }
    else
        return false;
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

// 随机返回一个在单位球内的点坐标
vec3 random_in_unit_sphere()
{
    // 函数内假设球心在原点(0, 0, 0)即可，外面调用处加上球心坐标的偏移
    vec3 p;
    do
    {   // [0, 1]*2 => [0, 2] -1 = [-1, 1]
        p = 2.0*vec3(random_double(), random_double(), random_double()) - vec3(1, 1, 1);
    } while (dot(p,p) >= 1.0); // 点积>=1不在单位球内，继续生成
    return p;
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
    /* 【Debug】 */
    virtual int print_material() const = 0;
};

/*
    Lambertian reflectance，不光滑表面材质的漫反射处理。（哑光、磨砂）
*/
class lambertian : public material
{
public:
    lambertian(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere(); // 散射方向随机
        scattered = ray(rec.p, target - rec.p, r_in.time()); // 散射后的, r_in.time()光线
        attenuation = albedo;   // 衰减，控制散射后光线强度
        return true; // 发生散射
    }
    virtual int print_material() const
    {
        return 111;
    }

    vec3 albedo;    // 材质特性：吸收多少入射光
};

/*
    光滑表面材质，只镜面反射光线。（金属）
*/
class metal : public material
{
public:
    metal(const vec3 &a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);    // 发生反射
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere(), r_in.time());  // 生成反射后光线，并加上一定的偏, r_in.time()差值
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;  // 反射角的范围是[0, 90)即点积大于零
    }
    virtual int print_material() const
    {
        return 222;
    }

    vec3 albedo;    // 材质特性：吸收多少入射光
    float fuzz;     // 给反射光施加微量偏移，限制在[0, 1]。0时无偏差。数值越大偏差越大，效果越模糊。
};

/*
    一些透明材质（不知道为啥叫它电解质）如玻璃等，有折射现象。
*/
class dielectric : public material
{
public:
    dielectric(float ri) : ref_idx(ri) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal); // 一部分发生反射，这一步下面先考虑全为折射的情况
        float NI_over_NT;
        attenuation = vec3(1.0, 1.0, 1.0);  // 这种材质的衰减attenuation总是1，不吸收光。
        vec3 refracted;
        float reflect_prob, cosine; // 反射系数和cos(入射角)
        /* 考虑入射角的大小。 */
        if (dot(r_in.direction(), rec.normal) > 0)  // 入射角大于90度，光线从电解质射入空气了，？讲道理这情况怎么产生的
        {
            outward_normal = -rec.normal;   // 所以法向为外部法向的反向量
            NI_over_NT = ref_idx;           // 光线从电解质射入空气
            // cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();   // 喵喵喵？
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();    // cos(入)
            cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));   // 折射系数+平方关系求cos(入')
        }
        else    // 入射角小于等于90度的正常的情况
        {
            outward_normal = rec.normal;    // 外部法向即法向
            NI_over_NT = 1.0 / ref_idx;     // 光线从空气射入电解质
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();    // 正常情况入射角即-UI*N
        }
        /* 发生部分折射时，求反射系数。 */
        if (refract(r_in.direction(), outward_normal, NI_over_NT, refracted))   // 发生折射现象
        {
            reflect_prob = schlick(cosine, ref_idx);
        }
        else    // 全反射现象，反射系数为1。
        {
            scattered = ray(rec.p, reflected, r_in.time());
            reflect_prob = 1.0;
        }

        // 随机数小于反射系数设为反射光线，否则设为折射光线
        if (random_double() < reflect_prob)
        {
            scattered = ray(rec.p, reflected, r_in.time());
        }
        else
        {
            scattered = ray(rec.p, refracted, r_in.time());
        }
        
        return true;
    }
    virtual int print_material() const
    {
        return 333;
    }

    float ref_idx;  // 材质特性：折射率
};

#endif