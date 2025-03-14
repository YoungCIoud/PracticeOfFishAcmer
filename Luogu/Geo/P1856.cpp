#include <bits/stdc++.h>

#define IOS \
std::ios::sync_with_stdio(false);\
std::cin.tie(nullptr);\
std::cout.tie(nullptr);

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, inv2 = 499122177;
constexpr int N = 1e5, M = 20, Inf = 1e9;
std::vector<int> a;

int v[N << 3], w[N << 3];
void pushup(int cur, int l, int r) {
    if (v[cur] != 0) {
        w[cur] = a[r] - a[l];
    }
    else if (l + 1 == r) {
        w[cur] = 0;
    }
    else {
        w[cur] = w[cur << 1] + w[cur << 1 | 1];
    }
    return;
}

// 左闭右开
void add(int cur, int l, int r, int sl, int sr, int val) {
    if (sl <= l && r <= sr) {
        v[cur] += val;
        pushup(cur, l, r);
        return;
    }

    int m = l + r >> 1;
    if (sl < m) {
        add(cur << 1, l, m, sl, sr, val);
    }
    if (sr > m) {
        add(cur << 1 | 1, m, r, sl, sr, val);
    }

    pushup(cur, l, r);
}

void solve() {
    a.clear();
    a.push_back(-Inf);
    
    // the number of rectangle
    int n = 0;
    std::cin >> n;
    std::vector linex(n << 1, std::array<int, 4>{});
    std::vector liney(n << 1, std::array<int, 4>{});
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        
        linex[i] = { y1, x1, x2, 1 };
        linex[i + n] = { y2, x1, x2, -1 };
        a.push_back(x1), a.push_back(x2);

        liney[i] = { x1, y1, y2, 1};
        liney[i + n] = { x2, y1, y2, -1 };
        a.push_back(y1), a.push_back(y2);
    }
    // the number of horizontal line or the vertical line
    n <<= 1;

    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());

    std::sort(linex.begin(), linex.end(), 
            [] (auto &u, auto &v) -> bool { return u[0] < v[0]; });
    std::sort(liney.begin(), liney.end(), 
            [] (auto &u, auto &v) -> bool { return u[0] < v[0]; });

    for (int i = 0; i < n; i++) {
        linex[i][1] = std::lower_bound(a.begin(), a.end(), linex[i][1]) - a.begin();
        linex[i][2] = std::lower_bound(a.begin(), a.end(), linex[i][2]) - a.begin();
        
        liney[i][1] = std::lower_bound(a.begin(), a.end(), liney[i][1]) - a.begin();
        liney[i][2] = std::lower_bound(a.begin(), a.end(), liney[i][2]) - a.begin();
    }

    i64 ans = 0;
    int tot = a.size() - 1;
    for (int i = 0, cur = 0; i < n; i++) {
        add(1, 1, tot, liney[i][1], liney[i][2], liney[i][3]);
        int d = std::abs(cur - w[1]);
        // if (d) {
        //     std::cout << d << ' ';
        // }
        ans += std::abs(cur - w[1]);
        cur = w[1];
    }
    // std::cout << '\n';
    for (int i = 0, cur = 0; i < n; i++) {
        add(1, 1, tot, linex[i][1], linex[i][2], linex[i][3]);
        int d = std::abs(cur - w[1]);
        // if (d) {
        //     std::cout << d << ' ';
        // }
        ans += std::abs(cur - w[1]);
        cur = w[1];
    }
    // std::cout << '\n';
    std::cout << ans << '\n';
    return;
}

int main () {
    IOS

    int _t = 1;
//    std::cin >> _t;
    while (_t--) {
        solve();
    }

    return 0;
}