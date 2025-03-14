#include <bits/stdc++.h>

#define IOS \
std::ios::sync_with_stdio(false);\
std::cin.tie(nullptr);\
std::cout.tie(nullptr);

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, inv2 = 499122177, Inf = 1e15;
constexpr int N = 1e5, M = 20;
std::vector<int> a;
std::array<int, 4> line[(N << 1) + 5];

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
    a.push_back(-1);
    
    // the number of rectangle
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        line[i] = { y1, x1, x2, 1 };
        line[i + n] = { y2, x1, x2, -1 };
        a.push_back(x1), a.push_back(x2);
    }
    // the number of horizontal line
    n <<= 1;

    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());

    std::sort(line, line + n, 
            [] (auto &u, auto &v) -> bool { return u[0] < v[0]; });

    for (int i = 0; i < n; i++) {
        line[i][1] = std::lower_bound(a.begin(), a.end(), line[i][1]) - a.begin();
        line[i][2] = std::lower_bound(a.begin(), a.end(), line[i][2]) - a.begin();
    }

    i64 ans = 0;
    int tot = a.size() - 1; // the number of different x
    add(1, 1, tot, line[0][1], line[0][2], line[0][3]);
    for (int i = 1; i < n; i++) {
        ans += 1ll * (line[i][0] - line[i - 1][0]) * w[1];
        add(1, 1, tot, line[i][1], line[i][2], line[i][3]);
    }
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
