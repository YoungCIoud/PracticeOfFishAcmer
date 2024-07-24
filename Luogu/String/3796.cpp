#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
// #define int long long
using i64 = long long;
//const int Mod = 1024523, M = 1e9, N = 500, Inf = 1e16;
constexpr int N = 150, Len = 70;
namespace AC
{
	int tot, tr[N * Len + 100][26], e[N * Len + 100];
	int fail[N * Len + 100], cnt[N + 5];
	void init()
	{
		tot = 1;
		memset(tr, 0, sizeof tr);
		memset(e, 0, sizeof e);
		memset(fail, 0, sizeof fail);
		memset(cnt, 0, sizeof cnt);
	}
	void insert(std::string& s, int idx)
	{
		int cur = 0;
		for (auto& c : s)
		{
			if (tr[cur][c - 'a'] == 0)
				tr[cur][c - 'a'] = tot++;
			cur = tr[cur][c - 'a'];
		}
		e[cur] = idx;
	}
	void build()
	{
		std::queue<int> q;
		for (int i = 0; i < 26; i++)
			if (tr[0][i]) q.push(tr[0][i]);
		
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			for (int i = 0; i < 26; i++)
			{
				if (tr[cur][i])
					q.push(tr[cur][i]),
					fail[tr[cur][i]] = tr[fail[cur]][i];
				else
					tr[cur][i] = tr[fail[cur]][i];
			}
		}
	}
	int quiry(std::string& s)
	{
		int cur = 0, mx = 0;
		for (auto& c : s)
		{
			cur = tr[cur][c - 'a'];
			for (int i = cur; i; i = fail[i])
				if (e[i]) mx = std::max(mx, ++cnt[e[i]]);
		}
		return mx;
	}
}

int main()
{
	int n = 1;
	while ((std::cin >> n) && n)
	{
		AC::init();
		std::vector<std::string> s(n + 1);
		for (int i = 1; i <= n; i++)
		{
			std::cin >> s[i];
			AC::insert(s[i], i);
		}
		std::cin >> s[0];
		AC::build();

		int mx = AC::quiry(s[0]);
		std::cout << mx << '\n';
		for (int i = 1; i <= n; i++)
			if (AC::cnt[i] == mx)
				std::cout << s[i] << '\n';
	}
	return 0;
}
