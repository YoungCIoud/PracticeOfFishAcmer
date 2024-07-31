// 怎么dp也玄学了起来
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr int Mod = 998244353, Inf = 1e9, N = 80, M = 1e4;
int main()
{
	IOS;
	int n, x, y;
	std::cin >> n >> x >> y;
	vct dp(n + 1, vct<int>(x + 1, Inf));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int a, b;
		std::cin >> a >> b;
		for (int j = i; j; j--)
			for (int k = x; k >= a; k--)
				dp[j][k] = std::min(dp[j][k], dp[j - 1][k - a] + b);
	}

	for (int i = n; i >= 0; i--)
		for (int j = 0; j <= x; j++)
			if (dp[i][j] <= y)
			{
				std::cout << std::min(i + 1, n);
				get AC;
			}
} 
