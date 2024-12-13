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

void solve()
{
    int n = 0;
    std::cin >> n;
    std::stack<int> stk, fron;
    std::vector<int> back;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        while (not stk.empty() && stk.top() > a) {
            back.push_back(stk.top());
            stk.pop();
        }
        if (stk.empty() || stk.top() <= a) {
            stk.push(a);
        }
        else {
            back.push_back(a);
        }
    }
    
    if (back.size() != 0)
        std::sort(back.begin(), back.end());
    while (not stk.empty()) {
        if (back.size() != 0 && stk.top() > back[0] + 1) {
            back.push_back(stk.top());
        }
        else {
            fron.push(stk.top());
        }
        stk.pop();
    }
    while (not fron.empty()) {
        std::cout << fron.top() << ' ';
        fron.pop();
    }
    if (back.size() != 0)
        std::sort(back.begin(), back.end());
    for (auto &i : back) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';
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

    sp();

    return 0;
}