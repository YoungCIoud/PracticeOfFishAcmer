// AC自动机
#include<bits/stdc++.h>
constexpr int len = 1e6;
int tr[len + 5][26], cnt = 1;
int fail[len + 5], e[len + 5];

void insert(std::string s)
{
	int cur = 0;
	for (auto c : s)
	{
		if (!tr[cur][c - 'a'])
			tr[cur][c - 'a'] = cnt++;
		cur = tr[cur][c - 'a'];
	}
	e[cur]++;
}

void build()
{
	std::queue<int> q;
	for (int i = 0; i < 26; i++)
		if (tr[0][i])
			q.push(tr[0][i]);
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		for (int i = 0; i < 26; i++)
		{
			if (tr[cur][i])
				fail[tr[cur][i]] = tr[fail[cur]][i],
				q.push(tr[cur][i]);
			else
				// 从当前状态,跳转到次态的后缀(修改了字典树的形态)
				tr[cur][i] = tr[fail[cur]][i];
		}
	}
}

int quiry(std::string s)
{
	int cur = 0, ans = 0;
	for (auto c : s)
	{
		cur = tr[cur][c - 'a'];
		for (int i = cur; i && ~e[i]; i = fail[i])
			ans += e[i], e[i] = -1;
	}
	return ans;
}

int main()
{
	int n;
	std::string s;
	std::cin >> n;
	while (n--)
	{
		std::cin >> s;
		insert(s);
	}
	build();
	std::cin >> s;
	std::cout << quiry(s) << '\n';
	return 0;
}
