#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 5e3, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;
int c[N + 5][N + 5];

int qpow(int a, int p, int Mo)
{
	int res = 1;
	for (; p; p >>= 1, a = a * a % Mo)
	{
		if (p & 1)
			res = res * a % Mo;
	}
	return res;
}
signed main()
{
	int n, m, p, ans = 0;
	cin >> n >> m >> p;
	c[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			c[i][j] = c[i - 1][j];
			if (j) c[i][j] = (c[i][j] + c[i - 1][j - 1]) % p;
		}
	}

	for (int k = 1; k <= n; k++)
	{
		ans = (ans + qpow(2, (n - k) * (m - 1), p) * qpow(qpow(2, k, p) - 1, m - 1, p) % p * c[n][k]) % p;
	}
	cout << ans << endl;
}
