#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 100, X = 40, Inf = (1ll << 31) - 1;
int n;
ll dp[N * 2 + 5][N * 2 + 5];
// 下标i所指的坐标表示第i颗珠子的头
ll a[N * 2 + 5];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i + n] = a[i];
	}
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1, j = i + l - 1; j < 2 * n; i++, j++)
		{
			dp[i][j] = -Inf;
			for (int k = i; k < j; k++)
			{
				dp[i][j] = max(dp[i][j], a[i] * a[k + 1] * a[j + 1] + dp[i][k] + dp[k + 1][j]);
			}
			//printf("dp[%d][%d]=%lld\n", i, j, dp[i][j]);
		}
	}

	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = max(ans, dp[i][i + n - 1]);
	}
	cout << ans;
	return 0;
}
