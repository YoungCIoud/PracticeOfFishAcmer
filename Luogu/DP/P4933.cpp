#include<iostream>
using namespace std;
const int Mod = 998244353, N = 1e3, V = 2e4;
int a[N + 5];
int dp[N + 5][V * 2 + 5];

signed main()
{
	int n; cin >> n;
	int ans = n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		for (int j = 1; j < i; j++)
		{
			dp[i][V + a[i] - a[j]] = (dp[i][V + a[i] - a[j]] + dp[j][V + a[i] - a[j]] + 1) % Mod;
			ans = (ans + dp[j][V + a[i] - a[j]] + 1) % Mod;
			//cout << j << " " << i << endl;
		}
	}
	cout << ans;
	return 0;
}
