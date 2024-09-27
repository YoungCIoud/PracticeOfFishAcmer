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
    auto ask =[&](std::string s) -> bool {
        std::cout << "? " << s << '\n';
        int a = 0;
        std::cin >> a;
        return a == 1;
    };
    if (n == 1) {
        if (ask("1")) {
            std::cout << "! 1\n";
        }
        else {
            std::cout << "! 0\n";
        }
    }
    else if (ask("00")) {
        std::string ans = "00";
        while (ans.size() < n) {
            if (ask(ans + "0")) {
                ans += "0";
            }
            else if (ask(ans + "1")) {
                ans += "1";
            }
            else {
                break;
            }
        }
        while (ans.size() < n) {
            if (ask("0" + ans)) {
                ans = "0" + ans;
            }
            else if (ask("1" + ans)) {
                ans = "1" + ans;
            }
            else {
                break;
            }
        }
        std::cout << "! " << ans << '\n';
    }
    else if (ask("01")) {
        std::string ans = "01";
        while (ans.size() < n) {
            if (ask(ans + "1")) {
                ans += "1";
            }
            else if (ans.back() == '1' && ask(ans + "0")) {
                ans += "0";
            }
            else {
                break;
            }
        }
        while (ans.size() < n) {
            if (ask("1" + ans)) {
                ans = "1" + ans;
            }
            else if (ans.front() == '1' && ask("0" + ans)) {
                ans = "0" + ans;
            }
            else {
                break;
            }
        }
        std::cout << "! " << ans << '\n';
    }
    else if (ask("10")) {
        if (ask(std::string(n - 1, '1') + "0")) {
            std::cout << "! " << std::string(n - 1, '1') + "0" << '\n';
        }
        else {
            std::cout << "! " << std::string(n, '1') << '\n';
        }
    }
    else {
        std::cout << "! " << std::string(n, '1') << '\n';
    }
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}