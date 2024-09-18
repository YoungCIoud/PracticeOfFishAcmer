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
    str S{}, T{};
    std::cin >> S >> T;

    vct<str> ans{};
    for (int i = 0; i < S.size(); i++)
        if (S[i] > T[i])
        {
            S[i] = T[i];
            ans.push_back(S);
        }
    for (int i = S.size() - 1; ~i; i--)
        if (S[i] < T[i])
        {
            S[i] = T[i];
            ans.push_back(S);
        }
    
    std::cout << ans.size() << '\n';
    for (auto& s : ans) std::cout << s << '\n';
    return;
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