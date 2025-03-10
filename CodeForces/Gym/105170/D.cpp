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

// #define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

std::array<int, 2> v(std::array<int, 3> u, std::array<int, 3> v) {
    return { v[0] - u[0], v[1] - u[1] };
}

i64 cross(std::array<int, 2> u, std::array<int, 2> v) {
    // x1y2 - x2y1
    return 1ll * u[0] * v[1] - 1ll * v[0] * u[1];
}

void solve() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector p(n, std::array<int, 3>{});
    std::unordered_map<double, std::vector<int>> mp;
    int idx = 0;
    for (auto &[x, y, id] : p) {
        std::cin >> x >> y;
        id = idx++;
        mp[x].push_back(id);
    }
    
    auto out = [](std::unordered_map<double, std::vector<int>> &mp) -> bool {
        bool ok = true;
        for (auto &[b, v] : mp) {
            if (v.size() == 1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (auto &[b, v] : mp) {
                std::cout << v.size() << ' ';
                for (auto &id : v) {
                    std::cout << id + 1 << ' ';
                }
                std::cout << '\n';
            }
        }
        return ok;
    };

    // 特殊情况，k 条竖线x
    if (mp.size() == k && out(mp)) {
        return;
    }
    
    std::sort(p.begin(), p.end(), [](auto &u, auto &v) {
        if (u[0] == v[0]) {
            return u[1] < v[1];
        }
        else {
            return u[0] < v[0];
        }
    });
    
    std::vector stk(2 * n + 5, 0);
    int top = 0;
    for (int i = 0; i < n; i++) {
        while (top >= 2 && cross(v(p[stk[top - 1]], p[i]), v(p[stk[top - 2]], p[stk[top - 1]])) >= 0) {
            top--;
        }
        stk[top++] = i;
    }
    int siz = top;
    for (int i = n - 2; i >= 0; i--) {
        while (top > siz && cross(v(p[stk[top - 1]], p[i]), v(p[stk[top - 2]], p[stk[top - 1]])) >= 0) {
            top--;
        }
        stk[top++] = i;
    }
    
    for (int i = 1; i < top; i++) {
        auto [x1, y1, id1] = p[stk[i - 1]];
        auto [x2, y2, id2] = p[stk[i]];
        
        if (x1 == x2) {
            continue;
        }
        
        double kk = (1.0 * (y1 - y2)) / (1.0 * (x1 - x2));
        mp.clear();
        for (int i = 0; i < n; i++) {
            double b = 1.0 * p[i][1] - 1.0 * p[i][0] * kk;
            mp[b].push_back(p[i][2]);
        }

        if (mp.size() == k && out(mp)) {
            break;
        }
    }

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