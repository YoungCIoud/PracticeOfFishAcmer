#include<iostream>
using namespace std;
const int N = 100;
int n, q;

int head[N + 5], nex[2 * N + 5], to[2 * N + 5], val[2 * N + 5], cnt;
void add(int u, int v, int w)
{
	nex[++cnt] = head[u], to[cnt] = v, val[cnt] = w;
	head[u] = cnt;
}

int dp[N + 5][N+5];
void dfs(int cur, int fa, int lim)
{
	if (lim == 0) return;
	int l = 0, lv = 0, r = 0, rv = 0;
	for (int i = head[cur]; i; i = nex[i])
	{
		if (to[i] == fa) continue;
		dfs(to[i], cur, lim - 1);
		if (l == 0) l = to[i], lv = val[i];
		else r = to[i], rv = val[i];
	}
	if (l == 0) return;
	// 枚举以cur为根节点的子树含有的边数
	for (int i = 1; i <= lim; i++)
	{
		// 包含一颗子树
		dp[cur][i] = max(dp[l][i - 1] + lv, dp[r][i - 1] + rv);
		// 包含两颗子树 则以两颗子树为根节点的子树一共包含lim-2条边
		for (int j = 0; j <= i-2; j++)
			dp[cur][i] = max(dp[cur][i], dp[l][j] + lv + dp[r][i - 2 - j] + rv);
	}
}

int main()
{
	cin >> n >> q;
	for (int i = 1; i < n; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		add(a, b, c), add(b, a, c);
	}
	dfs(1, 0, q);
	cout << dp[1][q];
}
