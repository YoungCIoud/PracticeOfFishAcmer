#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, Inf = 1e18, Mod = 998244353;
// 到第i个数时的最大值/最小值
int dp[N + 5][2];

void solve()
{
	int n; cin >> n;
	for (int i = 1, a; i <= n; i++)
	{
		cin >> a;
		// minmum
		dp[i][0] = dp[i - 1][0] + a;

		// maximum
		dp[i][1] = max(dp[i - 1][1] + a, abs(dp[i - 1][0] + a));
	}
	cout << dp[n][1] << endl;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
