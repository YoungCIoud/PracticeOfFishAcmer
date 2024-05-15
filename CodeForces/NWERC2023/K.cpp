// 注意先检查是否越界
#include<iostream>
#include<queue>
using namespace std;
const int dx[4] = { 1,1,-1,-1 };
const int dy[4] = { 1,-1,1,-1 };
const int N = 500;
int n, mov[2][2];
bool vis[N+5][N+5];

inline bool out(int x)
{
	return 0 >= x || x > n;
}

void bfs(int s)
{
	bool book[2][N+5][N+5] = { false };
	queue<pair<int,int>> q[2];
	q[s].push({ 1,1 });
	book[s][1][1] = true;
	while (!q[s].empty())
	{
		while (!q[s].empty())
		{
			int x = q[s].front().first;
			int y = q[s].front().second;
			q[s].pop();
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					int xx = x + dx[i] * mov[s][j];
					int yy = y + dy[i] * mov[s][j ^ 1];
					if (out(xx) || out(yy) || book[s ^ 1][xx][yy]) continue;
					// cout << xx << " " << yy << endl;
					q[s ^ 1].push({ xx,yy });
					book[s ^ 1][xx][yy] = true;
				}
			}
		}
		s ^= 1;
	}
	for (int k = 0; k < 2; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				vis[i][j] |= book[k][i][j];
}

int main()
{
	cin >> n;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			cin >> mov[i][j];
	bfs(1), bfs(0);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (vis[i][j]) ans++;
	cout << ans;
	return 0;
}
