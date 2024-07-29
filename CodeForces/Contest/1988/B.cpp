// 还是水题
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 998244353, Inf = 1e18, N = 2e5, M = 1e6;
bool solve()
{
	int n, cnt0 = 0, cnt1 = 0;
	std::cin >> n;
	char a = '*', b = '*';
	for (int i = 1; i <= n; i++)
	{
		a = b;
		std::cin >> b;
		if (b == '1')
			cnt1++;
		else if (a != '0')
			cnt0++;
		else
			continue;
	}
	return cnt1 > cnt0;
}

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
		puts(solve() ? "Yes" : "No");
	return 0;
}
