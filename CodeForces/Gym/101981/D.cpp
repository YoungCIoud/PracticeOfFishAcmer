#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 1e9 + 7;
constexpr int N = 100;
constexpr double eps = 1e-6, M = 1e5;
typedef std::array<double, 3> point;

int n = 0;
point a[N];

double dis(const point &u, const point &v) {
    double len = 0;
    for (int i = 0; i < 3; i++) {
        len += (u[i] - v[i]) * (u[i] - v[i]);
    }
    return len;
}

double max(const point &p) {
    double res = 0;
    for (int i = 0; i < n; i++) {
        res = std::max(res, dis(p, a[i]));
    }
    return res;
}

double work(point p, int id) {
    if (id == 3) {
        return max(p);
    }
    auto l = p, r = p;
    l[id] = -M, r[id] = M;
    double ans = 0;
    while (r[id] - l[id] > eps) {
        double len = (r[id] - l[id]) / 3.0;
        auto m1 = l, m2 = r;
        m1[id] = l[id] + len;
        m2[id] = r[id] - len;
        
        double d1 = work(m1, id + 1), d2 = work(m2, id + 1);
        ans = std::min(d1, d2);
        if (d1 > d2) {
            l = m1;
        }
        else {
            r = m2;
        }
    }
    return ans;
}

void solve() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    std::cout << std::fixed << std::setprecision(6) << sqrt(work({ 0, 0, 0 }, 0)) << '\n';

    return;
}

int main () {
    int _t = 1;
    while (_t--) {
        solve();
    }

    system("pause");
    return 0;
}
