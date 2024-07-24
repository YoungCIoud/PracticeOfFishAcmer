#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
using i64 = long long;
using u64 = unsigned long long;
int n, a, b, len;
std::string s;
std::string t;
std::vector<int> pre[2];
struct node
{
	int nex;
	int n0 = 0, n1 = 0;
};

int main()
{
	std::cin >> n >> a >> b >> s;
	len = log2(2 * b + 1) + 1;
	t += "#";
	while (t.length() < 2 * a + n)
		t += s;
	s = "#" + s;
	pre[0].assign(t.length(), 0);
	pre[1].assign(t.length(), 0);
	for (int i = 1; i < t.length(); i++)
	{
		pre[0][i] = pre[0][i - 1];
		pre[1][i] = pre[1][i - 1];
		pre[t[i] - '0'][i]++;
	}
	std::vector p(n + 1, std::vector<node>(len, { 0, 0, 0 }));
	std::vector<int> in(n + 1);
	for (int i = 1; i <= n; i++)
	{
		int p0 = std::lower_bound(pre[0].begin(), pre[0].end(), a + pre[0][i - 1]) - pre[0].begin() + 1;
		int p1 = std::lower_bound(pre[1].begin(), pre[1].end(), a + pre[1][i - 1]) - pre[1].begin() + 1;
		if (p0 < p1)
		{
			p0 %= n;
			if (p0 == 0)
				p0 = n;
			in[p0]++;
			p[i][0].nex = p0;
			p[i][0].n0++;
		}
		else
		{
			p1 %= n;
			if (p1 == 0)
				p1 = n;
			in[p1]++;
			p[i][0].nex = p1;
			p[i][0].n1++;
		}
	}
	for (int l = 1; l < len; l++)
	{
		for (int i = 1; i <= n; i++)
		{
			int v = p[i][l - 1].nex;
			p[i][l] = p[i][l - 1];
			p[i][l].nex = p[v][l - 1].nex;
			p[i][l].n0 += p[v][l - 1].n0;
			p[i][l].n1 += p[v][l - 1].n1;
		}
	}

	std::vector<int> ans(n + 1);
	for (int i = 1; i <= n; i++)
	{
		int n0 = 0, n1 = 0, cur = i;
		for (int l = len - 1; ~l; l--)
		{
			if (n0 + p[cur][l].n0 >= b || n1 + p[cur][l].n1 >= b)
				continue;

			n0 += p[cur][l].n0, n1 += p[cur][l].n1;
			cur = p[cur][l].nex;
		}
		n0 += p[cur][0].n0, n1 += p[cur][0].n1;
		std::cout << (n1 == b);
	}
	return 0;
}

