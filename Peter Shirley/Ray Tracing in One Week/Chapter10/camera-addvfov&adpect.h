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
    camera(float vfov, float aspect)
    {
        float theta = vfov*M_PI/180.0;  // 角度转弧度
        float half_height = tan(theta/2.0);     // 作图显然
        float half_width = aspect * half_height;    // 列式易得

        origin = vec3(0.0, 0.0, 0.0);
        
        lower_left_corner = vec3(-half_width, -half_height, -1.0);  // 水平，垂直，z坐标
        horizontal = vec3(2.0*half_width, 0.0, 0.0);    // 宽
        vertical = vec3(0.0, 2.0*half_height, 0.0);     // 高
    }
    
    // 光源+方向生成光射线
    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin); }

    vec3 origin;    // 观察者/相机位置
    vec3 lower_left_corner, horizontal, vertical;   // 观察的平面左下角位置坐标、水平垂直方向长度
};

#endif