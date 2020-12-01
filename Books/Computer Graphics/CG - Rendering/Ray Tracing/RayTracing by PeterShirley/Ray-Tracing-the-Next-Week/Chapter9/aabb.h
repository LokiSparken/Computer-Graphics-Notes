#ifndef AABBH
#define AABBH

#include "hittable.h"
#include "ray.h"

inline float ffmin(float a, float b) { return a<b ? a : b; }
inline float ffmax(float a, float b) { return a>b ? a : b; }

class aabb
{
public:
    aabb() {}
    aabb(const vec3 & a, const vec3 &b) { _min = a; _max = b; }

    vec3 min() const { return _min; }
    vec3 max() const { return _max; }

    bool hit(const ray &r, float tmin, float tmax) const
    {
        for (int a = 0; a < 3; a++)
        {
            // 按公式求x、y、z三维空间中相应所得参数t的范围
            float t0 = ffmin((_min[a] - r.origin()[a]) / r.direction()[a], (_max[a] - r.origin()[a]) / r.direction()[a]);
            float t1 = ffmax((_min[a] - r.origin()[a]) / r.direction()[a], (_max[a] - r.origin()[a]) / r.direction()[a]);
            tmin = ffmax(t0, tmin);
            tmax = ffmin(t1, tmax);
            if (tmax <= tmin) return false;
        }
        return true;
    }

    void print()
    {
        cout << "([" << _min.x() << ", " << _min.y() << ", " << _min.z() << "], [" << _max.x() << ", " << _max.y() << ", " << _max.z() << "])\n";
    }

    vec3 _min, _max;    // AABB中确定的参数t范围[t0, t1]
};

// 传入两个包围盒，综合两者取最大范围
aabb surrounding_box(aabb box0, aabb box1)
{
    vec3 small
    ( 
        ffmin(box0.min().x(), box1.min().x()),
        ffmin(box0.min().y(), box1.min().y()),
        ffmin(box0.min().z(), box1.min().z())
    );

    vec3 big
    (
        ffmax(box0.max().x(), box1.max().x()),
        ffmax(box0.max().y(), box1.max().y()),
        ffmax(box0.max().z(), box1.max().z())
    );

    return aabb(small, big);
}

#endif