#include<bits/stdc++.h>

// 求a对p的逆元
// 设a对p的逆元为x, 则 ax = yp + 1(y是一个常数)
// 也可看成 ax + py = 1(此行的y和上一行的y互为相反数)
// 当且仅当gcd(a, p) = 1时上式子有解

// 返回gcd(a,b)
int extend_gcd(long long a, int b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int res = extend_gcd(b, a % b, x, y);

    int t = x;
    x = y;
    y = t - (a / b) * y;

    return res;
}

// 求a关于p的逆元
long long inv(long long a, int p)
{
    long long x = 0, y = 0;
    extend_gcd(a, p, x, y);

    return (x % p + p) % p;
}

int main()
{
    const int P = 9973;
    int t = 1;
    std::cin >> t;
    while (t--)
    {
        long long a = 0, b = 0;
        std::cin >> a >> b;

        std::cout << a * inv(b, P) % P << '\n';
    }
    system("pause");
    return 0;
}