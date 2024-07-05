#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 500, Inf = 1e18, Mod = 998244353;
int h[N + 5][N + 5];
int pre[N + 5][N + 5];

int gcd(int x, int y)
{
	while (y != 0)
	{
		int t = x;
		x = y;
		y = t % y;
	}
	return x;
}

bool solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> h[i][j];
		}
	}
	//puts("read");
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		getchar();
		for (int j = 1; j <= m; j++)
		{
			int dig = getchar();
			int f = dig & 1;
			// 二维前缀和维护1的数量
			pre[i][j] = f + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
			sum += h[i][j] * (f ? 1 : -1);
		}
	}
	//puts("read");

	if (sum == 0)
	{
		return true;
	}
	if (sum < 0)
	{
		sum = -sum;
	}
	//puts("cacl");
	int g = 0;
	for (int i = k; i <= n; i++)
	{
		for (int j = k; j <= m; j++)
		{
			int u = i - k + 1, v = j - k + 1;
			int one = pre[i][j] - pre[u - 1][j] - pre[i][v - 1] + pre[u - 1][v - 1];
			int zero = k * k - one;
			//cout << one << endl;
			g = gcd(abs(one - zero), g);
		}
	}
	//cout << sum << " " << g << endl;
	return g && (sum % g ? false : true);
}

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}
