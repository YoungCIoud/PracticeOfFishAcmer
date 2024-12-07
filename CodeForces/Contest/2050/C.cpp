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

bool solve()
{
    std::string str;
    std::cin >> str;
    int sum = 0;
    std::vector cnt(10, 0);
    for (auto &c : str) {
        int d = c - '0';
        sum += d;
        cnt[d]++;
    }
    cnt[3] = std::min(cnt[3], 2);
    sum %= 9;
    if (sum == 0 || cnt[2] >= 8) {
        return true;
    }
    std::vector<int> n;
    while (cnt[2]--) {
        n.push_back(2);
    }
    while (cnt[3]--) {
        n.push_back(6);
    }
    for (int s = 1; s < (1 << n.size()); s++) {
        int res = 0;
        for (int i = 0; i < n.size(); i++) {
            if (s >> i & 1) {
                res += n[i];
            }
        }
        if ((res + sum) % 9 == 0) {
            return true;
        }
    }
    return false;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "Yes" : "No") << '\n';
    }

    sp();

    return 0;
}