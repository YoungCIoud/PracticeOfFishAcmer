#include <bits/stdc++.h>

#define debug(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef unsigned long long ULL;
typedef pair<int, int> pii;

const int MX = 100000 + 23;
const int INF = 1e9;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

// 2->3 3->0 0->1 1->2

ULL getha(pii a) { return a.first * 100007u + a.second; }
template <class T,int P = 2119969/*,451411,1141109,2119969*/>
struct hashmap {
T id[P]; int val[P];
int R[P]; // del: few clears
hashmap() {
  for (int i = 0; i < P; ++i) id[i] = {-1, -1};
  }
int get(T x) const {
	for (int i = int(getha(x) % P), j = 1; ~id[i]; i = (i + j) % P, j = (j + 2) % P /*unroll if needed*/) {
		if (id[i] == x) return val[i]; }
	return 0; }
int& operator [] (T x) {
	for (int i = int(getha(x) % P), j = 1;       ; i = (i + j) % P, j = (j + 2) % P) {
		if (id[i] == x) return val[i];
		else if (id[i] == make_pair(-1, -1)) {
			id[i] = x;
			R[++R[0]] = i;  // del: few clears
			return val[i]; } } }
void clear() { // del: few clears
for (int &x = R[0]; x; id[R[x]] = {-1, -1}, val[R[x]] = 0, --x); }
void fullclear() {memset(id, -1, sizeof id); R[0] = 0; } };

int n;

struct Point {
  int x, y, id;
};

struct HashFunc {
  unsigned int operator() (const pii &key) const {
    return (unsigned)key.first * 100007u + (unsigned)key.second; 
  }
};

vector<Point> P;
hashmap<pii> id;
// unordered_map<pii, int, HashFunc> id;

int X, Y, DIR;
string ans;

int to[4][MX];

bool cmp1(Point a, Point b) {
  if (a.y == b.y) return a.x < b.x;
  return a.y < b.y;
}

bool cmp2(Point a, Point b) {
  if (a.x == b.x) return a.y < b.y;
  return a.x < b.x;
}

void calcto() {
  sort(P.begin(), P.end(), cmp1);
  for (int i = 0; i < n; ++i) {
    if (i && P[i - 1].x + 1 == P[i].x
    && P[i - 1].y == P[i].y) {
      to[2][P[i].id] = to[2][P[i - 1].id] + 1;
    } else {
      to[2][P[i].id] = 0;
    }
  }
  reverse(P.begin(), P.end());
  for (int i = 0; i < n; ++i) {
    if (i && P[i - 1].x - 1 == P[i].x
    && P[i - 1].y == P[i].y) {
      to[0][P[i].id] = to[0][P[i - 1].id] + 1;
    } else {
      to[0][P[i].id] = 0;
    }
  }
  sort(P.begin(), P.end(), cmp2);
  for (int i = 0; i < n; ++i) {
    if (i && P[i - 1].x == P[i].x
    && P[i - 1].y + 1 == P[i].y) {
      to[3][P[i].id] = to[3][P[i - 1].id] + 1;
    } else {
      to[3][P[i].id] = 0;
    }
  }
  reverse(P.begin(), P.end());
  for (int i = 0; i < n; ++i) {
    if (i && P[i - 1].x == P[i].x
    && P[i - 1].y - 1 == P[i].y) {
      to[1][P[i].id] = to[1][P[i - 1].id] + 1;
    } else {
      to[1][P[i].id] = 0;
    }
  }
}

bool ok() {
  int Bound[4] = {-INF, -INF, INF, INF};
  for (auto [x, y, id] : P) {
    Bound[0] = max(Bound[0], x);
    Bound[1] = max(Bound[1], y);
    Bound[2] = min(Bound[2], x);
    Bound[3] = min(Bound[3], y);
  }
  id.clear();
  for (int i = 0; i < n; ++i) {
    id[{P[i].x, P[i].y}] = P[i].id;
  }

  sort(P.begin(), P.end(), cmp1);
  for (int i = 1; i < n && P[i].y == P[0].y; ++i) {
    static vector<int> r1, r2;
    r1.clear(); r2.clear();
    if (P[i - 1].x + 1 != P[i].x) {
      break;
    }
    
    int sum = 0;
    int x = P[i].x;
    int y = P[0].y;
    int d = 2;
    int cid = id[{x, y}];
    int b[4];
    memcpy(b, Bound, sizeof b);
    b[0] = P[i - 1].x;
    while (true) {
      int len = to[d][cid];
      if (d % 2 == 0) {
        len = min(len, abs(b[d] - x));
      } else {
        len = min(len, abs(b[d] - y));
      }
      if (len == 0) break;
      b[(d + 1) % 4] = (d + 1) & 1 ? y - dy[(d + 1) % 4]: x - dx[(d + 1) % 4];
      sum += len;
      

      r1.push_back(len);
      x = x + dx[d] * len;
      y = y + dy[d] * len;
      d = (d - 1 + 4) % 4;
      cid = id[{x, y}];
    }
    X = x;
    Y = y;
    DIR = ((d + 1) % 4) ^ 2;
    x = P[i - 1].x;
    y = P[0].y;
    d = 0;
    cid = id[{x, y}];
    memcpy(b, Bound, sizeof b);
    b[2] = P[i].x;
    while (true) {
      int len = to[d][cid];
      if (d % 2 == 0) {
        len = min(len, abs(b[d] - x));
      } else {
        len = min(len, abs(b[d] - y));
      }
      if (len == 0) break;
      b[(d - 1 + 4) % 4] = (d - 1 + 4) & 1 ? y - dy[(d - 1 + 4) % 4] : x - dx[(d - 1 + 4) % 4];
      sum += len;
      r2.push_back(len);
      x = x + dx[d] * len;
      y = y + dy[d] * len;
      d = (d + 1) % 4;
      cid = id[{x, y}];
    }
    if (sum != n) continue;
    else {
      ans.clear();
      reverse(r1.begin(), r1.end());
      for (int i = 0; i < r1.size(); ++i) {
        if (i) {
          ans.push_back('1');
        }
        for (int j = 0; j < r1[i]; ++j) {
          ans.push_back('0');
        }
      }
      r2[0]--;
      for (int i = 0; i < r2.size(); ++i) {
        if (i) {
          ans.push_back('1');
        }
        for (int j = 0; j < r2[i]; ++j) {
          ans.push_back('0');
        }
      }
      return true;
    }
  }
  return false;
}

void rotate() {
  for (int i = 0; i < n; ++i) {
    int x = P[i].x;
    int y = P[i].y;
    P[i].x = -y;
    P[i].y = x;
    for (int j = 2; j >= 0; --j)
      swap(to[j][i + 1], to[j + 1][i + 1]);
    // (1, 2) -> (-2, 1) counter clockwise 90 deg
  }
}

void rotans() {
  int tmpx = X;
  int tmpy = Y;
  X = -tmpy;
  Y = tmpx;
  DIR = (DIR + 1) % 4;
}

void solve() {
  cin >> n;
  P.clear();
  for (int i = 1; i <= n; ++i) {
    int x, y; cin >> x >> y;
    P.push_back({x, y, i});
  }
  calcto();
  for (int i = 0; i < 4; ++i) {
    if (ok()) {
      cout << ans.length() << endl;
      for (int j = i; j < 4; ++j) {
        rotans();
      }
      cout << X << " " << Y << " " << DIR << endl;
      cout << ans << endl;
      return;
    }
    rotate();

  }
  cout << -1 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  int t; cin >> t;
  while (t--) solve();
  return 0;
}