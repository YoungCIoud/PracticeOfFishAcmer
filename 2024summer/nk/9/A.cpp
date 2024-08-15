#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    vct<str> s(n);
    for (auto& i : s) std::cin >> i;
    
    int a = 0, b = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] == 'x')
            {
                while (j + b < m && s[i][j + b] == 'x') b++;
                while (i + a < n && s[i + a][j] == 'x') a++;
                break;
            }
        }
    }
    int aa = a / std::__gcd(a ,b);
    int bb = b / std::__gcd(a, b);
    //std::cout << aa << " " << bb << '\n';
    for (int i = 0; i < aa; i++)
        for (int j = 0; j <= bb; j++)
            std::cout << "x\n"[j == bb];
}

int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}