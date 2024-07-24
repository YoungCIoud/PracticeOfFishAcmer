// 思维 大大的思维
#include<bits/stdc++.h>
//using namespace std;
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
int main()
{
	int n, m, k;
	std::cin >> n >> m >> k;

	vct mpx(2, vct(n + 5, vct<int>(m + 5)));
	vct mpy(2, vct(n + 5, vct<int>(m + 5)));
	mpx[0][1][1] = 1, mpx[1][n][1] = 1;
	mpy[0][1][1] = 1, mpy[1][1][m] = 1;
	for (int i = 1; i <= k; i++)
	{
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		mpx[0][a][b]++, mpx[0][a][d + 1]--;
		mpx[1][c][b]++, mpx[1][c][d + 1]--;
		mpy[0][a][b]++, mpy[0][c + 1][b]--;
		mpy[1][a][d]++, mpy[1][c + 1][d]--;
	}
	for (int k = 0; k < 2; k++)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				mpx[k][i][j] += mpx[k][i][j - 1];

		for (int j = 1; j <= m; j++)
			for (int i = 1; i <= n; i++)
				mpy[k][i][j] += mpy[k][i - 1][j];
	}

	for (int j = 1; j <= m; j++)
		for (int i = 1; i <= n; i++)
			mpx[0][i][j] = (mpx[0][i][j] ? i : mpx[0][i - 1][j]);
	for (int j = 1; j <= m; j++)
		for (int i = n; i >= 1; i--)
			mpx[1][i][j] = (mpx[1][i][j] ? i : mpx[1][i + 1][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			mpy[0][i][j] = (mpy[0][i][j] ? j : mpy[0][i][j - 1]);
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= 1; j--)
			mpy[1][i][j] = (mpy[1][i][j] ? j : mpy[1][i][j + 1]);

	int ans = n * m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (mpx[0][i][j] == i && mpy[0][i][j] == j)
				ans = std::min(ans, (mpx[1][i][j] - i + 1) * (mpy[1][i][j] - j + 1));

	std::cout << ans;
	return 0;
}
