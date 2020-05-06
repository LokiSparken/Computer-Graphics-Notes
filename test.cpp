#include <bits/stdc++.h>
using namespace std;

int main()
{
    char *a[2];
    char *p0 = (char *)&a[0], *p1 = (char *)&a[1];
    // int *p0 = (int *)&a[0], *p1 = (int *)&a[1];
    // char *p0 = &a[0], *p1 = &a[1];
    cout << p1-p0 << endl;
    cin >> a[0];
    return 0;
}