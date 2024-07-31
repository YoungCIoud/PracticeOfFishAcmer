// 二分
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr int Mod = 998244353, Inf = 1e9, N = 1e5, M = 1e8;
int main()
{
	int n, q;
	std::cin >> n >> q;
	vct<int> a(n);
	for (auto& i : a)
		std::cin >> i;
	sort(a.begin(), a.end());

	// 以b为中心radius为半径包含了多少个数
	auto cnt = [&](int b, int radius) -> int
		{
			auto l = std::lower_bound(a.begin(), a.end(), b - radius);
			auto r = std::upper_bound(a.begin(), a.end(), b + radius);
			//std::cout
			//	<< "r:" << radius << '\t'
			//	<< "l:" << b - radius << " find:" << l - a.begin() << '\t'
			//	<< "r:" << b + radius << " find:" << r - a.begin() << '\t'
			//	<< "return " << r - l << '\n';
			return r - l;
		};

	while (q--)
	{
		int b, k;
		std::cin >> b >> k;
		
		int l = 0, r = Inf;
		while (l <= r)
		{
			int m = l + r >> 1;
			if (cnt(b, m) < k)
				l = m + 1;
			else
				r = m - 1;
		}
		std::cout << l << '\n';
	}
	get AC;
} 
