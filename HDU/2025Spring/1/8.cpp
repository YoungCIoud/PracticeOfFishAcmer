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

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, MAX = 1e4;
const double EPS = 1e-7, PI = acos(-1.0);

using point = std::array<double, 2>;
std::array<i64, 2> b[N + 5];
point a[N + 5];

double dis2(point &u, point &v) {
    double x = u[0] - v[0], y = u[1] - v[1];
    return x * x + y * y;
}

point cen(point &u, point &v) {
    return { (u[0] + v[0]) / 2.0, (u[1] + v[1]) / 2.0 };
}
point cen(point &u, point &v, point &w) {
    auto &[x1, y1] = u;
    auto &[x2, y2] = v;
    auto &[x3, y3] = w;

    double A = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1, B = x3 * x3 + y3 * y3 - x1 * x1 - y1 * y1;  
    double x = (A * (y3 - y1) - B * (y2 - y1)) / (2.0 * (x2 - x1) * (y3 - y1) - 2.0 * (x3 - x1) * (y2 - y1));
    double y = (A * (x3 - x1) - B * (x2 - x1)) / (2.0 * (y2 - y1) * (x3 - x1) - 2.0 * (y3 - y1) * (x2 - x1));
    return { x, y };
}

i64 area(std::array<i64, 2> &u, std::array<i64, 2> &v, std::array<i64, 2> &w) { 
    return std::abs((u[0] * (v[1] - w[1]) + v[0] * (w[1] - u[1]) + w[0] * (u[1] - v[1])));
}

void solve() {
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> b[i][0] >> b[i][1];
        a[i][0] = b[i][0], a[i][1] = b[i][1];
    }
    double Sr = 0;
    // for (int i = 0; i < n; i++) {
    //     int j = (i + 1) % n;
    //     Sr += (b[i][0] * b[j][1] - b[j][0] * b[i][1]);
    // }
    for (int i = 2; i < n; i++) {
        Sr += area(b[0], b[i - 1], b[i]);
    }
    Sr /= 2.0;

    std::random_shuffle(a, a + n);
    point O = a[0];
    double r = 0;
    for (int i = 1; i < n; i++) {
        if (dis2(O, a[i]) - r <= EPS) {
            continue;
        }

        O = a[i], r = 0;
        
        for (int j = 0; j < i; j++) {
            if (dis2(O, a[j]) - r <= EPS) {
                continue;
            }
            
            O = cen(a[i], a[j]), r = dis2(O, a[j]);
            for (int k = 0; k < j; k++) {
                if (dis2(O, a[k]) - r <= EPS) {
                    continue;
                }
                
                O = cen(a[i], a[j], a[k]), r = dis2(O, a[i]);
            }
        }
    }
    
    std::cout << std::fixed << std::setprecision(6) << (PI * r - Sr) / (2.0 * PI * std::sqrt(r)) << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    return 0;
}
