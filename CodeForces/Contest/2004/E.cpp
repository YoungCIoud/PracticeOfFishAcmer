#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e7, M = 1e5;
vct<int> sg(N + 5, 0);
// sg[1] = 1
// sg[a] = 0 (a % 2 == 0)
// sg[p_i] = i (i != 1) p is a sorted array of primes, with index started from 1
// otherwise sg[n] = sg[p_j], where p_j is the minimun prime factor of n

void solve()
{
    int n = 0;
    std::cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int a = 0;
        std::cin >> a;
        ans ^= sg[a];
    }
    
    if (ans) std::cout << "Alice\n";
    else std::cout << "Bob\n";
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;

    vct<bool> not_p(N + 5, false);
    vct<int> prime;
    sg[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!not_p[i])
        {
            prime.push_back(i);
            sg[i] = prime.size();
            if (i == 2) sg[i] = 0;
        }

        for (int &p : prime)
        {
            if (i * p > N) break;
            not_p[i * p] = true;
            sg[i * p] = sg[p];
            if (i % p == 0) break;

        }
    }

    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}