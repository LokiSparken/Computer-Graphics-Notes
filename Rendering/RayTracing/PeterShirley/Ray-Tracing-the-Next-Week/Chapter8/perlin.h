#ifndef PERLINH
#define PERLINH

#include "mymath.h"

// 用线性插值将纹理平滑化
inline float trilinear_interp(float c[2][2][2], float u, float v, float w)
{
    float accum = 0;
    for ( int i = 0; i < 2; ++i)
        for ( int j = 0; j < 2; ++j)
            for ( int k = 0; k < 2; ++k)
                accum += (i*u + (1-i)*(1-u)) * 
                         (j*v + (1-j)*(1-v)) * 
                         (k*w + (1-k)*(1-w)) * c[i][j][k];
    return accum;
}

// 5. turn ranfloat to ranvec
inline float perlin_interp(vec3 c[2][2][2], float u, float v, float w)
{
    // 把noise中对uvw的三次多项式化放到这里了
    float uu = u*u*(3-2*u), vv = v*v*(3-2*v), ww = w*w*(3-2*w);
    float accum = 0;
    for ( int i = 0; i < 2; ++i)
        for ( int j = 0; j < 2; ++j)
            for ( int k = 0; k < 2; ++k)
            {
                vec3 weight_v(u-i, v-j, w-k);
                accum += (i*uu + (1-i)*(1-uu)) * 
                         (j*vv + (1-j)*(1-vv)) * 
                         (k*ww + (1-k)*(1-ww)) * dot(c[i][j][k], weight_v);
            }
    return accum;
}

class perlin
{
public:
    float noise(const vec3 &p) const
    {
        float u = p.x() - floor(p.x()), v = p.y() - floor(p.y()), w = p.z() - floor(p.z());

        // 3. add hermite cubic
        // u = u*u*(3-2*u);
        // v = v*v*(3-2*v);
        // w = w*w*(3-2*w);

        // 2. add smooth
        int i = floor(p.x()), j = floor(p.y()), k = floor(p.z());

        // int i = int(4*p.x()) & 255, j = int(4*p.y()) & 255, k = int(4*p.z()) & 255;

        // 2. add smooth (trilinear_interp)
        vec3 c[2][2][2];    // 5. to ranvec
        for ( int di = 0; di < 2; ++di)
            for ( int dj = 0; dj < 2; ++dj)
                for ( int dk = 0; dk < 2; ++dk)
                    // c[di][dj][dk] = ranfloat[perm_x[(i+di) & 255] ^ perm_y[(j+dj) & 255] ^ perm_z[(k+dk) & 255]];
                    // 5. turn ranfloat to ranvec
                    c[di][dj][dk] = ranvec[perm_x[(i+di) & 255] ^ perm_y[(j+dj) & 255] ^ perm_z[(k+dk) & 255]];

        // return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]]; // 1. add perlin
        // return trilinear_interp(c, u, v, w);    // 2. add smooth
        return perlin_interp(c, u, v, w);     // 5. to ranvec
    }

    // 6. add turb
    float turb(const vec3 &p, int depth = 7) const
    {
        float accum = 0, weight = 1.0; 
        vec3 temp_p = p;
        for ( int i = 0; i < depth; ++i)
        {
            accum += weight*noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }
        return fabs(accum);
    }

    static float *ranfloat;
    static vec3 *ranvec;    // 5. turn ranfloat to ranvec
    static int *perm_x, *perm_y, *perm_z;
};

// 生成256个随机值，值域[0, 1]
// static float *perlin_generate()
// {
//     float *p = new float[256];
//     for ( int i = 0; i < 256; ++i )
//         p[i] = drand48();
//     return p;
// }

// 5. turn ranfloat to ranvec: 生成256个随机单位vector
static vec3 *perlin_generate()
{
    vec3 *p = new vec3[256];
    for ( int i = 0; i < 256; ++i)
        p[i] = unit_vector(vec3(-1 + 2*drand48(), -1 + 2*drand48(), -1 + 2*drand48()));
    return p;
}

// 打乱函数
void permute(int *p, int n)
{
    for ( int i = n-1; i > 0; --i)
    {
        int target = int(drand48()*(i+1));  // 从后往前，每次随机与前面的元素交换
        int temp = p[i];
        p[i] = p[target];
        p[target] = temp;
    }
    return ;
}

// 生成0-255并通过permute()函数打乱
static int *perlin_generate_perm()
{
    int *p = new int[256];
    for ( int i = 0; i < 256; ++i)
        p[i] = i;
    permute(p, 256);
    return p;
}

// float *perlin::ranfloat = perlin_generate();
vec3 *perlin::ranvec = perlin_generate();   // 5. turn ranfloat to ranvec
int *perlin::perm_x = perlin_generate_perm();
int *perlin::perm_y = perlin_generate_perm();
int *perlin::perm_z = perlin_generate_perm();

#endif
