#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e2, M = 1e5, Inf = 1e16, Mod = 1e9 + 7;
bool dp[M + 5];
int a[N + 5];
signed main()
{
	int n, sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sum += a[i];
	}

	// 前i个数能否组合出j
	dp[0] = true;
	for (int i = 1; i <= n; i++)
	{
		for (int j = sum; j - a[i] >= 0; j--)
		{
			dp[j] |= dp[j - a[i]];
			//if (dp[j]) cout << j << "ok\n";
		}
	}
	int ans = Inf;
	for (int i = 1; i <= sum; i++)
	{
		if (!dp[i]) continue;

		int mx = max(i, sum - i);
		if (mx < ans) ans = mx;
	}
	cout << ans << endl;
	return 0;
}
