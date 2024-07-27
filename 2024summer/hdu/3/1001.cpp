#include<bits/stdc++.h>
//using namespace std;
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string
using i64 = long long;
constexpr i64 Mod = 998244353;
constexpr int N = 1e6;

i64 f[N + 5], ans[N + 5];
int main()
{
	int n;
	std::cin >> n;
	f[1] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j+= i)
			f[j + 1] = (f[j + 1] + f[i]) % Mod;

	for (int i = 1; i <= n; i++)
	{
		for (int j = i + i; j <= n; j += i)
			ans[j] = (ans[j] + f[i]) % Mod;
		std::cout << (ans[i] + f[i]) % Mod << " \n"[i == n];
	}
	return 0;
}
