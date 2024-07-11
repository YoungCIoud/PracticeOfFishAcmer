#include<bits/stdc++.h>
//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 500, Inf = 1e18, Mod = 998244353;
int a[N + 5][N + 5], b[N + 5][N + 5];
bool solve()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		getchar();
		for (int j = 1; j <= m; j++)
		{
			int c = int(getchar());
			a[i][j] = c & 3;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		getchar();
		for (int j = 1; j <= m; j++)
		{
			int c = int(getchar());
			b[i][j] = c & 3;
		}
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (a[i][j] == b[i][j]) continue;

			int add = b[i][j] - a[i][j];
			if (b[i][j] < a[i][j]) add += 3;

			a[i][j] = (a[i][j] + add) % 3;
			a[n][m] = (a[n][m] + add) % 3;

			add = 3 - add;
			a[i][m] = (a[i][m] + add) % 3;
			a[n][j] = (a[n][j] + add) % 3;
		}
	}

	bool res = true;
	for (int i = 1; i <= n; i++)
		if (a[i][m] != b[i][m]) res = false;
	for (int i = 1; i <= m; i++)
		if (a[n][i] != b[n][i]) res = false;

	return res;
}

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		puts(solve() ? "Yes" : "No");
	}
	return 0;
}
