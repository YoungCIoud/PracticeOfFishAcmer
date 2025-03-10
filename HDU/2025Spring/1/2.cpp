#include <bits/stdc++.h>

#define IOS \
std::ios::sync_with_stdio(false);\
std::cin.tie(nullptr);\
std::cout.tie(nullptr);

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, inv2 = 499122177;
constexpr int N = 1e5, M = 1e5, L = 1e6;

void solve() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector p(k + 1, std::pair<int, i64>{ 0, 1ll });
    for (int i = 0; i <= k; i++) {
        std::cin >> p[i].first;
        p[i].first--;
    }
    
    std::sort(p.begin() + 1, p.end());
    i64 ans = 1;
    for (; p.size() > 1 ; n = n + 1 >> 1, p[0].first >>= 1) {
        if ((p[0].first ^ 1) < n) {
            auto it = std::lower_bound(p.begin() + 1, p.end(), std::pair<int, i64>{ p[0].first ^ 1, 0 });
            if (it != p.end() && (*it).first == (p[0].first ^ 1)) {
                (ans *= Mod + 1ll - (*it).second) %= Mod;
                p.erase(it);
            }
        }
        for (int j = 1; j < p.size(); j++) {
            if (j + 1 < p.size() && (p[j].first ^ 1) == p[j + 1].first) {
                std::pair<int, i64> tmp = { p[j].first >> 1, (p[j].second + p[j + 1].second) * inv2 % Mod };
                p[j] = p[j + 1] = tmp;
                j++;
            }
            else {
                if ((p[j].first ^ 1) < n) {
                    (p[j].second *= inv2) %= Mod;
                }
                p[j].first >>= 1;
            }
        }
        p.erase(std::unique(p.begin() + 1, p.end()), p.end());
    }
    std::cout << ans << '\n';
    return;
}

int main () {
    IOS

    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        solve();
    }

    return 0;
}
