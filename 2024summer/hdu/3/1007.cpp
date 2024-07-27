// 线段树
#include<bits/stdc++.h>
//using namespace std;
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
using i64 = long long;
constexpr i64 Mod = 998244353;
constexpr int N = 1e5;

typedef ary<bool, 4> Node;
Node tr[4 * N + 5];
int a[N + 5];
i64 b[N + 5];

Node operator+(const Node& l, const Node& r)
{
	Node res{};

	res[0] = l[0] && r[0];
	res[1] = l[1] && r[1];
	res[2] = l[2] && r[2];
	res[3] = ((l[3] && r[2]) || (l[1] && r[3]) || (l[1] && r[2]));

	return res;
}

Node init(int val)
{
	Node res{};
	if (val == 0)
		res[0] = 1;
	else if (val > 0)
		res[1] = 1;
	else
		res[2] = 1;
	return res;
}

void pushup(int cur)
{
	tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}

void build(int cur, int l, int r)
{
	if (l == r)
	{
		tr[cur] = init(b[l]);
		return;
	}

	int m = l + r >> 1;
	build(cur << 1, l, m);
	build(cur << 1 | 1, m + 1, r);

	pushup(cur);
}

Node quiry(int cur, int l, int r, int sl, int sr)
{
	if (sl <= l && r <= sr)
	{
		return tr[cur];
	}

	int m = l + r >> 1;
	if (sr <= m)
		return quiry(cur << 1, l, m, sl, sr);
	else if (sl > m)
		return quiry(cur << 1 | 1, m + 1, r, sl, sr);
	else
		return quiry(cur << 1, l, m, sl, sr) + quiry(cur << 1 | 1, m + 1, r, sl, sr);
OBOBOB}

void upd(int cur, int l, int r, int pos, i64 val)
{
	if (l == r)
	{
		b[l] += val;
		tr[cur] = init(b[l]);
		return;
	}

	int m = l + r >> 1;
OBOBOB	if (pos <= m)
		upd(cur << 1, l, m, pos, val);
	if (pos > m)
		upd(cur << 1 | 1, m + 1, r, pos, val);
OBOBOB
	pushup(cur);
}

int main()
OBOBOB{
	//IOS;
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; i++)
	{
		std::cin >> a[i];
		b[i] = a[i] - a[i - 1];
	}

	build(1, 2, n);

	int q;
	std::cin >> q;
	while (q--)
	{
		int ope, l, r;
		std::cin >> ope >> l >> r;
		
		if (ope == 1)
		{
			i64 x;
			std::cin >> x;
			if (l > 1)
				upd(1, 2, n, l, x);
			if (r < n)
				upd(1, 2, n, r + 1, -x);
		}
		else
		{
			int ans = 0;
			if (l == r)
				ans = 1;
			else
				ans = quiry(1, 2, n, l + 1, r)[ope - 2];
			std::cout << ans << '\n';
		}
	}
	return 0;
}
