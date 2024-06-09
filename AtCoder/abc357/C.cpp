#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int S = 729, Inf = 1e18;
int n;
char ans[S + 5][S + 5];

// 横纵坐标和问题的规模
void dfs(int x, int y, int s)
{
	if (s == 0) return void(ans[x][y] = '#');
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1 && j == 1)
			{
				for (int xx = x + pow(3, s - 1); xx < x + pow(3, s - 1) * 2; xx++)
					for (int yy = y + pow(3, s - 1); yy < y + pow(3, s - 1) * 2; yy++)
						ans[xx][yy] = '.';
			}
			else dfs(x + i * pow(3, s - 1), y + j * pow(3, s - 1), s - 1);
		}
	}
}

signed main()
{
	cin >> n;
	dfs(0, 0, n);
	for (int i = 0; i < pow(3, n); i++, puts(""))
		for (int j = 0; j < pow(3, n); j++)
			cout << ans[i][j];
}
