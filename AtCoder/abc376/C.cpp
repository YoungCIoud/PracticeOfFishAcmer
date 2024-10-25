#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::priority_queue<int> qa, qb;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        qa.push(a);
    }
    for (int i = 1; i < n; i++) {
        int b = 0;
        std::cin >> b;
        qb.push(b);
    }

    int ans = 0;
    while (not qb.empty()) {
        int siz = qa.top();
        qa.pop();
        
        int vol = qb.top();
        qb.pop();

        if (vol < siz) {
            if (ans == 0) {
                ans = siz;
                qb.push(vol);
            }
            else {
                ans = -1;
            }
        }
    }

    std::cout << (qa.empty() ? ans : qa.top()) << '\n';

    return;
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}