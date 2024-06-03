#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 2e5, A = 1e6, Inf = 1e18;
int h[A + 5], back[A + 5];
signed main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		h[a]++;
	}
	for (int i = A; i; i--)
	{
		back[i] = back[i + 1] + h[i];
	}

	int ans = 0;
	for (int i = 1; i <= A; i++)
	{
		if (!h[i]) continue;
		
		ans += (h[i] - 1) * h[i] / 2;
		ans += (back[i] - h[i]) * h[i];
		for (int j = 2; j * i <= A; j++)
			ans += h[i] * back[i * j];
	}
	cout << ans;
}
