#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e13;
constexpr int N = 100, T = 13, VAL = 1e9;

void solve()
{
	int n = 0, k = 0;
	std::cin >> n >> k;
	std::vector val(n + 1, 0ll);
	std::vector t(n + 1, 0);
	int D = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> val[i] >> t[i];
		D += 2 * t[i];
	}

	std::vector dp(2, std::vector(k + 1, std::vector(D * 2 + 1, -Inf)));
	dp[0][0][D] = 0;

	std::function chk = [&](int num) -> bool {
		return -D <= num && num <= D;
	};
	for (int i = 1, u = 1, v = 0; i <= n; i++, u ^= 1, v ^= 1) {
		for (int j = 0; j <= std::min(i, k); j++) {
			for (int s = -D; s <= D; s++) {
				dp[u][j][D + s] = dp[v][j][D + s];
				if (chk(s + t[i])) {
					dp[u][j][D + s] = std::max(dp[u][j][D + s], dp[v][j][D + s + t[i]] + val[i]);
				}
				if (chk(s - t[i])) {
					dp[u][j][D + s] = std::max(dp[u][j][D + s], dp[v][j][D + s - t[i]] + val[i]);
				}
			}

			if (j > 0) {
				t[i] *= 2;
				for (int s = -D; s <= D; s++) {
					if (chk(s + t[i])) {
						dp[u][j][D + s] = std::max(dp[u][j][D + s], dp[v][j - 1][D + s + t[i]] + val[i]);
					}
					if (chk(s - t[i])) {
						dp[u][j][D + s] = std::max(dp[u][j][D + s], dp[v][j - 1][D + s - t[i]] + val[i]);
					}
				}
			}
		}
	}

	i64 ans = 0;
	for (int i = 0; i <= k; i++) {
		ans = std::max(ans, dp[n & 1][i][D]);
	}
	std::cout << ans << '\n';

}

int main()
{
	// IOS;
	int t = 1;
	// std::cin >> t;
	
	while (t--)
	{
		solve();
	}

	system("pause");

	return 0;
}