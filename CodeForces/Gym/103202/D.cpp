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
int n = 0;
int cnt = 0;
std::vector<int> p;

void print(std::vector<int> &v) {
        cnt++;
        for (auto &i : v) {
            std::cout << (i ? 'r' : 'b');
        }
        std::cout << '\n';
}

// lst 最后一个 1 的位置
// tot 目前为止一共有多少个 1
// d 目前前缀数组中 偶数个数 - 奇数个数
void dfs(int lst, int tot, int d) {
    if (cnt >= 100 || (n - lst + 1) * 2 < std::min(abs(d + 1), abs(d - 1))) {
        return;
    }
    if (-1 <= d && d <= 1) {
        print(p);
    }

    for (int i = n - 1; i > lst; i--) {
        if (tot & 1) {
            p[i] = 1;
            dfs(i, tot + 1, d + 2 * (n - i));
            p[i] = 0;
        }
        else {
            p[i] = 1;
            dfs(i, tot + 1, d - 2 * (n - i));
            p[i] = 0;
        }
    }
    return;
}

int main()
{
    IOS;

    std::cin >> n;
    i64 mx = (n + 1) / 2;
    if (n & 1) {
        std::cout << mx * mx << '\n';
    }
    else {
        std::cout << mx * (mx + 1ll) << '\n';
    }
    if (n == 1) {
        std::cout << 'r' << '\n';
    }
    else {
        p.assign(n, 0);
        p[n / 2] = 1;
        print(p);
        p[n / 2] = 0;
        p[n / 2 - 1] = 1;
        if (!(n & 1)) {
            print(p);
        }
        // 抽象至极的减枝
        for (int i = n - 1; i > n / 2 - 1 && cnt < 100; i--) {
            if (i + 2 < n) {
                p[i + 2] = 0;
            }
            p[i] = 1;
            print(p);
        }

        for (int i = -1; i < 2 && n / 2 + i < n; i++) {
            p[n / 2 + i] = 0;
        }
        for (int i = n / 2 - 2; ~i; i--) {
            p[i] = 1;
            dfs(i, 1, n + 1 - 2 * (n - i));
            p[i] = 0;
        }
    }

    system("pause");

    return 0;
}