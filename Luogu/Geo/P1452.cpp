#include<bits/stdc++.h>

// 返回一个从a指向b的向量
std::array<int, 2> v(std::array<int, 2> a, std::array<int, 2> b)
{
    return { b[0] - a[0], b[1] - a[1] };
}

// 向量a叉乘向量b
int cross(std::array<int, 2> a, std::array<int, 2> b)
{
    return a[0] * b[1] - a[1] * b[0];
}

// 返回abc三点组成的三角形的面积的两倍
int s(std::array<int, 2> a, std::array<int, 2> b, std::array<int, 2> c)
{
    return abs(cross(v(a, b), v(a, c)));
}

//  返回两点之间距离的平方
int d2(std::array<int, 2> a, std::array<int, 2> b)
{
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
}

int main()
{
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);

    int n = 0;
    std::cin >> n;
    std::vector<std::array<int, 2>> a(n);
    for (auto& [x, y] : a) std::cin >> x >> y;
    std::sort(a.begin(), a.end());

    // 求凸包
    std::vector<int> stk(n), idx;
    int p = -1;
    for (int i = 0; i < n; i++)
    {
        while (p >= 1 && cross(v(a[stk[p - 1]], a[stk[p]]), v(a[stk[p]], a[i])) >= 0) p--;
        stk[++p] = i;
    }
    for (int i = 0; i <= p; i++)
        idx.push_back(stk[i]);
    p = -1;
    for (int i = n - 1; i >= 0; i--)
    {
        while (p >= 1 && cross(v(a[stk[p - 1]], a[stk[p]]), v(a[stk[p]], a[i])) >= 0) p--;
        stk[++p] = i;
    }
    for (int i = 1; i <= p; i++)
        idx.push_back(stk[i]);
    
    // 求直径
    int siz = idx.size() - 1, ans = 0;

    if (siz != 2) for (int i = 0, j = 0; i < siz; i++)
    {
        while ( s(a[idx[j]], a[idx[i]], a[idx[i + 1]]) <= s(a[idx[j + 1]], a[idx[i]], a[idx[i + 1]])) j = (j + 1) % siz;
        ans = std::max({ ans, d2(a[idx[j]], a[idx[i]]), d2(a[idx[j]], a[idx[i + 1]])});
    }

    std::cout << std::max(ans, d2(a[idx[0]], a[idx[siz - 1]])) << '\n';

    system("pause");

    return 0;
}