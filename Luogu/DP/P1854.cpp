#include<iostream>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 100, Inf = 0x3f3f3f3f;
ll dp[N + 5][N + 5];
// 第i种花放在第j个瓶子里取得的最大值
ll mp[N + 5][N + 5];
int las[N + 5][N + 5];
int route[N + 5];

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> mp[i][j];
			dp[i][j] = -Inf;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= m - (n - i); j++)
		{
			for (int k = i - 1; k < j; k++)
			{
				if (dp[i][j] < dp[i - 1][k] + mp[i][j])
				{
					dp[i][j] = dp[i - 1][k] + mp[i][j];
					las[i][j] = k;
				}
			}
		}
	}
	// puts("dp ok");
	int ind = 1;
	for (int i = 1; i <= m; i++)
	{
		if (dp[n][ind] < dp[n][i])
		{
			ind = i;
		}
	}
	cout << dp[n][ind] << endl;
	for (int i = 1; i <= n; i++)
	{
		route[i] = ind;
		ind = las[n - i + 1][ind];
	}
	for (int i = n; i; i--)
	{
		cout << route[i] << " ";
	}
	return 0;
}
