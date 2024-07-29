// 很难评价
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
#define get return
#define AC 0
using i64 = long long;
constexpr i64 Mod = 998244353, Inf = 1e18, N = 1e5, M = 1e6;
constexpr int d31[7] = { 1, 3, 5, 7, 8, 10, 12 };
constexpr int d30[4] = { 4, 6, 9, 11 };
int n, m;

int data[800][10], tot;
bool en[800];

int suf[M + 5];
std::queue<int> num[10];

str name[N + 5];
std::queue<ary<int, 2>> cha[26];
int ans = 0;

void insert0(str s)
{
	int cur = 0;
	for (auto& c : s)
	{
		if (data[cur][c - '0'] == 0)
			data[cur][c - '0'] = ++tot;
		cur = data[cur][c - '0'];
	}
	en[cur] = true;
	//std::cout << cur << " ";
}
void quiry0(str s)
{
	for (int i = 0; i < 10; i++)
		if (data[0][i])
			num[i].push(data[0][i]);

	for (int i = m - 1; ~i; i--)
	{
		auto& c = s[i];
		if ('a' <= c && c <= 'z')
			continue;

		int len = num[c - '0'].size();
		for (int j = 0; j < len; j++)
		{
			int tem = num[c - '0'].front();
			if (en[tem])
			{
				suf[i]++;
				//std::cout << "find" << '\n';
			}

			for (int k = 0; k < 10; k++)
				if (data[tem][k])
					num[k].push(data[tem][k]);

			num[c - '0'].pop();
		}
	}
}

void quiry1(str s)
{
	for (int i = 1; i <= n; i++)
		cha[name[i][0] - 'a'].push({ i, 0 });

	for (int i = 0; i < m; i++)
	{
		char& c = s[i];
		if ('a' <= c && c <= 'z')
		{
			int len = cha[c - 'a'].size();
			for (int j = 0; j < len; j++)
			{
				auto [u, v] = cha[c - 'a'].front();
				cha[c - 'a'].pop();

				if (v + 1 == name[u].size())
				{
					ans += suf[i + 1];
					continue;
				}

				cha[name[u][v + 1] - 'a'].push({ u, v + 1 });
			}
		}
	}
}

void solve()
{
	for (int i = 0; i < 26; i++)
		while (not cha[i].empty())
			cha[i].pop();
	for (int i = 0; i < 10; i++)
		while (not num[i].empty())
			num[i].pop();
	ans = 0;

	str s;
	std::cin >> n >> m >> s;
	for (int i = 0; i <= m; i++)
		suf[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		std::cin >> name[i];
	}

	quiry0(s);
	for (int i = m - 1; ~i; i--)
		suf[i] += suf[i + 1];
	quiry1(s);
	std::cout << ans << '\n';
}

int main()
{
	IOS;
	for (int i = 31; i; i--)
	{
		str day = std::to_string(i);
		if (day.length() == 1)
			day = "0" + day;
		std::reverse(day.begin(), day.end());
		for (int j = 0; j < 7; j++)
		{
			str mon = std::to_string(d31[j]);
			if (mon.length() == 1)
				mon = "0" + mon;
			std::reverse(mon.begin(), mon.end());
			insert0(day + mon);
		}
	}
	for (int i = 30; i; i--)
	{
		str day = std::to_string(i);
		if (day.length() == 1)
			day = "0" + day;
		std::reverse(day.begin(), day.end());
		for (int j = 0; j < 4; j++)
		{
			str mon = std::to_string(d30[j]);
			if (mon.length() == 1)
				mon = "0" + mon;
			std::reverse(mon.begin(), mon.end());
			insert0(day + mon);
		}
	}
	for (int i = 29; i; i--)
	{
		str day = std::to_string(i);
		if (day.length() == 1)
			day = "0" + day;
		std::reverse(day.begin(), day.end());
		insert0(day + "20");
	}
	// std::cout << tot;

	int t;
	std::cin >> t;
	while (t--)
	{
		solve();
	}
	get AC;
}
