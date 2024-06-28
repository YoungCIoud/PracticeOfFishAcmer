#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, Inf = 1e18, Mod = 998244353;
int A[N + 5], B[N + 5];

struct node
{
	int len;
	int sum[2];
	int ans;
	
	node()
	{
		len = 0;
		sum[0] = sum[1] = 0;
		ans = 0;
	}
	node operator+ (const node& a) const
	{
		node res;
		res.ans = (ans + a.ans) % Mod;
		res.len = len + a.len;
		res.sum[0] = (sum[0] + a.sum[0]) % Mod;
		res.sum[1] = (sum[1] + a.sum[1]) % Mod;
		return res;
	}
}tr[N * 4];
int tag[N * 4][2];
int op, ql, qr, val;

void build(int cur, int l, int r)
{
	if (l == r)
	{
		tr[cur].len = 1;
		tr[cur].sum[0] = A[l];
		tr[cur].sum[1] = B[l];
		tr[cur].ans = A[l] * B[l] % Mod;
		return;
	}

	int m = (l + r) >> 1;
	build(cur << 1, l, m);
	build(cur << 1 | 1, m + 1, r);

	tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}

void change(int cur, int a, int b)
{
	tr[cur].ans = (tr[cur].ans + a * tr[cur].sum[1] % Mod + b * tr[cur].sum[0] % Mod + a * b % Mod * tr[cur].len % Mod) % Mod;
	tr[cur].sum[0] = (tr[cur].sum[0] + tr[cur].len * a % Mod) % Mod;
	tr[cur].sum[1] = (tr[cur].sum[1] + tr[cur].len * b % Mod) % Mod;
	tag[cur][0] = (tag[cur][0] + a) % Mod, tag[cur][1] = (tag[cur][1] + b) % Mod;
}

void pushdown(int cur)
{
	change(cur << 1, tag[cur][0], tag[cur][1]);
	change(cur << 1 | 1, tag[cur][0], tag[cur][1]);
	tag[cur][0] = tag[cur][1] = 0;
}

node quiry(int cur, int l, int r)
{
	if (ql <= l && r <= qr) return tr[cur];

	if (tag[cur][0] || tag[cur][1]) pushdown(cur);
	int m = (l + r) >> 1;
	node res;
	if (ql <= m) res = res + quiry(cur << 1, l, m);
	if (m < qr) res = res + quiry(cur << 1 | 1, m + 1, r);
	tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];

	return res;
}

void upd(int cur, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		tr[cur].sum[op] = (tr[cur].sum[op] + val * tr[cur].len % Mod) % Mod;
		tr[cur].ans = (tr[cur].ans + tr[cur].sum[!op] * val % Mod) % Mod;
		if (l != r) tag[cur][op] = (tag[cur][op] + val) % Mod;
		return;
	}

	if (tag[cur][0] || tag[cur][1]) pushdown(cur);
	int m = (l + r) >> 1;
	if (ql <= m) upd(cur << 1, l, m);
	if (m < qr) upd(cur << 1 | 1, m + 1, r);
	tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}

signed main()
{
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> A[i];
	for (int i = 1; i <= n; i++) cin >> B[i];

	build(1, 1, n);


	while (q--)
	{
		cin >> op >> ql >> qr;
		op--;
		
		if (op == 2)
			cout << quiry(1, 1, n).ans % Mod << endl;
		else
		{
			cin >> val;
			upd(1, 1, n);
		}
	}

	return 0;
}
