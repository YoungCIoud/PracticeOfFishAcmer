#include<bits/stdc++.h>

constexpr int N = 1e5;

int main()
{
    std::vector<int> pri(0);
    std::vector not_p(N + 5, false);

    for (int i = 2; i <= N; i++)
    {
        if (!not_p[i]) pri.push_back(i);

        for (auto& p : pri)
        {
            if (p * i > N) break;
            not_p[p * i] = true;

            if (i % p == 0) break;
        }
    }

    int n = 0, ans = 0;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x = 0;
        std::cin >> x;

        // 对x所分解出来的质因数的个数进行计数
        int cnt = 0;
        for (int& p : pri)
        {
            if (p > x) continue;
            
            while (x % p == 0)
            {
                cnt++;
                x /= p;
            }
        }

        ans ^= cnt;
    }

    std::cout << (ans ? "Anna" : "Bruno") << '\n';

    system("pause");

    return 0;
}