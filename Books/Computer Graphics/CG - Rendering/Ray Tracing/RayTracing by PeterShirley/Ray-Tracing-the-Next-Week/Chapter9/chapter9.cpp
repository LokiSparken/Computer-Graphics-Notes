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
#include "constant_medium.h"

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

hittable *final() 
{
    int nb = 20;
    hittable **list = new hittable*[30];
    hittable **boxlist = new hittable*[10000];
    hittable **boxlist2 = new hittable*[10000];
    material *white = new lambertian( new constant_texture(vec3(0.73, 0.73, 0.73)) );
    material *ground = new lambertian( new constant_texture(vec3(0.48, 0.83, 0.53)) );
    int b = 0;
    for (int i = 0; i < nb; i++) 
    {
        for (int j = 0; j < nb; j++) 
        {
            float w = 100;
            float x0 = -1000 + i*w;
            float z0 = -1000 + j*w;
            float y0 = 0;
            float x1 = x0 + w;
            float y1 = 100*(random_double()+0.01);
            float z1 = z0 + w;
            boxlist[b++] = new box(vec3(x0,y0,z0), vec3(x1,y1,z1), ground);
        }
    }
    int l = 0;
    list[l++] = new bvh_node(boxlist, b, 0, 1);
    // material *light = new diffuse_light( new constant_texture(vec3(7, 7, 7)) );
    // list[l++] = new xz_rect(123, 423, 147, 412, 554, light);
    // list[l++] = new xz_rect(173, 423, 147, 412, 554, light);
    vec3 center(400, 400, 200);
    list[l++] = new moving_sphere(center, center+vec3(30, 0, 0), 0, 1, 50, new lambertian(new constant_texture(vec3(0.7, 0.3, 0.1))));
    list[l++] = new sphere(vec3(260, 150, 45), 50, new dielectric(1.5));
    list[l++] = new sphere(vec3(0, 150, 145), 50, new metal(vec3(0.8, 0.8, 0.9), 10.0));
    // hittable *boundary = new sphere(vec3(360, 150, 145), 70, new dielectric(1.5));
    // list[l++] = boundary;
    // list[l++] = new constant_medium(boundary, 0.2, new constant_texture(vec3(0.2, 0.4, 0.9)));
    // boundary = new sphere(vec3(0, 0, 0), 5000, new dielectric(1.5));
    // list[l++] = new constant_medium(boundary, 0.0001, new constant_texture(vec3(1.0, 1.0, 1.0)));
    int nx, ny, nn;
    unsigned char *tex_data = stbi_load("earth.jpg", &nx, &ny, &nn, 0);
    material *emat =  new lambertian(new image_texture(tex_data, nx, ny));
    list[l++] = new sphere(vec3(400,200, 400), 100, emat);
    texture *pertext = new noise_texture(0.1);
    list[l++] =  new sphere(vec3(220,280, 300), 80, new lambertian( pertext ));
    int ns = 1000;
    for (int j = 0; j < ns; j++) 
    {
        boxlist2[j] = new sphere(vec3(165*random_double(), 165*random_double(), 165*random_double()), 10, white);
    }
    list[l++] =   new translate(new rotate_y(new bvh_node(boxlist2,ns, 0.0, 1.0), 15), vec3(-100,270,395));
    return new hittable_list(list,l);
}

int main()
{
    clock_t start, end;
    start = clock();

    ofstream output;
    output.open("chapter9-4-100pp-nofog.ppm");
    
    if(output.is_open()) printf("open file ok\n");

    int nx = 800, ny = 800 , ns = 100;
    output << "P3\n" << nx << " " << ny << "\n255\n";

    end = clock();
    printf("test time: %fs\n",(double)(end-start)/CLOCKS_PER_SEC); 

    printf("\n[create world]\n");
    hittable *world = final();
    printf("\n[world create ok]\n");

    // cornell
    vec3 lookfrom(278, 278, -800);
    vec3 lookat(278, 278, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 40.0;
    camera cam( lookfrom, lookat, vec3(0,1,0), 
                vfov, float(nx)/float(ny), 
                aperture, dist_to_focus, 
                0.0, 1.0);
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