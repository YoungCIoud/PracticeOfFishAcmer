#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n, s;
int a[200005];

bool check(int mid)
{
	int cnt[3] = { 0 }, sum = 0;
	for (int i = 0; i < mid; i++)
	{
		sum += a[i];
		cnt[a[i] % 3]++;
	}
	if (cnt[1] > cnt[2])
	{
		cnt[1] -= cnt[2];
		sum += cnt[1] / 2 + 2 * cnt[1] % 2;
	}
	else
	{
		cnt[2] -= cnt[1];
		sum += cnt[2];
	}
	return sum <= s * 3;
}

signed main()
{
	cin >> n >> s;
	for (int i = 0; i < n; i++) cin >> a[i];
	sort(a, a + n);
	s -= 2;
	n -= 2;
	int l = 0, r = n;
	while (l <= r)
	{
		int m = l + r >> 1;
		if (check(m)) l = m + 1;
		else r = m - 1;
	}
	cout << 2 + r;
	return 0;
}
