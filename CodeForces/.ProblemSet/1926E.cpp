#include<iostream>
using namespace std;

void solve()
{
	int n, k;
	cin >> n >> k;
	int base = 1;
	while ((n + 1) / 2 < k) k -= (n + 1) / 2, n /= 2, base++;
	cout << (k - 1 << base) + (1 << base - 1) << endl;
}

int main()
{
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}
