// Output an image in ppm file
#include <fstream>
using namespace std;

int main()
{
    ofstream output;    // 创建ofstream对象
    output.open("chapter1.ppm");    // 关联文本文件，输出后为测试效果对文件名有所改动

    // 按nx*ny像素输出每个像素的RGB到P3格式的ppm文件中
    int nx = 400, ny = 200;
    output << "P3\n" 
           << nx << " " << ny << "\n255\n";
    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float r = float(i) / float(nx);
            float g = 0.2;
            float b = float(j) / float(ny);
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            output << ir << " " << ig << " " << ib << "\n";
        }
    }

    output.close(); // 使用完文本文件后关闭
    return 0;
}