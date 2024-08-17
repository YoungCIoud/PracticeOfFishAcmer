#include<bits/stdc++.h>

using i64 = long long;
constexpr i64 Mod = 998244353;

i64 qpow(i64 a, i64 p)
{
    i64 res = 1;
    for (; p; a = a * a % Mod, p >>= 1)
        if (p & 1) res = res * a % Mod;
    return res;
}

i64 inv(i64 a)
{
    return qpow(a, Mod - 2);
}

int main()
{
    i64 a = 0, b = 0;
    std::cin >> a >> b;
    i64 i = inv(a + b);
    std::cout << a * i % Mod << " " << b * i % Mod;

    system("pause");

    return 0;
}