// 终于 AC自动机的最终形态
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define aryi2 std::array<int, 2>
#define str std::string
using i64 = long long;
using u64 = unsigned long long;
constexpr int MaxT = 2e6, N = 2e5, MaxS = 2e5;
int cnt[N + 5];
namespace AC
{
	struct Node
	{
		int nex[26] = {};
		int fail = 0;
		vct<int> idx {};

		int val = 0;
	}node[MaxS + 5];
	int root = 0, tot = 1;

	void insert(str s, int idx)
	{
		int cur = root;
		for (auto& c : s)
		{
			if (node[cur].nex[c - 'a'] == 0)
				node[cur].nex[c - 'a'] = tot++;
			cur = node[cur].nex[c - 'a'];
		}
		node[cur].idx.push_back(idx);
	}

	void build()
	{
		std::queue<int> q;
		for (int i = 0; i < 26; i++)
			if (node[root].nex[i])
				q.push(node[root].nex[i]);
		
		while (!q.empty())
		{
			int cur = q.front();
			auto& t = node[cur];
			q.pop();

			for (int i = 0; i < 26; i++)
			{
				if (t.nex[i])
				{
					node[t.nex[i]].fail = node[t.fail].nex[i];
					q.push(t.nex[i]);
				}
				else
				{
					t.nex[i] = node[t.fail].nex[i];
				}
			}
		}
		return;
	}

	void quiry(str s)
	{
		int cur = root;
		for (auto& c : s)
		{
			cur = node[cur].nex[c - 'a'];
			node[cur].val++;
		}
		return;
	}

	int head[MaxS + 5], nex[MaxS + 5], to[MaxS + 5];
	int num = 1;
	
	void add(int u, int v)
	{
		nex[num] = head[u], to[num] = v;
		head[u] = num++;
	}

	int dfs(int cur)
	{
		auto& t = node[cur];
		for (int e = head[cur]; e; e = nex[e])
			t.val += dfs(to[e]);

		for (auto& i : t.idx)
			cnt[i] += t.val;

		return t.val;
	}

	void failtree()
	{
		for (int i = 1; i < tot; i++)
			add(node[i].fail, i);

		dfs(root);
	}
};

int main()
{
	int n;
	str s;
	std::cin >> n;
	for (int i = 1; i <= n; i++)
	{
		std::cin >> s;
		AC::insert(s, i);
	}
	AC::build();
	std::cin >> s;
	AC::quiry(s);
	AC::failtree();

	for (int i = 1; i <= n; i++)
		std::cout << cnt[i] << '\n';

	return 0;
}
