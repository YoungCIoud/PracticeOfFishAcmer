// 神奇构造
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
using i64 = long long;
using u64 = unsigned long long;
std::map<i64, int> same;
std::vector<std::pair<i64, i64>> p;
int main()
{
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		std::cin >> x >> y;
		
		if (x == y)
			same[x]++;
		else
			p.push_back({ x, y });
	}

	std::vector<std::pair<int, int>> ans;
	std::priority_queue<std::pair<int, int>> s;
	for (auto [num, tim] : same)
		s.push({ tim, num });
	int cur = -1;
	while (s.size() > 1)
	{
		auto [ta, na] = s.top();
		s.pop();
		auto [tb, nb] = s.top();
		s.pop();
		ta -= 1;
		tb -= 1;
		if (ta)
			s.push({ ta, na });
		if (tb)
			s.push({ tb, nb });

		ans.push_back({ na, na }),
		ans.push_back({ nb, nb });
		cur = nb;
	}
	int tim = 0, las = -1;
	if (s.size())
	{
		tim = s.top().first;
		las = s.top().second;
		for (auto& [x, y] : p)
			x -= las, y -= las;
		sort(p.begin(), p.end(), [](std::pair<int, int> x, std::pair<int, int> y) {
			if (x.first == 0 && x.second == 0) return true;
			else return false;
			});
		for (auto& [x, y] : p)
			x += las, y += las;
	}

	for (auto [x, y] : p)
	{
		if (tim && cur != las)
		{
			ans.push_back({ las, las });
			tim--;
			cur = las;
		}
		if (x == cur)
			std::swap(x, y);
		ans.push_back({ x, y });
		cur = y;
	}
	if (tim && cur != las)
	{
		ans.push_back({ las, las });
		cur = las, tim--;
	}
	if (ans.size() == n)
	{
		puts("Yes");
		for (auto [x, y] : ans)
			std::cout << x << ' ' << y << '\n';
	}
	else
		puts("No");
	return 0;
}
