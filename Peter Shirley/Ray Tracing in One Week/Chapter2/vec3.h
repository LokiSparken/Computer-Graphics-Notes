#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

class vec3
{
public:
    vec3() {}   // 默认构造函数
    vec3(float e0, float e1, float e2) { e[0]=e0,e[1]=e1,e[2]=e2; }
    // 向量坐标
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    // 颜色RGB值
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    // 重载单目运算符+、-
    inline const vec3 &operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0],-e[1],-e[2]); }

    // 重载方括号
    inline const float operator[](int i) const { return e[i]; }   // 常量对象使用下标访问内容
    inline float &operator[](int i) { return e[i]; }    // 非常量对象

    // 重载复合赋值运算符
    inline vec3 &operator+=(const vec3 &v2) 
    {
        e[0] += v2.e[0];
        e[1] += v2.e[1];
        e[2] += v2.e[2];
        return *this;
    }
    inline vec3 &operator-=(const vec3 &v2)
    {
        e[0] -= v2.e[0];
        e[1] -= v2.e[1];
        e[2] -= v2.e[2];
        return *this;
    }
    inline vec3 &operator*=(const vec3 &v2)
    {
        e[0] *= v2.e[0];
        e[1] *= v2.e[1];
        e[2] *= v2.e[2];
        return *this;
    }
    inline vec3 &operator/=(const vec3 &v2)
    {
        e[0] /= v2.e[0];
        e[1] /= v2.e[1];
        e[2] /= v2.e[2];
        return *this;
    }
    inline vec3 &operator*=(const float t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    inline vec3 &operator/=(const float t)
    {
        // 将三次除法转为一次除法和三次乘法
        float k = 1.0 / t;
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
        return *this;
    }

    // 常用向量相关函数
    inline float length() const { return sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]); } // 向量的模
    inline float squared_length() const { return e[0]*e[0]+e[1]*e[1]+e[2]*e[2]; } // 向量的模的平方
    inline void make_unit_vector()  // 向量单位化
    {
        float k = 1.0 / this->length();
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
    }

    float e[3];
};

// 重载输入输出
inline istream &operator>>(istream &is, vec3 &t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline ostream &operator<<(ostream &os, const vec3 &t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

// 重载双目运算符
inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(float t, const vec3 &v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, float t)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(const vec3 &v, float t)
{
    float k = 1.0 / t;
    return vec3(v.e[0] * k, v.e[1] * k, v.e[2] * k);
}

// 向量单位化（更便于调用的方式？）
inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

// 点积
inline float dot(const vec3 &v1, const vec3 &v2)
{
    return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

// 叉乘
/*
    矩阵形式的叉乘：
        x       y       z
     v1.e[0] v1.e[1] v1.e[2]
     v2.e[0] v2.e[1] v2.e[2]
    根据第一行的代数余子式表示形式求得结果
*/
inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
    return vec3(  (v1.e[1]*v2.e[2] - v2.e[1]*v1.e[2]),
                 -(v1.e[0]*v2.e[2] - v2.e[0]*v1.e[2]),
                  (v1.e[0]*v2.e[1] - v2.e[0]*v1.e[1]) );
}