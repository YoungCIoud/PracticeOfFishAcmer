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
struct Node {
    std::array<int, 4> a;
    int id() {
        int res = 0;
        for (int i = 0; i < 4; i++) {
            res *= 10;
            res += a[i];
        }
        return res;
    }
};

int dis[N];
void init() {
    std::queue<Node> q;
    std::vector vis(N, false);
    q.push({ 0, 0, 0, 0 });
    vis[0] = true;
    while (not q.empty()) {
        auto cur = q.front();
        q.pop();

        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < 4; i++) {
                for (int j = i; j < 4; j++) {
                    Node to = cur;
                    for (int l = i; l <= j; l++) {
                        to.a[l] = (to.a[l] + (k ? 9 : 1)) % 10;
                    }
                    if (not vis[to.id()]) {
                        q.push(to);
                        vis[to.id()] = true;
                        dis[to.id()] = dis[cur.id()] + 1; 
                    }
                }
            }
        }
    }
}

void solve()
{
    std::string a{}, b{};
    std::cin >> a >> b;
    int res = 0;
    for (int i = 0; i < 4; i++) {
        b[i] = (b[i] - a[i] + 10) % 10;
        res *= 10;
        res += b[i];
    }
    std::cout << dis[res] << '\n';
}

int main()
{
    init();
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}