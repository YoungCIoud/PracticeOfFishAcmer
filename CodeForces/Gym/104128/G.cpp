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
    int power = 1, num = 1, cnt = 0;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        if (a == 1) {
            power++;
            num++;
        }
        else if (a == -1) {
            num--;
        }
        else if (num > 1) {
            num--;
            cnt++;
        }
        else {
            power++;
            num++;
        }
        if (num <= 0) {
            if (cnt >= 1) {
                cnt--;
                power++;
                num += 2;
            }
            else {
                num = -n;
            }
        }
    }

    if (num > 0) {
        int g = std::__gcd(power, num);
        std::cout << power / g << ' ' << num / g << '\n';
    }
    else {
        std::cout << -1 << '\n';
    }
    return;
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}