#include <fstream>
#include <cfloat>
#include "camera.h"
#include "sphere.h"
#include "material.h"
#include "hitable_list.h"

/* 【功能】获取当前打印像素点所需颜色色值。 */
/*
    接受参数: <观察者光线>，<所有可命中物体组构成的世界>，<递归层数>。
    对散射进行递归，
*/
vec3 color(const ray &r, hitable *world, int depth)
{
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec))   // 光线物体有交点
    {
        ray scattered;      // 散射/反射后光线
        vec3 attenuation;   // 衰减
        // 手动设置递归层数小于50层，并发生散射/反射后，用新产生的光线继续emmmm...射出去撞东西？最后各向综合起来的才是最终观察到的颜色。
        // 递归层数是防止光线在一个只有反射面的盒子里，递归到爆
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth+1);  // 根据命中的材质特性，光线被吸收多少，相应衰减多少强度
        }
        else // 层数到了或者衰减到一定程度就莫有了，(0, 0, 0)黑色
        {
            return vec3(0, 0, 0);
        }
        
    }
    else    // 无交点
    {
        // 那就是原来的背景色！
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    ofstream output;
    output.open("chapter10-ok-addvfov&aspect.ppm");  // debug过程中左球效果一直和作者说的错误情况长得很像……嘤嘤嘤

    int nx = 200, ny = 100 , ns = 100;
    output << "P3\n" << nx << " " << ny << "\n255\n";

    camera cam(90, float(nx)/float(ny));

    float R = cos(M_PI/4);
    hitable *list[2];
    list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
    list[1] = new sphere(vec3( R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
    hitable *world = new hitable_list(list,2);

    // // 新增两个球，原来的两个磨砂，小球左右各放个金属材质的，可以反射出中间小球的样子
    // hitable *list[5];   // 建立可命中的物体组，存为链表。抽象父类指向继承该父类的球体子类。
    // list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));      // 中间球，改性质了
    // list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0))); // 下面的大球
    // list[2] = new sphere(vec3(1, 0,-1), 0.5, new metal(vec3(0.8,0.6,0.2), 0.3));  // 右球
    // list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));  // 左球（折射率1.5，玻璃球）
    // list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));

    // hitable *world = new hitable_list(list, 5);

    // camera cam; // 建立观察者/相机

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);  // 针对每个像素点，初始色值0
            for(int s = 0; s < ns; s++) // 每个像素点中用100束光线进行采样
            {
                // 每束光线的具体横纵方向随机生成[0, 1)之间的数值进行随机采样
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                // 对当前的采样值生成光线并映射到相应色值，累加
                ray r = cam.get_ray(u, v);
                // vec3 p = r.point_at_parameter(2.0);  // 不明白这行有什么用？是不是作者忘记删了
                col += color(r, world, 0);
            }
            col /= float(ns);   // 最后取均值
            // "Gamma 2"，开1/gamma次根号，这里即开根号
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            output << ir << " " << ig << " " << ib << "\n";
        }
    }

    output.close();
    return 0;
}