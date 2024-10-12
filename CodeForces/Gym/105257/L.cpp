#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;
void solve()
{
    i64 a = 0;
    std::cin >> a;
    for (int i = 2; true; i++) {
        if (a % i) {
            std::cout << i << '\n';
            return;
        }
    }
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