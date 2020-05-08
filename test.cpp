#include <bits/stdc++.h>
using namespace std;

struct Foo
{
    template <typename T>
    operator T*() { return nullptr; }

    // template <typename T>
    // operator const T*() const { return nullptr; }
};

template <typename T>
void f(T*) { cout << "T*" << endl;}

template <typename T>
void f(const T*) { cout << "const T*" << endl; }

struct Test { };

int main()
{
    Foo a;
    // const Foo b;
    f<int> (a);
    // f<int> (b);

    cout << endl;

    f<Test> (a);
    // f<Test> (b);
    
    system("pause");
    return 0;
}