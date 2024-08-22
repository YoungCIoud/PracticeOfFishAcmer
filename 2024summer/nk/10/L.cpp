#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e9;
constexpr int N = 5, M = 50;

// 从0可到达的所有状态
vct dis(N + 1, vct(2, vct<int>(0)));

int main()
{
    // 预处理出dis
    for (int i = 1, mx = 10; i <= N; i++, mx *= 10)
    {
        dis[i][0].assign(mx, Inf);
        dis[i][1].assign(mx, Inf);

        dis[i][0][0] = 0;
        std::queue<ary<int, 2>> q;
        q.push({ 0, 0 });
        while (not q.empty())
        {
            // 当前状态 用了奇数步还是偶数步
            auto [s, d] = q.front();
            q.pop();

            // 枚举一次操作后所有的次态
            for (int l = 0; l < i; l++)
            {
                for (int r = l; r < i; r++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        int nex = 0;
                        for (int p = 0, pw = 1; p < i; p++, pw *= 10)
                        {   // 当前位的数字
                            int digit = s / pw % 10;
                            if (l <= p && p <= r)
                                digit = (digit + (k ? 1 : 9)) % 10;

                            nex += digit * pw;
                        }

                        if (dis[i][d ^ 1][nex] > dis[i][d][s] + 1)
                        {
                            dis[i][d ^ 1][nex] = dis[i][d][s] + 1;
                            q.push({ nex, d ^ 1});
                        }
                    }
                }
            }
        }
    }

    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        int n = 0, m = 0;
        std::cin >> n >> m;
        vct<ary<int, 2>> infor(m, { 0, 0 });
        for (auto& [x, y] : infor)  std::cin >> x >> y;

        vct<int> ans{};

        int mx = pow(10, n);
        // 枚举所有的状态
        for (int i = 0; i < mx; i++)
        {
            bool flag = true;
            for (auto& [s, d] : infor)
            {
                // 从s到i,相当于从0到nex
                int nex = 0;
                for (int p = 0, pw = 1; p < n; p++, pw *= 10)
                {
                    int digit = i / pw % 10 - s / pw % 10;
                    digit = (digit + 10) % 10;
                    nex += digit * pw;
                }

                if (dis[n][d & 1][nex] > d)
                {
                    flag = false;
                    break;
                }
            }
            if (flag) ans.push_back(i);
        }

        if (ans.empty())
        {
            std::cout << "IMPOSSIBLE\n";
        }
        else if (ans.size() == 1)
        {
            str s = std::to_string(ans[0]);
            while (s.size() < n) s = '0' + s;
            std::cout << s << '\n';
        }
        else
        {
            std::cout << "MANY\n";
        }
    }

    system("pause");

    return 0;
}