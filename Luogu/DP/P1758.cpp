// 注意力惊人
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long
using i64 = long long;
const int Mod = 1024523, M = 1e9, N = 500, Inf = 1e16;
signed main()
{
	int n, m;
	std::cin >> n >> m;
	std::string a, b;
	std::cin >> a >> b;
	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());

	std::vector f(2, std::vector(n + 1, std::vector<int>(n + 1)));
	f[0][0][0] = 1;
	for (int l = 1, ind = 1; l <= n + m; l++, ind ^= 1)
		for (int i = std::max(0ll, l - m); i <= std::min(n, l); i++)
			for (int j = std::max(0ll, l - n); j <= std::min(n, l); j++)
			{
				int v = 0;
				if (i && j && a[i - 1] == a[j - 1])
					v += f[ind ^ 1][i - 1][j - 1];
				if (l - i && l - j && b[l - i - 1] == b[l - j - 1])
					v += f[ind ^ 1][i][j];
				if (i && l - j && a[i - 1] == b[l - j - 1])
					v += f[ind ^ 1][i - 1][j];
				if (l - i && j && b[l - i - 1] == a[j - 1])
					v += f[ind ^ 1][i][j - 1];
				f[ind][i][j] = v % Mod;
			}
	std::cout << f[(n + m) & 1][n][n] << '\n';
	return 0;
}
