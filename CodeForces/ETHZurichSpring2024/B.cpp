#include<iostream>
#include<map>
#include<unordered_map>
#include<string>
#include<math.h>

//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 1e5, Inf = (1ll << 31) - 1, Mod = 1e9 + 7;
int deg[N + 5];

ll qpow(int a, int p)
{
	ll res = 1;
	for (; p; a = a * a % Mod, p >>= 1)
	{
		if (p & 1)
		{
			res = res * a % Mod;
		}
	}
	return res;
}

int main()
{
	int n;
	cin >> n;
	int ans = n - 1;

	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		cin >> a >> b;
		deg[a]++;
		deg[b]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if (deg[i] >= 2)
		{
			ans = (ans + qpow(2, deg[i]) - deg[i] - 1 + Mod) % Mod;
		}
	}
	cout << ans;
}
