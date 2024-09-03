#include<bits/stdc++.h>

int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<int> dis(n);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> dis[i % n];
        dis[i % n] %= m;
    }
    
    std::vector<int> q(n, 0), cnt(m, 0);
    cnt[0]++;
    for (int i = 1; i < n; i++)
    {
        q[i] = (q[i - 1] + dis[i]) % m;
        cnt[q[i]]++;
    }

    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        cnt[q[i]]--;
        ans += cnt[q[i]];

        q.push_back((q.back() + dis[i]) % m);
        cnt[q.back()]++;
    }

    std::cout << ans << '\n';

    system("pause");
    return 0;
}