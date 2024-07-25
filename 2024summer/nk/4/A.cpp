// 哎
#include<bits/stdc++.h>
//using namespace std;
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
using i64 = long long;
constexpr int N = 1e6;
int fa[N + 5], deep[N + 5], ans[N + 5];
int getfa(int u)
{
	if (u != fa[u])
	{
		int v = fa[u];
		fa[u] = getfa(fa[u]);
		deep[u] += deep[v];
	}
	return fa[u];
}


void solve()
{
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		deep[i] = 0;
		ans[i] = 0;
	}
	
	for (int i = 1; i <= n - 1; i++)
	{
		int u, v, c;
		std::cin >> u >> v >> c;
		fa[v] = u;
		deep[v] = 1;
		int f = getfa(v);
		ans[f] = std::max(ans[f], deep[v] + ans[v]);
		std::cout << ans[c] << " ";
	}
	std::cout << '\n';
}

int main()
{
	int t = 1;
	std::cin >> t;
	while (t--)
	{
		solve();
	}
}
