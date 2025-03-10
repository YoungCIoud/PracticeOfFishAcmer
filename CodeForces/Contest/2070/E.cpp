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
constexpr int N = 3e5, M = 1e5, Inf = 1e9;

class BIT {
private:
    int n, d; // 因为会出现负数，所以这里有 d 的偏移
    std::vector<int> a;

    int lowbit(int x) {
        return x & -x;
    }
public:
    BIT(int _n, int _d = 0) {
        n = _n, d = _d;
        a.assign(n + d + 2, 0);
    }

    void add(int pos, int val) {
        pos += d;
        if (pos == 0) {
            return;
        }
        for (int i = pos; i <= n + d; i += lowbit(i)) {
            a[i] += val;
        }
        return;
    }

    int ask(int pos) {
        pos += d;
        int res = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            res += a[i];
        }
        return res;
    }
};

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;

    BIT tr(n, 3 * n);
    int sum = 0;
    tr.add(sum, 1);
    
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        sum += (s[i - 1] == '0' ? 1 : -3);
        ans += tr.ask(sum - 2);
        ans += tr.ask(sum + 1) - tr.ask(sum);
        tr.add(sum, 1);
    }
    
    std::cout << ans << '\n';
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