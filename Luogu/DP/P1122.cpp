#include<vector>
#include<iostream>
using namespace std;
const int N = 16000;
int val[N + 5], in[N + 5], dp[N + 5][2];// 0代表选 1代表不选
vector<int> g[N + 5];

void dfs(int cur,int fa)
{
	dp[cur][0] = 0, dp[cur][1] = val[cur];
	for (int to : g[cur])
	{
		if (to == fa) continue;
		dfs(to, cur);
		dp[cur][1] += max(dp[to][1] , dp[to][0]);
	}
}

int main()
{
	int n; cin >> n;
	for (int i = 1; i <= n; i++) cin >> val[i];
	for (int i = 1; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1,0);
	//for (int i = 1; i <= n; i++) cout << dp[i][0] << " " << dp[i][1] << endl;
	int ans = -0x3f3f3f3f;
	for (int i = 1; i <= n; i++)
		ans = max(ans, dp[i][1]);
	cout << ans;
	return 0;
}
