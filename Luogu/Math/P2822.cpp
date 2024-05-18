//  组合数 杨辉三角 二维前缀和
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
// #define int long long
using namespace std;
const int N = 2e3;
int c[N + 5][N + 5];
int ans[N + 5][N + 5];


int main()
{
	int t, k;
	cin >> t >> k;
	c[0][0] = c[1][0] = c[1][1] = 1;
	for (int i = 2; i <= N; i++)
	{
		c[i][0] = 1;
		for (int j = 1; j <= i; j++)
		{
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
			c[i][j] %= k;
			ans[i][j] = ans[i][j - 1] + ans[i - 1][j] - ans[i - 1][j - 1];
			if (c[i][j] == 0) ans[i][j]++;
		}
		ans[i][i + 1] = ans[i][i];
	}
	while (t--)
	{
		int a, b;
		cin >> a >> b;
		cout << ans[a][b > a ? a : b] << endl;
	}
	return 0;
}
