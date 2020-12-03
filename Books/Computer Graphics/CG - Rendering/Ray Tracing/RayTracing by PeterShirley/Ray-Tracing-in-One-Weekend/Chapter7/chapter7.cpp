#include <fstream>
#include <cfloat>
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"

// 随机返回一个在单位球内的点坐标
vec3 random_in_unit_sphere()
{
    // 函数内假设球心在原点(0, 0, 0)即可，外面调用处加上球心坐标的偏移
    vec3 p;
    do
    {   // [0, 1]*2 => [0, 2] -1 = [-1, 1]
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0); // 点积>=1不在单位球内，继续生成
    return p;
}

/* 【功能】获取当前打印像素点所需颜色色值。 */
/*
    接受参数: <观察者光线> 和 <所有可命中物体组构成的世界>。
    调用可命中物体列表的hit函数，求这束观察者光线和世界中的物体有无交点并得到最近的交点相关数据。
*/
vec3 color(const ray &r, hitable *world)
{
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec))   // 有交点
    {
        // 光线与物体交点+交点法向得到的坐标作为一个单位球的球心
        // 在这个球上随机选取点，作为漫反射方向经过的点
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        // 最后根据漫反射光线映射成颜色
        return 0.5*color(ray(rec.p, target-rec.p), world);
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
    output.open("chapter7-light.ppm");

    int nx = 200, ny = 100 , ns = 100;
    // 最后测下来还是100吧，一个像素点里100已经很多了，采样数再大没啥更好的效果，计算量还爆炸orz
    output << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);   // 要显示的平面左下角坐标
    vec3 horizontal(4.0, 0.0, 0.0);             // 水平（x轴）方向显示范围
    vec3 vertical(0.0, 2.0, 0.0);               // 垂直（y轴）方向显示范围
    vec3 origin(0.0, 0.0, 0.0);                 // 相机/观察者脑袋（eye）位置

    hitable *list[2];   // 建立可命中的物体组，存为链表。抽象父类指向继承该父类的球体子类。
    list[0] = new sphere(vec3(0, 0, -1), 0.5);      // (0, 0, -1)处半径0.5的球体
    list[1] = new sphere(vec3(0, -100.5, -1), 100); // (0, -100.5, -1)处半径100的球体（最后显示出来那一片绿2333）
    // 可命中物体链表组也继承自抽象的命中类。这里把世界看成可命中物体组构成的，然后由观察者从一个位置（这里origin(0, 0, 0）去观察。
    hitable *world = new hitable_list(list, 2);

    camera cam; // 建立观察者/相机

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
                col += color(r, world);
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