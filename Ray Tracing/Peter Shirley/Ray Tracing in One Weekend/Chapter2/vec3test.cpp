#include <bits/stdc++.h>
#include "vec3.h"
using namespace std;

int main()
{
    // 输入输出测试
    vec3 test(1,2,3);
    cout << test << endl;

    cout << "Please input the x,y,z: \n";
    cin >> test;
    cout << test << endl;

    test = vec3(6,6,6);
    vec3 one(1,1,1);
    // 单目测试
    cout << +one << endl;   // 1 1 1
    cout << -one << endl;   // -1 -1 -1
    // 双目测试
    cout << one+test << endl;   // 7 7 7
    cout << test-one << endl;   // 5 5 5
    cout << one*test << endl;   // 6 6 6
    cout << test/vec3(2,2,2) << endl;   // 3 3 3
    cout << 8*one << endl;  // 8 8 8 
    cout << one*8 << endl;  // 8 8 8
    cout << test/2 << endl; // 3 3 3

    // 复合赋值测试
    test += one;
    cout << test << endl; // 7 7 7
    test -= one;
    cout << test << endl; // 6 6 6
    test *= vec3(2,2,2);
    cout << test << endl; // 12 12 12
    test /= vec3(2,2,2);
    cout << test << endl; // 6 6 6
    test *= 2.0;
    cout << test << endl; // 12 12 12
    test /= 2.0;
    cout << test << endl; // 6 6 6

    // 下标运算测试
    vec3 test2(5,10,20);
    cout << test2[0] << " " << test2[1] << " " << test2[2] << endl;
    const vec3 testc(50,100,200);
    cout << testc[0] << " " << testc[1] << " " << testc[2] << endl;

    // 向量相关测试
    vec3 testl(1,2,2);
    cout << testl.length() << endl; // 3
    cout << testl.squared_length() << endl; // 9
    vec3 testu(1,1,1);
    testu.make_unit_vector();
    cout << testu << endl;   // 0.577 0.577 0.577 (1/sqrt(3))
    testu = vec3(1,1,1);
    cout << unit_vector(testu) << endl; // 0.577 0.577 0.577

    // 点积
    cout << dot(one, test) << endl; // 18

    // 叉乘
    cout << cross(vec3(1,1,1), vec3(2,3,4)) << endl; // 1 -2 1

    return 0;
}