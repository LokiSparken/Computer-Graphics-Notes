#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a[5][5]={{1,2,3,4,5}};
    auto t1 = a[0];
    auto &t2 = a[0];

    cout << typeid(t1).name() << endl;
    cout << *t1 << endl << endl;

    cout << typeid(t2).name() << endl;

    system("pause");
    return 0;
}