#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e3, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;

signed main()
{
	int n, m;
	std::cin >> n >> m;
	vector<string> mp(n);
	for (int i = 0; i < n; i++)
		std::cin >> mp[i];
	// 0上 1下 2左 3右
	vector<int> di = { -1, 1, 0, 0 };
	vector<int> dj = { 0, 0, -1, 1 };
	vector<vector<int>> trans(128);
	trans['|'] = { 0, 1, 3, 2 };
	trans['-'] = { 1, 0, 2, 3 };
	trans['/'] = { 3, 2, 1, 0 };
	trans['\\'] = { 2, 3, 0 , 1 };

	vector<int> nex(n * m * 4, -1); // nex[i]是i的后继状态
	vector<int> ref(n * m * 4, -1); // ref[i]表示i状态的反射情况
	for (int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			for (int k = 0; k < 4; k++)
			{
				int nexi = i + di[k], nexj = j + dj[k];
				if (nexi < 0 || nexi >= n || nexj < 0 || nexj >= m) continue;

				int u = i * 4 * m + j * 4 + k;
				int v = nexi * 4 * m + nexj * 4 + trans[mp[nexi][nexj]][k];
				nex[u] = v;
				if (k != trans[mp[nexi][nexj]][k])
					ref[v] = nexi * m + nexj;
			}
	vector<int> vis(n * m * 4, 0), ans(n * m * 4, 0);
	vector<int> book(n * m, -1);
	
	for (auto i : nex)
		if (i != -1) vis[i] = 1;
	for (int i = 0; i < n * m * 4; i++)
	{
		if (vis[i]) continue;
		
		vector<int> path;
		for (int j = i; ~j; j = nex[j])
		{
		 	path.push_back(j);
			vis[j] = 2;
		}
		
		int sum = 0;
		for (int j = path.size() - 1; j; j--)
		{
			if (~ref[path[j]])
			{
				sum += book[ref[path[j]]] != i;
				book[ref[path[j]]] = i;
			}
			ans[path[j - 1]] = sum;
		}
	}
	for (int i = 0; i < m * n * 4; i++)
	{
		if (vis[i] == 2) continue;

		vector<int> path;
		for (int j = i; vis[j] != 2; j = nex[j])
		{
			path.push_back(j);
			vis[j] = 2;
		}

		int sum = 0;
		for (auto p : path)
		{
			if (~ref[p])
			{
				sum += book[ref[p]] != i;
				book[ref[p]] = i;
			}
		}
		for (int p : path)
			ans[p] = sum;
	}
	int q;
	std::cin >> q;
	while (q--)
	{
		int x, y;
		string s;
		std::cin >> x >> y >> s;
		int hash = (x - 1) * m * 4 + (y - 1) * 4;
		if (s == "below") hash += 1;
		else if (s == "left") hash += 2;
		else if (s == "right") hash += 3;
		cout << ans[hash] << endl;
	}
	return 0;
}
