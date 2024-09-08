#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 120, M = 1e5;

// 母函数
int c1[N +  5], c2[N + 5];

int main()
{
    for (int i = 0; i <= N; i++)
        c1[i] = 1, c2[i] = 0;
    
    for (int k = 2; k <= N; k++)
    {
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= N; j += k)
                c2[i + j] += c1[i];
        for (int i = 0; i <= N; i++)
            c1[i] = c2[i], c2[i] = 0;
    }
    
    int n = 0;
    while (std::cin >> n)
        std::cout << c1[n] << '\n';
}


// dp 
// // dp[i][j]将i划分成最大数不超多j的方案数
// i64 dp[N + 5][N + 5];

// int main()
// {
//     for (int i = 1; i <= N; i++)
//     {
//         for (int j = 1; j <= N; j++)
//         {
//             if (i == 1 || j == 1) dp[i][j] = 1;
//             else if (i < j) dp[i][j] = dp[i][i];
//             else if(i == j) dp[i][j] = dp[i][j - 1] + 1;
//             else dp[i][j] = dp[i - j][j] + dp[i][j - 1];
//         }
//     }
    
//     int n = 0;
//     while (std::cin >> n)
//         std::cout << dp[n][n] << '\n';

//     system("pause");

//     return 0;
// }