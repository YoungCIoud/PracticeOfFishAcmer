#include<bits/stdc++.h>
#define int unsigned long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 3e3, M = 1e5, Inf = 1e16, Mod = 1e9 + 7;
int pre[N + 5], dp[N + 5][N + 5], same[N + 5][N + 5];
void solve()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		pre[i] = pre[i - 1] + a;
	}
	for (int i = 1; i <= n; i++)
	{
		dp[i][1] = 1;
		for (int j = 2; j <= i; j++)
		{
			same[j][pre[i - 1] % j] += dp[i - 1][j - 1];
			same[j][pre[i - 1] % j] %= Mod;
		}

		for (int j = 2; j <= i; j++)
		{
			dp[i][j] += same[j][pre[i] % j];
			dp[i][j] %= Mod;
			// same[j][pre[i] % j] 相当于对dp[k][j - 1]的求和
			//for (int k = j - 1; k < i; k++)
			//{
			//	if ((pre[i] - pre[k]) % j == 0)
			//	{
			//		dp[i][j] = (dp[i][j] + dp[k][j - 1]) % Mod;
			//	}
			//}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = (ans + dp[n][i]) % Mod;
	}
	cout << ans << endl;
}

signed main()
{
	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
