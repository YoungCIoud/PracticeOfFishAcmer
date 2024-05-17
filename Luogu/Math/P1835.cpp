#include<iostream>
#define int long long
using namespace std;
const int N = 1e6;
bool notP[N + 5];
signed main()
{
	int l, r;
	cin >> l >> r;
	for (int i = 2; i * i <= r; i++)
	{
		// 判断质数
		bool isp = true;
		for(int j=2;j*j<=i;j++)
			if (i % j == 0)
			{
				isp = false;
				break;
			}
		if (!isp) continue;
		for (int j = max(i * 2, (l + i - 1) / i * i); j <= r; j += i)
			notP[j-l] = true;
	}
	int ans = 0;
	for (int i = 0; i <= r - l; i++)
		if (!notP[i]) ans++;
	if (l == 1) ans--;
	cout << ans;
	return 0;
}
