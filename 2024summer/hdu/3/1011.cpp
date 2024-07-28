// 三分
#include<bits/stdc++.h>
//using namespace std;
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 998244353, Inf = 1e18, N = 2e5;
constexpr int dx[4] = { 1, -1, 0, 0 };
constexpr int dy[4] = { 0, 0, -1, 1 };
int n;
ary<i64, 3> a[N + 5];

i64 cnt(int m)
{
	i64 mxx = -Inf, mnx = Inf;
	i64 mxy = -Inf, mny = Inf;
	for (int i = 1; i <= n; i++)
	{
		mxx = std::max(mxx, a[i][0] + dx[a[i][2]] * m);
		mnx = std::min(mnx, a[i][0] + dx[a[i][2]] * m);
		mxy = std::max(mxy, a[i][1] + dy[a[i][2]] * m);
		mny = std::min(mny, a[i][1] + dy[a[i][2]] * m);
	}
	return 2 * (mxx + mxy - mnx - mny);
}

int main()
{
	std::cin >> n;
	for (int i = 1; i <= n; i++)
	{
		i64 x, y;
		char c;
		std::cin >> x >> y >> c;
		switch (c)
		{
		case 'E':
			c = 0;
			break;
		case 'W':
			c = 1;
			break;
		case 'S':
			c = 2;
			break;
		default:
			c = 3;
			break;
		}
		a[i] = { x, y, i64(c) };
	}
	int l = 0, r = 2e9;
	while (l <= r)
	{
		int ml = l + (r - l) / 3;
		int mr = r - (r - l) / 3;
		if (cnt(ml) > cnt(mr))
			l = ml + 1;
		else
			r = mr - 1;
	}
	std::cout << cnt(l) << '\n';

	get AC;
}
