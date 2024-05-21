#include<string>
#include<iostream>
using namespace std;
#define int long long
const int N = 1000, M = 200, Inf = 0x3f3f3f3f, Mod = 1e9 + 7;
int dp[2][M + 5][M + 5][2];

signed main()
{
	int n, m, sum;
	cin >> n >> m >> sum;
	string a, b;
	cin >> a >> b;
	dp[0][0][0][0] = dp[1][0][0][0] = 1;
	for(int i=1,pos=1;i<=n;i++,pos^=1)
		for(int j=1;j<=m;j++)
			for (int k = 1; k <= min(i, min(j, sum)); k++)
			{
				dp[pos][j][k][0] = (dp[pos ^ 1][j][k][0] + dp[pos ^ 1][j][k][1]) % Mod;
				if (a[i - 1] == b[j - 1])
					dp[pos][j][k][1] = dp[pos ^ 1][j - 1][k][1] + dp[pos ^ 1][j - 1][k - 1][0] + dp[pos ^ 1][j - 1][k - 1][1];
				else dp[pos][j][k][1] = 0;
				dp[pos][j][k][1] %= Mod;
			}
	cout << (dp[n & 1][m][sum][0] + dp[n & 1][m][sum][1]) % Mod;
	return 0;
}
