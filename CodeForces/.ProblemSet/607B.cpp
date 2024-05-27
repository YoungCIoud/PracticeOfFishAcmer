#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 500, X = 40, Inf = (1ll << 31) - 1;
int a[N + 5], dp[N + 5][N + 5];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		dp[i][i] = 1;
	}
	for (int i = 1; i < n; i++)
	{
		dp[i][i + 1] = a[i] == a[i + 1] ? 1 : 2;
	}
	for (int l = 3; l <= n; l++)
	{
		for (int i = 1, j = i + l - 1; j <= n; i++, j++)
		{
			dp[i][j] = Inf;
			if (a[i] == a[j])
			{
				dp[i][j] = dp[i + 1][j - 1];
			}
			for (int k = i; k < j; k++)
			{
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}
		}
	}
	// cout << dp[4][6] << endl;
	cout << dp[1][n];
	return 0;
}
