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
    int n = 0, k = 0;
    std::cin >> n >> k;
    i64 mn = 0;
    std::vector v(n, std::vector<int>{});
    for (auto &a : v) {
        int l = 0;
        std::cin >> l;
        a.assign(l, 0);
        for (auto &i : a) {
            std::cin >> i;
        }

        // 计算 a 中的逆序对的数量
        for (int i = 0; i < l; i++) {
            for (int j = i + 1; j < l; j++) {
                if (a[i] > a[j]) {
                    mn++;
                }
            }
        }
    }
    
    std::sort(v.begin(), v.end(), [&](const auto &x, const auto &y) {
        return x[0] > y[0];
    });
    i64 mx = mn;
    int len = 0;
    for (auto &a : v) {
        mx += len * a.size();
        len += a.size();
    }

    if (k < mn || k > mx) {
        std::cout << "No\n";
        return;
    }
    else {
        std::cout << "Yes\n";
    }

    k -= mn;
    std::array<int, 2> idx = { -1, -1 };
    for (int i = 0; i < n && (idx[0] == -1); i++) {
        len -= v[i].size();
        for (int j = 0; j < v[i].size(); j++) {
            if (len > k) {
                idx = { i, j };
                break;
            }
            else {
                k -= len;
                std::cout << v[i][j] << ' ';
            }
        }
    }
    for (int i = n - 1; (~idx[0]) && i > idx[0]; i--) {
        for (int j = 0; j < v[i].size(); j++) {
            std::cout << v[i][j] << ' ';
            if (--len == k) {
                std::cout << v[idx[0]][idx[1]] << ' ';
            }
        }
    }
    for (int i = idx[1] + 1; (~idx[0]) && i < v[idx[0]].size(); i++) {
        std::cout << v[idx[0]][i] << ' ';
    }
    std::cout << '\n';
    
    return;
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