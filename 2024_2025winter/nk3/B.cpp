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
constexpr int N = 1e5, M = 2e5, Inf = 1e9;
bool vis[M + 5];

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }

    int idx = -1;
    std::deque<int> q;
    for (int i = 0, j = 0; i < n && idx == -1; i++) {
        while (j - i < n) {
            while (not q.empty() && not vis[a[q.back() % n] + a[j % n]]) {
                q.pop_back();
            }
            q.push_back(j);
            j++;
        }
        while (not q.empty() && q.front() < i) {
            q.pop_front();
        }

        if (q.size() == 1) {
            idx = i;
        }
    }

    if (~idx) {
        std::cout << "Yes\n";
        int r = idx;
        std::stack<int> stk;
        while (r - idx < n) {
            while (not stk.empty() && not vis[a[stk.top() % n] + a[r % n]]) {
                std::cout << stk.top() % n << ' ';
                stk.pop();
            }
            stk.push(r);
            r++;
        }
        std::cout << stk.top() % n << '\n';
    }
    else {
        std::cout << "No\n";
    }

    return;
}

int main()
{
    std::vector<int> pri;
    for (int i = 2; i <= M; i++) {
        if (not vis[i]) {
            pri.push_back(i);
        }
        for (auto &p : pri) {
            if (p * i > M) {
                break;
            }
            vis[p * i] = true;
            if (i % p == 0) {
                break;
            }
        }
    }

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