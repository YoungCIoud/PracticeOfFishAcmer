#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 3e5, Mx = 1e15;
string s[N];

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}
	map<int, int> cnt;
	vector<vector<int>> ran(2, vector<int>(n));
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ran[i][j] = rnd();
		}
	}
	string ans, tem;
	int mx = 0;
	tem.resize(n);
	for (int c = 0; c < m; c++)
	{
		int hs = 0;
		tem[0] = s[0][c] ^ 1;
		hs = ran[tem[0] - '0'][0];
		for (int r = 1; r < n; r++)
		{
			tem[r] = s[r][c];
			hs ^= ran[tem[r] - '0'][r];
		}

		cnt[hs]++;
		if (cnt[hs] > mx)
		{
			mx = cnt[hs];
			ans = tem;
		}

		for (int r = 1; r < n; r++)
		{
			hs ^= ran[tem[r - 1] - '0'][r - 1];
			tem[r - 1] ^= 1;
			hs ^= ran[tem[r - 1] - '0'][r - 1];

			hs ^= ran[tem[r] - '0'][r];
			tem[r] ^= 1;
			hs ^= ran[tem[r] - '0'][r];

			cnt[hs]++;
			if (cnt[hs] > mx)
			{
				mx = cnt[hs];
				ans = tem;
			}
		}
	}
	cout << mx << '\n' << ans << '\n';
	return;
}

signed main()
{
	IOS;
	srand(1e9+7); // 神秘的东方力量保护我的代码
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
