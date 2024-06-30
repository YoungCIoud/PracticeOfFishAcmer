#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 100, Inf = 1e18, Mod = 998244353;

int dp[N + 5][N + 5];

void solve()
{
	string a, b;
	cin >> a >> b;
	int la = a.length(), lb = b.length();
	a = "*" + a;
	b = "*" + b;
	for (int i = 1; i <= la; i++)
		for (int j = 1; j <= lb; j++)
			dp[i][j] = 0;

	for (int i = 1; i <= la; i++)
	{
		for (int j = 1; j <= lb; j++)
		{
			if (a[i] == b[j])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			// else dp[i][j] = max(dp[i][j - 1], dp[i - 1][j])
			else dp[i][j] = dp[i - 1][j]; //保证了a是连续的
		}
	}
	int mx = 0;
	for (int i = 1; i <= lb; i++)
		mx = max(mx, dp[la][i]);
	cout << la + lb - mx << endl;
	return;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
