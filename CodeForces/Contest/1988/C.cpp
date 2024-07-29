// 没注意开i64wa了一发
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 998244353, Inf = 1e18, N = 2e5, M = 1e6;

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
	{
		vct<i64> ans;
		i64 n;
		std::cin >> n;
		for (int i = 60; ~i; i--)
		{
			if ((n >> i & 1ll) == 0)
				continue;

			i64 tem = n & ((1ll << 60) - 1ll - (1ll << i));
			if (tem)
				ans.push_back(tem);
		}
		ans.push_back(n);
		std::cout << ans.size() << '\n';
		for (auto& i : ans)
			std::cout << i << ' ';
		std::cout << '\n';
	}
	return 0;
}
