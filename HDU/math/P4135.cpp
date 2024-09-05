#include<bits/stdc++.h>

using i64 = long long;
int prime[10], num;
void trans(i64 n)
{
    num = 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i) continue;

        prime[num++] = i;
        while (n % i == 0) n /= i;
    }
    if (n != 1) prime[num++] = n;
}

i64 cnt(i64 n)
{
    i64 res = 0;
    for (int i = 1; i < (1 << num); i++)
    {
        i64 p = 1;
        int cnt = 0;
        for (int j = 0; j < num; j++)
        {
            if ((i >> j) & 1)
            {
                p *= prime[j];
                cnt++;
            }
        }
        if (cnt & 1) res += n / p;
        else res -= n / p;
    }
    return n - res;
}

int main()
{
    int t = 1;
    std::cin >> t;
    for (int i = 1; i <= t; i++)
    {
        i64 a = 0, b = 0, n = 0;
        std::cin >> a >> b >> n;

        trans(n);
        std::cout << "Case #" << i << ": " << cnt(b) - cnt(a - 1) << '\n';
    }
    return 0;
}