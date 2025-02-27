#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    std::vector<int> pos;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            pos.push_back(i);
        }
    }

    int mid = (pos.size() - 1) / 2;
    i64 ans = 0;
    for (int i = 0; i <= mid; i++) {
        ans += pos[mid] - pos[i];
    }
    for (int i = mid + 1; i < pos.size(); i++) {
        ans += pos[i] - pos[mid];
    }

    ans -= 1ll * mid * (mid + 1) / 2ll;
    ans -= 1ll * (pos.size() - mid - 1) * (pos.size() - mid) / 2ll;
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}