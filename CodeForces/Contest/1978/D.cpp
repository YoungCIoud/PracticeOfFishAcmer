#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, Inf = 1e18, Mod = 998244353;
int n, c;
int st[N + 5][20], pre[N + 5];

void solve()
{
	cin >> n >> c;
	for (int i = 1; i <= n; i++)
	{
		cin >> st[i][0];
		pre[i] = pre[i - 1] + st[i][0];
	}

	if (n == 1)
		return void(puts("0"));

	for (int bit = 1; bit < 20; bit++)
		for (int i = 1; i + (1ll << bit) - 1 <= n; i++)
			st[i][bit] = max(st[i][bit - 1], st[i + (1ll << bit - 1)][bit - 1]);

	auto q = [&](int l, int r) -> int 
		{
			int bit = log2(r - l + 1);
			return max(st[l][bit], st[r - (1ll << bit) + 1][bit]);
		};
	if (st[1][0] + c < q(2, n))
	{
		cout << 1 << " ";
	}
	else cout << 0 << " ";
	for (int i = 2; i < n; i++)
	{
		int add = 0;
		int ans = 0;
		if (st[i][0] <= max(st[1][0] + c, q(1, i - 1)) || st[i][0] < q(i + 1, n))
		{
			ans = i - 1;
			add = c + pre[i - 1];
		}
		if (st[i][0] + add < q(i + 1, n))
		{
			ans++;
		}
		cout << ans << " ";
	}
	if (st[n][0] > max(q(1, n - 1), st[1][0] + c))
	{
		cout << 0;
	}
	else cout << n - 1;
	cout << endl;
	return;
}

signed main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
