// 这个转化太牛了
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using i64 = long long;
const int Mod = 998244353;

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	// 未经过优化的转移
	//std::vector f(n + 1, std::vector(n + 1, std::vector<int>(n + 1)));
	//f[0][0][0] = 1;
	//int ans = 0;
	//for (int i = 1; i <= n; i++)
	//	for (int j = 1; j <= n; j++)
	//		for (int k = 1; k <= n; k++)
	//			if (a[i] == a[j] && a[i] == a[k])
	//			{
	//				for (int ii = 0; ii < i; ii++)
	//					for (int jj = 0; jj < j; jj++)
	//						for (int kk = 0; kk < k; kk++)
	//							f[i][j][k] = f[i][j][k] + f[ii][jj][kk];
	//				ans += f[i][j][k];
	//			}
	//std::cout << ans << '\n';
	std::vector dp(n + 1, std::vector(n + 1, std::vector<i64>(n + 1)));
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			for(int k = 0; k <= n; k++)
				if (i == 0 || j == 0 || k == 0)
				{
					dp[i][j][k] = 1;
				}
				else
				{
					dp[i][j][k] = (a[i] == a[j] && a[i] == a[k]) ? dp[i - 1][j - 1][k - 1] : 0;
					dp[i][j][k] += dp[i][j][k - 1] + dp[i][j - 1][k] + dp[i - 1][j][k];
					dp[i][j][k] -= dp[i][j - 1][k - 1] + dp[i - 1][j][k - 1] + dp[i - 1][j - 1][k];
					dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - 1][k - 1]) % Mod;
				}
	std::cout << (dp[n][n][n] - 1 + Mod) % Mod << '\n';
	return 0;
}
