#ifndef TEXTUREH
#define TEXTUREH

#include "mymath.h"

class texture
{
public:
    virtual vec3 value(float u, float v, const vec3 &p) const = 0;
};

// 将固定颜色用纹理形式表示
class constant_texture : public texture
{
public:
    constant_texture() {}
    constant_texture(vec3 c) : color(c) {}

    virtual vec3 value(float u, float v, const vec3 &p) const
    {
        return color;
    }

    vec3 color;
};

class checker_texture : public texture
{
public:
    checker_texture() {}
    checker_texture(texture *t0, texture *t1): even(t0), odd(t1) {}

    virtual vec3 value(float u, float v, const vec3 &p) const
    {
        float sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
        // float sines = cos(10*p.x())*cos(10*p.y())*cos(10*p.z());
        // float sines = sin(p.x())*sin(p.y())*sin(p.z());
        if (sines < 0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }

    texture *odd, *even;    // 两种固定颜色纹理
};

#endif