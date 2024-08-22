#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair <int, int> pii;


void work() {
	int n, m; LD k, r;
	cin >> n >> m >> k >> r;
	vector <int> a;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	int see = min(n, m + 320), need = see - m;
	for (int i = 0; i < n - see; i++) r = k * a[i] + (1 - k) * r;
	a.erase(a.begin(), a.begin() + n - see);
	vector <LD> f(need + 1, -1e18);
	f[0] = r;
	auto check = [] (LD &x, LD y) {
		x = max(x, y);
	};
	for (auto p : a) {
		vector <LD> g = f;
		for (int j = 0; j <= need; j++) if (f[j] >= 0) {
			check(g[min(j + 1, need)], k * p + (1 - k) * f[j]);
		}
		f = move(g);
	}
	cout << fixed << setprecision(12) << f[need] << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T = 1;
	cin >> T;
	for (int ca = 1; ca <= T; ca ++) {
		work();
	}
}

