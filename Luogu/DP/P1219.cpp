#include<iostream>
using namespace std;
int w[355], cnt[5];
int dp[45][45][45][45];

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1; i <= m; i++)
	{
		int t; cin >> t;
		cnt[t]++;
	}
	dp[0][0][0][0] = w[1];
	for (int a = 0; a <= cnt[1]; a++)
		for (int b = 0; b <= cnt[2]; b++)
			for (int c = 0; c <= cnt[3]; c++)
				for (int d = 0; d <= cnt[4]; d++)
				{
					int pos = 1 + a + b * 2 + c * 3 + d * 4;
					if (a) dp[a][b][c][d] = max(dp[a - 1][b][c][d] + w[pos], dp[a][b][c][d]);
					if (b) dp[a][b][c][d] = max(dp[a][b - 1][c][d] + w[pos], dp[a][b][c][d]);
					if (c) dp[a][b][c][d] = max(dp[a][b][c - 1][d] + w[pos], dp[a][b][c][d]);
					if (d) dp[a][b][c][d] = max(dp[a][b][c][d - 1] + w[pos], dp[a][b][c][d]);
				}
	cout << dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]];
	return 0;
}
