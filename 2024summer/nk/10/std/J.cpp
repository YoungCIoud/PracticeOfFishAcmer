#include <bits/stdc++.h>

#define debug(...) ;//fprintf(stderr, __VA_ARGS__)
#define LL long long

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

const int MX = 1e6 + 6;

int t1[MX], t2[MX], T1[MX], T2[MX], tot = 0;
struct edge {
  int node, next;
} h[MX * 2 * 4];
void addedge(int u, int v, int *head, int flag = true) {
  h[++tot] = (edge) {v, head[u]};
  head[u] = tot;
  if (flag) {
    addedge(v, u, head, false);
    //debug("%d %d\n", u, v);
  }
}

int d1[MX], d2[MX], n;
int fa[MX], size[MX], good[MX], val[MX];

int find(int x) {
  return fa[x] == x ? x : x = find(fa[x]);
}

void link(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return;
  val[y] = val[x];
  if (size[x] < size[y])
    std::swap(x, y);
  fa[y] = x;
  size[x] += size[y];
  good[x] &= good[y];
}

void init() {
  for (int i = 1; i <= n; ++i) {
    t1[i] = t2[i] = T1[i] = T2[i] = 0;
  }
  tot = 0;
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
    size[i] = 1;
    d1[i] = d2[i] = 0;
  }
}

// std::vector<int> tmp[MX];
void remake() {
  for (int i = 1; i <= n; ++i) {
    for (int z = t1[i], d; z; z = h[z].next) {
      d = h[z].node;
      if (find(d) != find(i)) {
        addedge(find(i), find(d), T1, false);
//        tmp[find(i)].push_back(find(d));
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int z = t2[i], d; z; z = h[z].next) {
      d = h[z].node;
      if (find(d) != find(i)) {
        addedge(find(i), find(d), T2, false);
//        tmp[find(i)].push_back(find(d));
      }
    }
  }
}

int pa[MX];
int flag[MX], tag[MX];
void dfs(int x, int f) {
  pa[x] = f;
  flag[x] = true;
  for (int i = T2[x], d; i; i = h[i].next) {
    d = h[i].node;
    if (flag[d]) {
      ++tag[d];
    }
  }
  for (int i = T1[x], d; i; i = h[i].next) {
    d = h[i].node;
    if (d == pa[x]) continue;
    dfs(d, x);
    if (tag[x] != 1)
      good[x] = false;
    tag[x] = false;
  }
  flag[x] = false;
}

bool dfs2(int x, int f){
  for (int i = t2[x], d; i; i = h[i].next) {
    d = h[i].node;
    if (d == f) continue;
    pa[d] = x;
    if (!dfs2(d, x))
      return false;
  }
  val[x] = x;
  for (int i = t1[x], d; i; i = h[i].next) {
    d = h[i].node;
    d = find(d);
    if (val[d]) {
      if (pa[val[d]] != x)
        return false;
      link(x, d);
    }
  }
  return true;
}

int check(int root) {
  for(int i = 1; i <= n; ++i) {
    val[i] = 0;
    fa[i] = i;
    size[i] = 1;
    pa[i] = 0;
  }
  return dfs2(root, 0) ? root : -1;
}

int buc[MX];
void solve() {
  std::cin >> n;
  init();
  for (int i = 2, x; i <= n; ++i) {
    std::cin >> x;
    addedge(x ,i, t1);
    ++d1[i], ++d1[x];
  }
  for (int i = 2, x; i <= n; ++i) {
    std::cin >> x;
    addedge(x, i, t2);
    ++d2[i], ++d2[x];
  }

  int bad = 0;
  for (int i = 1; i <= n; ++i) {
    good[i] = d1[i] == d2[i];
    if (d2[i] > d1[i] + 1) {
      bad = true;
    }
  }

  if (bad) {
    std::cout << -1 << "\n";
    // puts("-1");
    return;
  }

  for (int i = 1; i <= n; ++i) {
    for (int z = t1[i], d; z; z = h[z].next)
      buc[d = h[z].node] = true;
    for (int z = t2[i], d; z; z = h[z].next) {
      if (buc[d = h[z].node]) {
        link(i, d);
      }
    }
    for (int z = t1[i], d; z; z = h[z].next)
      buc[d = h[z].node] = false;
    
  }

  remake();
  dfs(find(1), 0);

  int ans = -1;
  for (int i = 1; i <= n; ++i) {
    if (i == find(i) && good[i]) {
      ans = check(i);
      break;
    }
  }
  std::cout << ans << "\n";
  // printf("%d\n", ans);
}

int main() {
  std::ios::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) solve();
  return 0;
}
