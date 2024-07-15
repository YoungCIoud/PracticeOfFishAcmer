#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e5, M = 5e6, Inf = 1e16, Mod = 1e9 + 7;
int n, k;
int a[N + 5];

int trie[M + 5][2], cnt = 1, p[M + 5];

int quiry(int mid, int val)
{
	int cur = 1, pos = 0;
	for (int i = 30; ~i; i--)
	{
		int bit = val >> i & 1;
		if (mid >> i & 1)
		{
			pos = max(pos, p[trie[cur][bit]]);
			cur = trie[cur][bit ^ 1];
		}
		else cur = trie[cur][bit];
	}
	return pos;
}

void insert(int val, int pos)
{
	int cur = 1;
	for (int i = 30; ~i; i--)
	{
		int bit = val >> i & 1;
		if (!trie[cur][bit])
			trie[cur][bit] = ++cnt;

		cur = trie[cur][bit];
		p[cur] = pos;
	}
}

int sum(int mid)
{
	int res = 0, pos = 0;
	for (int i = 1; i <= n; i++)
	{
		pos = max(pos, quiry(mid, a[i]));
		res += pos;
		insert(a[i], i);
	}

	for (int i = 0; i <= cnt; i++)
		trie[i][0] = trie[i][1] = p[i] = 0;
	cnt = 1;

	return res;
}

void solve()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}

	int l = 0, r = (1ll << 30);
	while (l <= r)
	{
		int m = l + r >> 1;
		if (sum(m) < k) l = m + 1;
		else r = m - 1;
	}
	cout << r << endl;
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
