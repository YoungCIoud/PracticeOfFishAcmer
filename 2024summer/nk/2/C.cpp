// 原来这还能dp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 3e3, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;
signed main()
{
	int n;
	cin >> n;
	string s[2];
	cin >> s[0] >> s[1];
	array<int, 2> dp{};
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[0][i] == 'R')
			dp[0]++;
		else
			dp[0] = 0;
		if (s[1][i] == 'R')
			dp[1]++;
		else
			dp[1] = 0;

		if (s[0][i] == 'R' && s[1][i] == 'R')
			dp = { max(dp[0], dp[1] + 1), max(dp[1], dp[0] + 1) };

		ans = max({ans, dp[0], dp[1]});
	}
	cout << max(0ll, ans - 1) << endl;
	return 0;
}
