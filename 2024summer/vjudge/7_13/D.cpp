#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 1e3, M = 1e5, Inf = 1e16, Mod = 1e9 + 7;
// 匈牙利算法找二分图最大匹配
int a[N + 5];
int b[N + 5];
int c[N + 5];
signed main()
{
	int x, y, z, K;
	cin >> x >> y >> z >> K;
	for (int i = 1; i <= x; i++)
		cin >> a[i];
	sort(a + 1, a + 1 + x, greater<int>());
	for (int i = 1; i <= y; i++)
		cin >> b[i];
	sort(b + 1, b + 1 + y, greater<int>());
	for (int i = 1; i <= z; i++)
		cin >> c[i];
	sort(c + 1, c + 1 + z, greater<int>());

	vector<int> ans;
	for (int i = 1; i <= x; i++)
	{
		for (int j = 1; j <= y; j++)
		{
			for (int k = 1; k <= z; k++)
			{
				if (i * j * k > K) break;
				ans.push_back(a[i] + b[j] + c[k]);
			}
		}
	}
	sort(ans.begin(), ans.end(), greater<int>());
	for (int i = 0; i < K; i++)
		cout << ans[i] << endl;
	return 0;
}
