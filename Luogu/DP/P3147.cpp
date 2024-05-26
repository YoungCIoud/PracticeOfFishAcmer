#include<iostream>
#include <climits>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 1 << 18, X = 40, Inf = INT_MAX;
// 可合成的最大值为 40 + 18 = 58
int a[N + 5];
int dp[60][N + 5];
// dp[i][j] 合成i且最左边的数是j时最右边的数([j,dp[i][j]]正好可以合成i)

int main()
{
	int n;
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		dp[a[i]][i] = i;
		ans = max(ans, a[i]);
	}
	for (int i = 2; i <= 58; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (dp[i - 1][j] && dp[i - 1][dp[i - 1][j] + 1])
			{
				dp[i][j] = dp[i - 1][dp[i - 1][j] + 1];
				ans = max(ans, i);
			}
		}
	}
	cout << ans;
	return 0;
}
