#include<iostream>
using namespace std;
const int N = 100, Inf = 0x3f3f3f3f;
// 0-4 分别是- A C G T
const int val[5][5] = {
	-Inf,-3,-4,-2,-1,
	-3,5,-1,-2,-1,
	-4,-1,5,-3,-2,
	-2,-2,-3,5,-2,
	-1,-1,-2,-2,5
};
int a[N + 5], b[N + 5], dp[N + 5][N + 5];
// dp[i][j]表示a的前i个字符和b的前j个字符的最大值
int f(char c)
{
	switch (c)
	{
	case 'A':return 1;
	case 'C':return 2;
	case 'G':return 3;
	case 'T':return 4;
	default:return -1;
	}
}
int main()
{
	int n, m;
	cin >> n; getchar();
	for (int c = getchar(), i = 1; i <= n; c = getchar(), i++)
		a[i] = f(c), dp[i][0] = dp[i - 1][0] + val[0][a[i]];
	cin >> m; getchar();
	for (int c = getchar(), i = 1; i <= m; c = getchar(), i++)
		b[i] = f(c), dp[0][i] = dp[0][i - 1] + val[0][b[i]];
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dp[i][j] = max(dp[i - 1][j - 1] + val[a[i]][b[j]], max(dp[i - 1][j] + val[0][a[i]], dp[i][j - 1] + val[0][b[j]]));

	cout << dp[n][m];
	return 0;
}
