#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 30, Inf = 1e18;
int a[N + 5];
int dp[N + 5][N + 5];
int root[N + 5][N + 5];

void print(int l, int r)
{
	if (l > r) return;
	cout << root[l][r] << " ";
	print(l, root[l][r] - 1);
	print(root[l][r] + 1, r);
}

signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int len = 1; len <= n; len++)
	{
		for (int i = 1, j = i + len - 1; j <= n; i++, j++)
		{
			if (a[i] + dp[i + 1][j] > a[j] + dp[i][j - 1])
			{
				dp[i][j] = a[i] + dp[i + 1][j];
				root[i][j] = i;
			}
			else
			{
				dp[i][j] = a[j] + dp[i][j - 1];
				root[i][j] = j;
			}
			for (int r = i + 1; r < j; r++)
			{
				if (dp[i][j] < a[r] + dp[i][r - 1] * dp[r + 1][j])
				{
					dp[i][j] = a[r] + dp[i][r - 1] * dp[r + 1][j];
					root[i][j] = r;
				}
			}
		}
	}
	cout << dp[1][n] << endl;
	print(1, n);
	return 0;
}
