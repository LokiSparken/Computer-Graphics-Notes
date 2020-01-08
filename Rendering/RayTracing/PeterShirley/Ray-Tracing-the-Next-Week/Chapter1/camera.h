#ifndef CAMERA
#define CAMERA

#include <cmath>
#include "ray.h"
#include "const.h"

/*
    在透镜（光圈）上随机一点作光源。
    这里在z=0平面上随机单位圆上点，因为通常vup设(0, 1, 0)，当然这里在外部调用构造传入的参数也是这个。
    所以此时透镜平面就是z=0即x,y轴构成的平面。
*/
vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = 2.0*vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}

class camera
{
public:
    /*
        构造相机/观察者。
        参数：<相机/观察者位置>、<看向的点>、<头顶朝向>
             控制视野的<张角>、<画面宽高比>
             景深效果<光圈大小>、<成像距离>
    */
    camera( vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
    {
        lens_radius = aperture / 2.0;   // 光圈半径为总大小的一半

        float theta = vfov*M_PI/180.0;  // 角度转弧度
        float half_height = tan(theta/2.0);     // 作图显然
        float half_width = aspect * half_height;    // 列式易得

        /* 构造相机/观察者坐标系。 */
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        
        lower_left_corner = origin - half_width*u*focus_dist - half_height*v*focus_dist - w * focus_dist;  // 观察者坐标+看向的位置+偏移到左下角
        horizontal = 2.0*half_width*u*focus_dist;  // 宽度×宽的方向
        vertical = 2.0*half_height*v*focus_dist;   // 高度×高的方向
    }
    
    /* 生成光射线。 */
    ray get_ray(float s, float t) 
    {
        vec3 rd = lens_radius * random_in_unit_disk();    // 从以原点为中心的透镜（光圈）上随机出一点
        /*
            rd为在x,y,z(y向上)坐标系中，透镜在z=0平面时，透镜上随机出的一点。
            改点坐标映射到在u,v,w坐标系中的坐标即(u*rd.x, v*rd.y, w*rd.z)，此处z=0所以只作前两个。
        */
        vec3 offset = u*rd.x() + v*rd.y();
        /*
            因此光源：相机/观察者位置即透镜中心+透镜上随机出的点的偏移。
            方向：看向的点 - 光源，所得向量。
        */
        return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
    }

    vec3 origin, u, v, w;    // 观察者/相机位置，及构造出的坐标系
    vec3 lower_left_corner, horizontal, vertical;   // 观察的平面左下角位置坐标、宽、高
    float lens_radius;  // 透镜半径
};

#endif