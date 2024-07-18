// 动态规划 思维
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 3e3, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;
int card[N + 5];
int dp[N + 5][N + 5];
int rng[N + 5][2];

signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= 2 * n; i++)
	{
		cin >> card[i];
		if (rng[card[i]][0])
			rng[card[i]][1] = i;
		else
			rng[card[i]][0] = i;
	}
	vector<int> ls(n + 1, 0);
	for (int i = 1; i <= n; i++) ls[i] = i;

	rng[0][0] = 0, rng[0][1] = n * 2 + 1;
	sort(ls.begin(), ls.end(), [](int x, int y) {
		return rng[x][1] - rng[x][0] < rng[y][1] - rng[y][0];
		});

	for (int i = 0; i <= n; i++)
	{
		int num = ls[i];
		auto [l, r] = rng[num];
		dp[l][l] = num;
		for (int j = l + 1; j <= r; j++)
		{
			dp[l][j] = dp[l][j - 1] + num;
			if (rng[card[j]][0] > l && rng[card[j]][1] == j)
			{
				dp[l][j] = max(dp[l][j], dp[l][rng[card[j]][0] - 1] + dp[rng[card[j]][0]][rng[card[j]][1]]);
			}
		}
		//cout << num << ":(" << l << "," << r << ") " << dp[l][r] << endl;
	}
	cout << dp[0][n * 2 + 1] << endl;
	return 0;
}
