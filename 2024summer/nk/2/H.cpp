// 代码还是哥哥的好
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 800, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;

void solve()
{
	int n, x, y;
	cin >> n >> x >> y;
	string s;
	cin >> s;
	vector<array<int, 2>> a(n + 1);
	a[0] = { 0, 0 };
	for (int i = 0; i < n; i++)
	{
		a[i + 1] = a[i];
		if (s[i] == 'W')
			a[i + 1][1]++;
		else if (s[i] == 'S')
			a[i + 1][1]--;
		else if (s[i] == 'D')
			a[i + 1][0]++;
		else
			a[i + 1][0]--;
	}

	map<array<int, 2>, int> idx;
	int ans = 0;
	for (int i = n; ~i; i--)
	{
		idx[a[i]] = i;
		if (idx.count({ a[i][0] + x, a[i][1] + y }))
		{
			int j = idx[{ a[i][0] + x, a[i][1] + y }];
			j = max(j, i + 1);
			ans += n - j + 1;
		}
	}
	cout << ans;
	return;
}
signed main()
{
	int t = 1;
	//cin >> t;
	while (t--)
		solve();
}
