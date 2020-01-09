#ifndef RAY
#define RAY

#include "mymath.h"

class ray
{
public:
    ray() {}
    ray(const vec3 &a, const vec3 &b, float ti = 0.0) { A = a; B = b; time = ti;}
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(float t) const { return A + t*B; }

    vec3 A, B;  // p(t) = A + B*t;
    /*
        感觉应该是根据三维空间直线的参数方程得到的：
        (x-x0)/a = (y-y0)/b = (z-z0)/c = t  参数方程原始形式
        分母分别乘到t，再移项得到三个方程：
        x = at + x0
        y = bt + y0
        z = ct + z0
        其中令 (x0, y0, z0) = A即ray类中光源位置。
        又令 (a, b, c) = B即射线方向向量。
    */
   float time;
};

#endif