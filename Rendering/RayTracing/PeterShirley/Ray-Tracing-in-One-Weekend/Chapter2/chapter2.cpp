#include <fstream>
#include "vec3.h"
using namespace std;

int main()
{
    ofstream output;    // 创建ofstream对象
    output.open("chapter2-200x100.ppm");    // 关联文本文件，输出后为测试效果对文件名有所改动

    int nx = 200, ny = 100;
    output << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j=ny-1; j >= 0; j--)
    {
        for (int i=0; i < nx; i++)
        {
            vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            output << ir << " " << ig << " " << ib << "\n";
        }
    }

    output.close();
    return 0;
}