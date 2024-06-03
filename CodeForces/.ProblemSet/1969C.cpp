#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 3e5, K = 10, Inf = 1e18;

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(n + 1, Inf);
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, Inf));
	dp[0][0] = 0;
	// 用d次操作, 可以将一段长度为d + 1的数字化成其中最小的
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= k; j++)
		{
			int mn = Inf;
			for (int d = 0; i + d < n && j + d <= k; d++)
			{
				mn = min(mn, a[i + d + 1]);
				dp[i + d + 1][j + d] = min(dp[i + d + 1][j + d], dp[i][j] + mn * (d + 1));
			}
		}
	}

	cout << *min_element(dp[n].begin(), dp[n].end()) << endl;
}

signed main()
{
	int t;
	cin >> t;
	//puts("ok");
	while (t--)
	{
		solve();
	}
	return 0;
}
