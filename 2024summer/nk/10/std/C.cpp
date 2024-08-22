#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair <LL, LL> point;

#define x first
#define y second
#define cp const point &
point operator + (cp a, cp b) { return {a.x + b.x, a.y + b.y}; }
point operator - (cp a, cp b) { return {a.x - b.x, a.y - b.y}; }
LL det (cp a, cp b) { return a.x * b.y - b.x * a.y; }

int half (cp a) { return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : 0;}

void work () {
	int n;
	cin >> n;
	vector <pair <point, LD>> b;
	for (int i = 0; i < n; i++) {
		LD p; int x, y;
		cin >> p >> x >> y;
		b.push_back({{x, y}, p});
	}
	LD ans = 0;
	for (int i = 0; i < n; i++) {
		auto a = b;
		swap(a[0], a[i]);
		auto [base, pbase] = a[0];
		for (int j = 1; j < n; j++) a[j].first = a[j].first - base;
		a.erase(a.begin());
		sort(a.begin(), a.end(), [](auto u, auto v) {
			auto [a, pa] = u;
			auto [b, pb] = v; 
			int sign = half (a) - half(b);
			if (sign) return sign > 0;
			return det(a, b) > 0;
		});
		int cnt = 0;
		LD logs = 0;
		auto add = [&] (LD p, int d) {
			if (p == 0) cnt += d;
			else logs += log(p) * d;
		};
		auto eval = [&] () -> LD{
			if (cnt) return 0;
			return exp(logs);
		};
		for (int i = 0; i < a.size(); i++) {
			add (a[i].second, 1);
		}
		for (int i = 0, j = 0; i < a.size(); i++) {
			while (j - i < (int) a.size() && det(a[i].first, a[j % a.size()].first) >= 0) {
				add (a[j++ % a.size()].second, -1);
			}
			// cerr << "base = " << base.x << " " << base.y << ", ";
			// cerr << "ai = " << (a[i].first + base).x << " " << (a[i].first + base).y << ", ";
			// cerr << "eval = " <<  eval() << " " << exp(logs) << " ~~ " << i << " " << j;
			// cerr << " DET = " <<  det(base, a[i].first + base) << endl;
			ans += eval() * (1 - pbase) * (1 - a[i].second)* det(base, a[i].first + base);
			add (a[i].second, 1);
		}
	}
	cout << fixed << setprecision(10) << ans / 2 << '\n';

}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T = 1;
	cin >> T;
	for (int ca = 1; ca <= T; ca ++)
		work();
}

