// 大水题
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 998244353, Inf = 1e18, N = 1e5, M = 1e6;

void solve()
{
	int ans = 0;
	int n, k;
	std::cin >> n >> k;
	while (n > k)
	{
		ans += n / k;
		n = n / k + n % k;
	}
	std::cout << ans + (n > 1 ? 1 : 0) << '\n';
}

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
		solve();
	return 0;
}
