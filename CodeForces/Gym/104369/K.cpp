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

ll qpow(ll a, int p)
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

ll inv(int a)
{
	return qpow(a, Mod - 2);
}

int main()
{
	int n, k, a, b;
	cin >> n >> k >> a >> b;

	if (a == b)
	{
		cout << 0 << endl;
		return 0;
	}
	ll p = qpow(b - a, k) * qpow(b, n - k) % Mod;
	ll q = (qpow(b, n) - qpow(b - a, n) + Mod) % Mod;
	// cout << p << " " << q << endl;
	cout << p * inv(q) % Mod;
}
