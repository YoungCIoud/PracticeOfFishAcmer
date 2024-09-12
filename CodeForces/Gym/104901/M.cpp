#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

std::pair<int, int> v(std::pair<int, int> a, std::pair<int, int> b)
{
    return { b.first - a.first, b.second - a.second };
}

i64 operator^ (std::pair<int, int> a, std::pair<int, int> b)
{
    return 1ll * a.first * b.second - 1ll * b.first * a.second;
}

struct Node
{
    bool ok;
    int x, y;
}O, P;
// inline bool cmp(Node &A, Node &B)
// {
//     // 考虑向量和OP同向
//     if (A.y == O.y && A.x >= O.x) return true;
//     if (B.y == O.y && B.x >= O.x) return false;

//     std::pair<int, int> OP = { 1, 0 }, OA = { A.x - O.x, A.y - O.y }, OB = { B.x - O.x, B.y - O.y };
//     // 考虑OA和OB在OP异侧
//     if (((OP ^ OA) > 0) ^ ((OP ^ OB) > 0)) return (OP ^ OA) > 0;
//     else return (OA ^ OB) > 0;
// }
inline bool cmp(Node &A, Node &B)
{
    std::pair<int, int> OA = { A.x - O.x, A.y - O.y }, OB = { B.x - O.x, B.y - O.y };
    if (OA ^ OB) return (OA ^ OB) > 0;
    else return OA.first < OB.first;
}
void solve()
{
    int n = 0;
    std::cin >> n;
    vct<std::pair<int, int>> a(n);
    vct<bool> cv(n);
    for (auto &[x, y] : a) std::cin >> x >> y;
    std::sort(a.begin(), a.end());

    vct<int> stk(n);
    int p = -1;
    for (int i = 0; i < n; i++)
    {
        while (p >= 1 && (v(a[stk[p - 1]], a[stk[p]]) ^ v(a[stk[p]], a[i])) > 0) p--;
        stk[++p] = i;
    }
    for (int i = 0; i < p; i++) cv[stk[i]] = true;

    p = -1;
    for (int i = n - 1; i >= 0; i--)
    {
        while (p >= 1 && (v(a[stk[p - 1]], a[stk[p]]) ^ v(a[stk[p]], a[i])) > 0) p--;
        stk[++p] = i;
    }
    for (int i = 0; i < p; i++) cv[stk[i]] = true;

    // for (int i = 0; i < n; i++)
    //     if (cv[i]) std::cout << a[i].first << ' ' << a[i].second << '\n';

    int ans = 1;
    vct<Node> t(n - 1);
    for (int i = 0; i < n; i++)
    {
        if (cv[i]) continue;

        // 以第i个点为极点进行极角排序
        O = { false, a[i].first, a[i].second };
        P = O, P.x++;

        int tot = 0;
        for (int j = 0; j < n; j++)
            if (i != j) t[tot++] = { cv[j], a[j].first, a[j].second };
        sort(t.begin(), t.end(), cmp);

        for (int j = 1; j <= n - 1; j++)
            if (t[j % (n - 1)].ok && t[j - 1].ok) ans++;
    }

    std::cout << ans << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}