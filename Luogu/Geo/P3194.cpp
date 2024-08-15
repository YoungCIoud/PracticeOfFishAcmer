#include<bits/stdc++.h>

// 斜率 截距 编号
typedef std::array<double, 3> line;
typedef std::array<double, 2> node;

// 两直线交点
node meet(line a, line b)
{
    return (node){ (b[1] - a[1]) / (a[0] - b[0]), (a[0] * b[1] - b[0] * a[1]) / (a[0] - b[0])};
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::vector<line> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i][0] >> a[i][1];
        a[i][2] = i + 1;
    }
    std::sort(a.begin(), a.end(), [](line a, line b){
        if (a[0] == b[0]) return a[1] < b[1];
        else return a[0] < b[0];
    });

    std::vector<line> stk(n);
    int p = -1;
    for (int i = 0; i < n; i++)
    {
        if (i + 1 < n && a[i][0] == a[i + 1][0]) continue;
        while (p >= 1 && meet(stk[p], stk[p - 1])[0] >= meet(stk[p], a[i])[0]) p--;
        stk[++p] = a[i];
    }

    sort(stk.begin(), stk.begin() + 1 + p, [](line a, line b){
        return a[2] < b[2];
    });
    for (int i = 0; i <= p; i++)
        std::cout << stk[i][2] << " ";

    system("pause");

    return 0;
}