// 什么暴力猜结论题
#include<bits/stdc++.h>
//using namespace std;
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
using i64 = long long;

i64 sqr(i64 a)
{
	i64 l = 0, r = 1e9;
	while (l <= r)
	{
		i64 m = l + r >> 1;
		if (m * m <= a) l = m + 1;
		else r = m - 1;
	}
	return r;
}

void solve()
{
	i64 x;
	std::cin >> x;
	i64 y = sqr(x);
	
	i64 ans = 2 * y;
	if (y * y == x)
		ans += 1;
	else if (x > y * (y + 1))
		ans += 3;
	else
		ans += (x % 2 ? 3 : 2);
	
	std::cout << ans << '\n';
}

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
	{
		solve();
	}
}
