#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

struct event
{
    bool arrival;
    int idx;
    i64 time;
};

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    vct<i64> x(m + 1, 0), last(n + 1, 0);
    std::cin >> x[1];

    vct<event> e{};
    vct<int> A(m + 1), B(m + 1);
    for (int i = 1; i <= m; i++)
    {
        int S = 0, T = 0;
        std::cin >> A[i] >> B[i] >> S >> T;
        e.push_back({ false, i, S});
        e.push_back({ true, i, T});
    }
    sort (e.begin(), e.end(), [](event a, event b)
    {
        if (a.time != b.time) return a.time < b.time;
        if (a.arrival ^ b.arrival) return a.arrival;
        return a.idx < b.idx; 
    });

    for (auto [arrival, idx, time] : e)
    {
        if (arrival)
            last[B[idx]] = std::max(last[B[idx]], time + x[idx]);
        else
            x[idx] = std::max(x[idx], last[A[idx]] - time);
    }

    for (int i = 2; i <= m; i++) std::cout << x[i] << ' ';
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}