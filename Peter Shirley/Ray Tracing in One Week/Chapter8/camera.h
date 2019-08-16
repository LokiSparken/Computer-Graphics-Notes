#ifndef CAMERA
#define CAMERA

#include "ray.h"

class camera
{
public:
    camera()
    {
        origin = vec3(0.0, 0.0, 0.0);
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
    }
    
    // 光源+方向生成光射线
    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin); }

    vec3 origin;    // 观察者/相机位置
    vec3 lower_left_corner, horizontal, vertical;   // 观察的平面左下角位置坐标、水平垂直方向长度
};

#endif