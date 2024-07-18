//纯纯是思维 哎
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 1e6, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;
int cnt = 1;
map<pair<int, int>, int> f;
int hah(pair<int, int> pos)
{
	if (f[pos])
		return f[pos];

	f[pos] = cnt;
	return cnt++;
}
vector<vector<int>> pos(N + 5);
signed main()
{
	IOS;
	int n, x, y;
	cin >> n >> x >> y;
	string s;
	cin >> s;
	if (x == 0 && y == 0)
	{
		cout << (n * (n + 1) / 2);
		return 0;
	}
	for (int i = 0; i < n; i++)
	{
		static int tx = 0, ty = 0;
		if (s[i] == 'W') ty++;
		else if (s[i] == 'S') ty--;
		else if (s[i] == 'A') tx--;
		else tx++;
		pos[hah({ tx, ty })].push_back(i);
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		int tar = hah({ x, y });
		int r = -1;
		if (!pos[tar].empty())
		{
			r = lower_bound(pos[tar].begin(), pos[tar].end(), i) - pos[tar].begin();
			if (r < pos[tar].size() && r >= 0)
				ans += n - pos[tar][r];
		}

		if (s[i] == 'W') y++;
		else if (s[i] == 'S') y--;
		else if (s[i] == 'A') x--;
		else x++;
	}
	cout << ans << endl;
	return 0;
}
