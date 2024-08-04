// 大力讨论 我们都是罚时高手
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 1e9 + 7, Inf = 1e9;
constexpr int N = 1e3, M = 20;

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
	{
		int n;
		std::cin >> n;
		vct<int> a(n);
		for (auto& i : a)
			std::cin >> i;

		std::sort(a.begin(), a.end());
		vct<int> b;
		for (int i = 0; i < n; i++)
		{
			if (a[i] == 0) continue;

			b.push_back(a[i]);
			for (int j = i + 1; j < n; j++)
				if (a[j] % a[i] == 0) a[j] = 0;
		}

		int _n = b.size();
		vct<int> g(_n + 1);
		for (int i = 0; i < _n; i++)
			for (int j = 0; j < _n; j++)
				if (i != j) g[i] = gcd(g[i], b[j]);
		g[_n] = gcd(g[0], b[0]);

		bool flag = false;
		if (g[_n] == b[0])
		{
			std::cout << n - 1 << '\n';
			flag = true;
		}
		for (int i = 0; i < _n && !flag; i++)
		{
			if (g[i] == b[i ? 0 : 1] || g[i] > b[i])
			{
				std::cout << n << '\n';
				flag = true;
			}
			for (int j = 0; j < _n && !flag; j++)
				if (i != j && b[i] % b[j] && g[i] % (b[i] % b[j]) == 0)
				{
					std::cout << n << '\n';
					flag = true;
				}
		}

		if (!flag)
			std::cout << n + 1 << '\n';
	}
	get AC;
}
