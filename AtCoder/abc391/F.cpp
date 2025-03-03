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
constexpr int N = 2e5, M = 1e5, Inf = 1e9;

int n;
std::vector<i64> A(N + 5), B = A, C = A;

i64 f(std::array<int, 3> p) {
    i64 w = 1ll;
    i64 res = 0;
    for (int i = 0; i < 3; i++) {
        res += w * p[i];
        w *= n;
    }
    return res;
}

std::array<int, 3> g(i64 val) {
    std::array<int, 3> res;
    for (int i = 0; i < 3; i++) {
        res[i] = val % n;
        val /= n;
    }
    return res;
}

std::priority_queue<std::pair<i64, i64>> q;
std::set<i64> vis;

void add(std::array<int, 3> p) {
    i64 hp = f(p);
    if (p[0] < n && p[1] < n && p[2] < n && vis.count(hp) == 0) {
        q.push({ A[p[0]] * B[p[1]] + B[p[1]] * C[p[2]] + A[p[0]] * C[p[2]], hp });
        vis.insert(hp);
    }
}

void solve()
{
    int k = 0;
    std::cin >> n >> k;
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> B[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> C[i];
    }
    std::sort(A.begin(), A.begin() + n, std::greater<i64>());
    std::sort(B.begin(), B.begin() + n, std::greater<i64>());
    std::sort(C.begin(), C.begin() + n, std::greater<i64>());

    q.push({ A[0] * B[0] + B[0] * C[0] + C[0] * A[0], 0 });
    for (int i = 0; i < k; i++) {
        if (i == k - 1) {
            std::cout << q.top().first << '\n';
            break;
        }
        auto [x, y, z] = g(q.top().second);
        q.pop();
        add({ x + 1, y, z });
        add({ x, y + 1, z });
        add({ x, y, z + 1 });
    }
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