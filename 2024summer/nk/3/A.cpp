// ???
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
using i64 = long long;
using u64 = unsigned long long;

int main()
{
	int n, l, r;
	std::cin >> n >> l >> r;
	int k = (n - l - 1) / (r - l);
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		int a;
		std::cin >> a;
		sum += std::min(k, (a - 1) / 2);
	}
	puts(sum >= k * l ? "Yes" : "No");
	return 0;
}
