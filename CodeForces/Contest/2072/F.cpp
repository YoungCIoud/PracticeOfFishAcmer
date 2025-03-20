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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e6, MAX = 1e9; 
int cnt2[N + 5];

void solve() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    n--;
    
    int cnt = 0;
    std::cout << k << ' ';
    for (int i = 1, j = n; i <= n; i++, j--) {
        cnt -= cnt2[i];
        cnt += cnt2[j];
        std::cout << (cnt ? 0 : k) << ' ';
    }
    std::cout << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;

    for (int i = 2; i <= N; i++) {
        cnt2[i] = std::log2(i & -i);
    }

    while (_t--)
    {
        solve();
    }

    return 0;
}
