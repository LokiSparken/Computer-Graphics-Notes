#ifndef CAMERA
#define CAMERA

#include <cmath>
#include "ray.h"

class camera
{
public:
    /*
        构造相机/观察者。
        参数：张角vfov（观察者位置origin分别到视野的上边界和下边界所得两向量夹角），
             画面宽高比aspect。
    */
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect)
    {
        vec3 u, v, w;
        float theta = vfov*M_PI/180.0;  // 角度转弧度
        float half_height = tan(theta/2.0);     // 作图显然
        float half_width = aspect * half_height;    // 列式易得

        /* 构造相机/观察者坐标系。 */
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        
        lower_left_corner = origin - half_width*u - half_height*v - w;  // 观察者坐标+看向的位置+偏移到左下角
        horizontal = 2.0*half_width*u;  // 宽度×宽的方向
        vertical = 2.0*half_height*v;   // 高度×高的方向
    }
    
    // 光源+方向生成光射线
    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin); }

    vec3 origin;    // 观察者/相机位置
    vec3 lower_left_corner, horizontal, vertical;   // 观察的平面左下角位置坐标、宽、高
};

#endif