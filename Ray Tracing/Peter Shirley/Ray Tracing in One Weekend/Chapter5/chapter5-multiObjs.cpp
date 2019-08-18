#include <fstream>
// #include "float.h"
#include <cfloat>
#include "sphere.h"
#include "hitable_list.h"

/* 【功能】获取当前打印像素点所需颜色色值。 */
/*
    接受参数: <观察者光线> 和 <所有可命中物体组构成的世界>。
    调用可命中物体列表的hit函数，求这束观察者光线和世界中的物体有无交点并得到最近的交点相关数据。
*/
vec3 color(const ray &r, hitable *world)
{
    hit_record rec;
    // if (world->hit(r, 0.0, MAXFLOAT, rec))
    if (world->hit(r, 0.0, FLT_MAX, rec))   // 有交点
    {
        // 根据交点法线x, y, z相应映射成颜色色值        
        return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
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
    output.open("chapter5-multiObjs.ppm");

    int nx = 200, ny = 100;
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

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            /*
                生成射线r（假设是观察者正在看所显示的平面上一个像素点，即当前要打印颜色的像素点）：
                1. 由于eye位置在原点所以A = origin。
                2. 射线方向为 <被观察像素点> - <eye位置> 所得向量，其中eye原点，因此即<被观察像素点>。
                通过要显示平面左下角坐标加上横纵偏移量求得。
            */
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r, world);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            output << ir << " " << ig << " " << ib << "\n";
        }
    }

    output.close();
    return 0;
}