#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 5e5, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;
// 题目要求前k大的[l, r]段异或值之和.
// 进行前缀和处理之后, 转化为求求前k大的异或对(l, r)(其中l < r)之和.
// 若将l < r这个条件放在一个正方形中, 
// 会发现满足此条件的区域是主对角线两侧的一个三角形之一.
// 我们要在这个三角形区域求前k大的(l, r)异或对的和.
// 如果我们建立字典树后直接查询, 
// 就有可能出现查出的(l, r)在另一半三角形区域中.
// 若对于每个r我们只查询一次, 就可以先查询r再插入r.
// 但这题每个点要查询多次.
// 可以忽略l < r这个条件, 此时查询的区域就是整个矩形.
// 由于主对角线两侧是对称的且主对角线上的异或对结果为0,
// 所以可以转化为求前2k大的异或对之和再除2
// 具体的:
// 建01字典树,插入的值是异或前缀和,
// 并在每个点维护有多少的数经过了这个点
// 然后先查询一遍每个点异或值的最大值放入堆中(记录是那个点的第几大的值)
// 把一个数从堆取出来的时候,插入这个点下一个排名的值
int n, k;
int pre[N + 5];
struct trie
{
	int s[2], cnt;
}t[N * 34];
int cnt = 1;
void insert(int val)
{
	int cur = 1;
	for (int i = 32; ~i; i--)
	{
		int bit = val >> i & 1;
		if (t[cur].s[bit] == 0)
			t[cur].s[bit] = ++cnt;

		cur = t[cur].s[bit];
		t[cur].cnt++;
		//cout << cur << " ";
	}
}
// 返回一个数res，res满足:
// 严格小于res的数最多有th个
// 严格小于res + 1的数至少有th + 1个
int quiry(int val, int th)
{
	//cout << val << " ";
	int cur = 1, res = 0;
	for (int i = 32; ~i; i--)
	{
		int bit = val >> i & 1;
		//cout << t[cur].s[bit] << ":" << t[t[cur].s[bit]].cnt << "," << th;
		if (t[t[cur].s[bit]].cnt < th)
		{
			//cout << "反";
			th -= t[t[cur].s[bit]].cnt;
			cur = t[cur].s[bit ^ 1];
			res |= (1ll << i);
		}
		else
		{
			//cout << "同";
			cur = t[cur].s[bit];
		}
	}
	//cout << " " << res << endl;
	return res;
}
struct node {
	int val, id, rank;
	bool operator<(const node& x) const{
		return val < x.val;
	}
};
priority_queue<node> q;
signed main()
{
	cin >> n >> k;
	insert(pre[0]);
	for (int i = 1; i <= n; i++)
	{
		cin >> pre[i];
		pre[i] ^= pre[i - 1];
		insert(pre[i]);
	}
	//cout << endl;
	
	for (int i = 0; i <= n; i++)
	{
		q.push({ quiry(pre[i], n + 1), i , n + 1 });
	}

	int ans = 0;
	for (int i = 0; i < k + k; i++)
	{
		// 当前值 编号 比当前还小的数的个数
		auto [val, id, rk] = q.top();
		q.pop();
		ans += val;
		if (rk)
			q.push({ quiry(pre[id], rk - 1), id, rk - 1 });
	}
	cout << ans / 2 << endl;
	return 0;
}
