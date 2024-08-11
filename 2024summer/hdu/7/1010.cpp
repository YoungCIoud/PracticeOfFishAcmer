#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e9;

void solve()
{
    int n = 0, x = 0, k = 0;
    std::cin >> n >> x >> k;
    vct<int> a(n);

    for (auto& i : a) std::cin >> i;

    std::priority_queue<int> q;
    i64 sum = 0, i = 0;
    for (i = 0; i < n && sum < x; i++)
    {
        sum += a[i];
        q.push(a[i]);
        while (sum >= x && k > 0)
        {
            k--;
            sum -= q.top();
            q.pop();
        }
        if (sum >= x)
            break;
    }

    std::cout << i << '\n';

    return ;
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

    //system("pause");

    return 0;
}