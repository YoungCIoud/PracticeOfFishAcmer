#define ll long long
#define ull unsigned long long
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int M = 1e5 + 5;
ll mod = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int n;
	cin >> n;
	vector<vector<ll>> f(n / 2 + 1, vector<ll>(n / 2 + 1, 0));
	f[0][0] = 1;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	sort(a.begin(), a.end());
	a.emplace_back(0);
	int cur = a[0];
	int cnt = 1;
	for (int i = 2; i <= n + 1; ++i) {
		if (a[i - 1] != cur) {
			ll d = 1;
			for (ll j = 2; j <= cnt; ++j) {
				d = d * j % mod;
			} 
			for (int j = i / 2; j <= min(i - 1, n / 2); ++j) {
				int k = i - 1 - j;
				for (int x = cnt; x >= 0; --x) {
					int y = cnt - x;
					if (k - y >= 0 && j - x >= 0) {
						f[j][k] = (f[j][k] + (f[j - x][k - y] * d) % mod) % mod;
					} 
				}
			}
			cnt = 1;
			cur = a[i - 1];
		}
		else {
			cnt++;
		}
	}
	cout << f[n / 2][n / 2] % mod << endl;
    return 0;
}