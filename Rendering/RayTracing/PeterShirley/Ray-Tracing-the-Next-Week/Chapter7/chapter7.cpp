#include <fstream>
#include <cfloat>
#include "box.h"
#include "bvh.h"
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "moving_sphere.h"
#include "sphere.h"
#include "texture.h"
#include <ctime>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "surface_texture.h"

#include "rectangle.h"

/* 【功能】获取当前打印像素点所需颜色色值。 */
/*
    接受参数: <观察者光线>，<所有可命中物体组构成的世界>，<递归层数>。
    对散射进行递归
*/
vec3 color(const ray &r, hittable *world, int depth)
{
    hit_record rec;
    bool hitanything = world->hit(r, 0.001, FLT_MAX, rec);
    if (hitanything)   // 光线物体有交点
    {
        ray scattered;      // 散射/反射后光线
        vec3 attenuation;   // 衰减
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return emitted + attenuation * color(scattered, world, depth+1);  // 根据命中的材质特性，光线被吸收多少，相应衰减多少强度
        }
        else
            return emitted;
    }
    else    // 无交点，背景色
        return vec3(0, 0, 0);
}

hittable *cornell_box()
{
    hittable **list = new hittable *[6];
    int i = 0;
    material *red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));

    // 该视角：左x轴正向，上y轴正向，纸内z轴正向，前方的墙z坐标555.
    list[i++] = new flip_normal(new yz_rect(0, 555, 0, 555, 555, green));   // 左
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);                        // 右
    list[i++] = new xz_rect(213, 343, 227, 332, 554, light);                // 小灯
    // list[i++] = new xz_rect(113, 443, 127, 432, 554, light);             // 大灯
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);                      // 底
    list[i++] = new flip_normal(new xz_rect(0, 555, 0, 555, 555, white));   // 顶
    list[i++] = new flip_normal(new xy_rect(0, 555, 0, 555, 555, white));   // 前

    // add two box
    list[i++] = new box(vec3(130, 0, 65), vec3(295, 165, 230), white);
    list[i++] = new box(vec3(265, 0, 295), vec3(430, 330, 460), white);

    return new hittable_list(list, i);
}

int main()
{
    clock_t start, end;
    start = clock();

    ofstream output;
    output.open("chapter7-.ppm");
    
    if(output.is_open()) printf("open file ok\n");

    int nx = 800, ny = 800 , ns = 100;
    output << "P3\n" << nx << " " << ny << "\n255\n";

    end = clock();
    printf("test time: %fs\n",(double)(end-start)/CLOCKS_PER_SEC); 

    printf("\n[create world]\n");
    hittable *world = cornell_box();
    printf("\n[world create ok]\n");

    // cornell
    vec3 lookfrom(278, 278, -800);
    vec3 lookat(278, 278, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 60.0;
    camera cam( lookfrom, lookat, vec3(0,1,0), 
                vfov, float(nx)/float(ny), 
                aperture, dist_to_focus, 
                0.0, 0.5);
    printf("camera create ok\n");

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);  // 针对每个像素点，初始色值0
            // printf("pos: (%d %d)\n", i, j);
            for(int s = 0; s < ns; s++) // 每个像素点中用100束光线进行采样
            {
                // 光线方向在camera中已设定好，这里生成的就是在成像平面上相对左下角，在宽高两方向上偏移的系数
                float offsetu = float(i + random_double()) / float(nx);
                float offsetv = float(j + random_double()) / float(ny);
                // 对当前的采样值生成光线并映射到相应色值，累加
                ray r = cam.get_ray(offsetu, offsetv);
                col += color(r, world, 0);
            }
            // printf("\n");
            col /= float(ns);   // 最后取均值
            // "Gamma 2"，开1/gamma次根号，这里即开根号
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            output << ir << " " << ig << " " << ib << "\n";
            // printf("i=%d, j=%d\n", i, j);
        }
    }

    output.close();

    end = clock();
    double second = (double)(end-start) / CLOCKS_PER_SEC;
    printf("Run time: %fs\n", second);

    system("pause");
    return 0;
}