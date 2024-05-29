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

int main()
{
	int n, m;
	cin >> n >> m;
	cout << n * m * (n - 1) * (m - 1) / 4;
	return 0;
}
