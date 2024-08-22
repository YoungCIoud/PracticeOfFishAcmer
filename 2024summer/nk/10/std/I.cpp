#include <bits/stdc++.h>
using namespace std;

void work() {
	int n;
	cin >> n;
	vector <int> p(n), a(n);
	for (int i = 0; i < n; i++) a[i] = i;
	for (int i = 0; i < n; i++) cin >> p[i], p[i]--;
	vector <string> ans;
	while (p != a) {
		vector < pair <int, int> > runs;
		vector <int> q(n);
		for (int i = 0; i < n; i++) q[p[i]] = i;
		for (int i = 0; i < n; ) {
			int j = i + 1;
			while (j < n && q[j] > q[j - 1]) j++;
			runs.push_back({i, j});
			i = j;
		}
		string w = "";
		for (int i = 0; i < n; i++) w += 'B';
		for (int i = 0; i < runs.size(); i += 2) {
			auto [l, r] = runs[i];
			for (int j = l; j < r; j++) w[q[j]] = 'A';
		}
		ans.push_back(w);
		vector <int> pp;
		for (int i = 0; i < n; i++) if (w[i] == 'A') pp.push_back(p[i]);
		for (int i = 0; i < n; i++) if (w[i] == 'B') pp.push_back(p[i]);
		p = move(pp);
	}
	reverse(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (auto s : ans) cout << s << '\n';
}

int main() {
//	ios::sync_with_stdio(false); cin.tie(0);
	int T = 1;
	cin >> T;
	for (int ca = 1; ca <= T; ca ++) {
		work();
	}
}

