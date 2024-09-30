#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;
std::string s = "aeiou";
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> cnt(5, n / 5);
    for (int i = 0; i < n % 5; i++) {
        cnt[i]++;
    }
    for (int i = 0; i < 5; i++) {
        for (int c = 0; c < cnt[i]; c++) {
            std::cout << s[i];
        }
    }
    std::cout << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}