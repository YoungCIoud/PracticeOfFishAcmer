#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

const int MX = 3e5 + 23;

int n, a[MX];
vector<int> f, g;

LL qqq() {
  int ans = 0;
  for (int i = 0, j = (int)f.size() - 1, k = (int)g.size() - 1; i < f.size(); ++i) {
    while (j >= 0 && f[i] > (int)f.size() - 1 - j) --j;
    while (k >= 0 && f[i] - ((int)g.size() - 1 - k) > -g[k]) --k;
    if (j < i) break;
    ans = max(ans, i + 1 + k + 1);
  }
  return ans;
}

void solve() {
  f.clear();
  g.clear();
  cin >> n;
  int addition = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (a[i] < 0) f.push_back(-a[i]);
    else if (a[i] == 0) ++addition;
    else g.push_back(a[i]);
  }
  reverse(f.begin(), f.end());
  LL ans = qqq();
  swap(f, g);
  ans = max(ans, qqq());
  cout << ans + addition << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) solve();
  return 0;
}