#include<bits/stdc++.h>

class v2
{
public:
    v2(double x = 0, double y = 0):x(x), y(y)
    {
        len = sqrt(x * x + y * y);
    }
    // 向量由a指向b
    v2(std::array<double, 2>& a, std::array<double, 2>& b)
    {
        x = b[0] - a[0], y = b[1] - a[1];
        len = sqrt(x * x + y * y);
    }
    
    double length()
    {
        return len;
    }

    v2 operator+(const v2& a)
    {
        return v2(x + a.x, y + a.y);
    }

    v2 operator-(const v2& a)
    {
        return v2(x - a.x, y - a.y);
    }
    // 数乘
    v2 operator* (const double a)
    {
        return v2(a * x, a * y);
    }
    // 点积
    double operator* (const v2& a)
    {
        return x * a.x + y * a.y;
    }
    // 叉积
    double operator^ (const v2& a)
    {
        return x * a.y - a.x * y;
    }
private:
    double x, y;
    double len;
};

int main()
{
    int n = 0;
    std::cin >> n;
    std::vector<std::array<double, 2>> a(n);
    for (auto& [x, y] : a) std::cin >> x >> y;
    sort(a.begin(), a.end());

    std::vector<int> stk(n), c;
    int p = -1;
    for (int i = 0; i < n; i++)
    {
        while (p >= 1 && (v2(a[stk[p - 1]], a[stk[p]]) ^ v2(a[stk[p]], a[i])) > 0) p--;
        stk[++p] = i;
    }
    for (int i = 0; i <= p; i++) c.push_back(stk[i]);

    p = -1;
    for (int i = n - 1; i >= 0; i--)
    {
        while (p >= 1 && (v2(a[stk[p - 1]], a[stk[p]]) ^ v2(a[stk[p]], a[i])) > 0) p--;
        stk[++p] = i;
    }
    for (int i = 1; i <= p; i++) c.push_back(stk[i]);

    auto dis = [&](std::array<double, 2> a, std::array<double, 2> b) -> double
    {
        return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));
    }; 

    double ans = 0.0;
    for (int i = 1; i < c.size(); i++)
        ans += dis(a[c[i]], a[c[i - 1]]);
    
    printf("%.2lf\n", ans);
    
    system("pause");

    return 0;
}