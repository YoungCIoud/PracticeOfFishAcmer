// 我是历史学家,这是真史
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 800, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;
char ans[N + 5][N + 5];

void solve()
{
	int n, m, k, x, y;
	char c, fst;
	cin >> n >> m >> k >> x >> y >> c;

	fst = c;
	if ((x + y) & 1)
		fst ^= 3;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans[i][j] = fst ^ (((i + j) & 1) * 3);
	int mx = n + m + ((n - 1) * (m - 1) + (fst & 1)) / 2;
	if (n + m > k || mx < k)
	{
		puts("No");
		return;
	}
	puts("Yes");
	int i = 1, j = 1;
	
	for (i = 1; i < n && mx != k; i++)
	{
		for (j = 1; j <= m; j++)
		{
			cout << c;
			if (c == ans[i][j]) continue;

			if (ans[i][j] == 'A')
				mx -= (int)(j != m);
			else
				mx -= (int)(j != 1);

			if (mx == k)
			{
				j += 1;
				break;
			}
		}
		if (mx == k)
			break;
		cout << endl;
	}
	for (i; i <= n; i++, j = 1)
	{
		for (j; j <= m; j++)
			cout << ans[i][j];
		cout << endl;
	}
	return;
}
signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
		solve();
}
