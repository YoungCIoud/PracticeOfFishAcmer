#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
// n^2将符合条件的区间维护出来
// dp[i][k] 第i个数是第k个区间的右括号
const int N = 3000, K = 20, Inf = 1e18;
int dp[N + 5][K + 5], a[N + 5], pre[N + 5], pref[N + 5][N + 5];
bool ok[N + 5][N + 5];

signed main()
{
	int n, k, x;
	cin >> n >> k >> x;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		pre[i] = pre[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++ )
			if (pre[j] - pre[i - 1] == x)
				ok[i][j] = 1;

		for (int j = 0; j <= k; j++)
			dp[i][j] = Inf;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + ok[i][j];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= min(i, k); j++)
			for (int m = j - 1; m < i; m++)
				dp[i][j] = min(dp[i][j], dp[m][j - 1] + pref[i][i] + pref[m][m] - pref[i][m] - pref[m][i]);
	cout << dp[n][k];
	return 0;
}
