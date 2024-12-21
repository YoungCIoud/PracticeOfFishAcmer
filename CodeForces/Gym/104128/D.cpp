// 最多操作一次，要使序列第 K 大的值最大。
// 操作是选一段长度为 m 的子段， 加一个等差数列上去。
// 维护一个对顶堆
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

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 2e5, M = 2e5;
int n = 0, k = 0, m = 0;
i64 c = 0, d = 0;
std::vector a(N, 0ll);
std::vector pre(N + 1, 0);

bool chk(i64 x) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        pre[i] = 0;
        if (a[i] >= x) {
            cnt++;
        }
    }
    if (cnt >= k) {
        return true;
    }

    for (int i = 0; i < n; i++) {
        if (a[i] < x && a[i] + c + d * std::min(m - 1, i) >= x) {
            pre[std::max(i, m - 1)]++;
            if (a[i] + c >= x) {
                pre[std::min(n, i + m)]--;
            }
            else {
                pre[std::min(n, i + m - int((x - a[i] - c + d - 1ll) / d))]--;
            }
        }
    }
    
    for (int i = m - 1; i < n; i++) {
        cnt += pre[i];
        if (cnt >= k) {
            return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d%d%d%lld%lld", &n, &k, &m, &c, &d);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    i64 l = 0, r = Inf;
    while (l <= r) {
        i64 mid = l + r >> 1;
        if (chk(mid)) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    printf("%lld\n", r);

    sp();

    return 0;
}