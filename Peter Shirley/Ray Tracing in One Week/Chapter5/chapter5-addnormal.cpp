#include <fstream>
#include "ray.h"

/* 【功能】判断是否与球有交点*/
float hit_sphere(const vec3 &center, float radius, const ray &r)
{
    vec3 oc = r.origin() - center;  // A-C
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(r.direction(), oc);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - 4*a*c;   // 二次方程delta
    if (discriminant < 0)   // 方程无解，没有交点
    {
        return -1.0;
    }
    else    // 否则取其中较小的一个即可。
    /*
        因为参数t是确定点在射线上位置的p(t)=A+Bt，离出发点光源A越近则离观察者越近。
        当有两个交点时，两个交点在观察者方向看到的结果平面上投影为一个点，所以取近的即可。
        而且要用近的这个点的法向求对应rgb。
    */
    {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
    
}

/* 【功能】获取当前打印像素点所需颜色色值。 */
vec3 color(const ray &r)
{
    // 【打印球，根据不同的法向获取不同色值】
    float t = hit_sphere(vec3(0, 0, -1), 0.5, r);   // 求光线和球体交点情况
    if (t > 0.0)    // 有交点时
    {
        // 此处的法向量即交点减去球心得到的向量，再单位化
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
        // 单位法向x, y, z从[-1,1]，整体+1再/2，转到[0, 1]
        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
    }
    // 【打印背景】
    // 得到光射线方向的单位向量
    vec3 unit_direction = unit_vector(r.direction());
    /* 
        以该方向在垂直（y轴）方向上的位置决定所需要的颜色是白还是蓝。
        t = 1 蓝，t = 0 白
        由于垂直范围原来在[-1,1]之间，因此整体+1再/2，转化到[0,1]，使用线性插值将颜色区间进行缩放。
    */
    t = 0.5*(unit_direction.y() + 1.0);
    /*
        blended_value = (1-t)*s + t*e, t∈[0,1]
        我总感觉还是写成这样的形式更容易理解啊……
        blended_value = s + (e-s)*t, t∈[0,1]
        起始 + 长度×偏移比例QAQ
        听说前面那个形式统一一点=。=|||
    */
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    /*
        返回出去后惠*255.99，因此实际上的色值起始返回是：
        s = (255, 255, 255) 白
        e = (128, 179, 255) 一种蓝
    */
}

int main()
{
    ofstream output;
    output.open("chapter5-addnormal.ppm");

    int nx = 200, ny = 100;
    output << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);   // 要显示的平面左下角坐标
    vec3 horizontal(4.0, 0.0, 0.0);             // 水平（x轴）方向显示范围
    vec3 vertical(0.0, 2.0, 0.0);               // 垂直（y轴）方向显示范围
    vec3 origin(0.0, 0.0, 0.0);                 // 相机/观察者脑袋（eye）位置

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
            vec3 col = color(r);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            output << ir << " " << ig << " " << ib << "\n";
        }
    }

    output.close();
    return 0;
}