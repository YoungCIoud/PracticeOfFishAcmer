# [7_13](vjudge.net/contest/638765#overview)
## B(二分图最大匹配匈牙利算法)
### 题意
二维平面上有两组点,
前一组的某一点a可与后一组的某一点b形成匹配当且仅当a的横纵坐标都小于b的.  
求最大匹配.
### 解
二分图最大匹配考虑匈牙利算法(以此题为例):
```c++
bool mp[N + 5][N + 5], vis[N + 5];
int p[N + 5]; // p[i]表示b组i点的匹配是r组p[i]点
bool match(int cur)
{
	for (int i = 1; i <= n; i++)
	{
		// cur 和 i 之间无边 或者 在此次匹配中i已经访问过了
		if (!mp[cur][i] || vis[i]) continue;
		
		vis[i] = true;
		// 如果b组i这个点没有匹配或者
		// r组p[i]这个点能找到其他匹配从而把i留给cur
		if (p[i] == 0 || match(p[i]))
		{
			p[i] = cur;
			return true;
		}
	}
	return false;
}

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		r[i] = { x, y };
	}
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		b[i] = { x, y };
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			mp[i][j] = (r[i][0] < b[j][0] && r[i][1] < b[j][1]);
	// 以上为建边

	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		// 注意此处需要重置
		fill(vis + 1, vis + 1 + n, false);
		if (match(i)) ans++;
	}
	cout << ans << endl;
}
```

## D
### 题意
三组数中每组取一个数求和,求前k大的和.
### 解
1. 可以直接暴力循环,当ijk的乘积大于k时break一次
1. 先求出前两组前min(k,x*y)大的数,在拿这组数跟第三组求前k大的数
## F
### 题意
有一个二维表,这个表满足a[i][j]=i*j, 求这个表中第K大的数.
### 解
考虑另一个问题: 求一个数在表中是第几大的.
很容易想到二分就能解决这个问题.

所以我们二分答案计算严格比这个数小的有多少个.
## G
### 题意
将一个数用二进制表示,
在其末尾加上一个1或0后反转(忽略先导零)的到一个新的二进制数,
这个二进制数的十进制形式为一个新得到的数.
对于这个数,又可以进行如上操作得到新的数.

给出两个数x, y,判读y是否能够由x通过若干次操作后得出y.
### 解
解题的关键就在与发现最终的能由x得出的答案一定是一段连续的1中间夹着x二进制形式的一些变式.

具体看代码.

~~代码太难写了QAQ~~
## I
### 题意
给出一个包含N个数的序列A,
需要将其划分成若干个连续的子序列,
且第i个子序列里数的和是i的倍数，
求有多少种不同的划分.
### 解
可以设计以`dp[i][j]`表示将前i个数分成j组的划分数,转移方程:
```math
dp[i][j] = dp[i][j] + dp[k][j - 1]
```
其中k满足[k+1,i]这一段的和是j的倍数
所以得出n三次方的dp:
```c++
for (int i = 1; i <= n; i++)
	{
		dp[i][1] = 1;
		for (int j = 2; j <= i; j++)
		{
			for (int k = j - 1; k < i; k++)
			{
				if ((pre[i] - pre[k]) % j == 0)
				{
					dp[i][j] = (dp[i][j] + dp[k][j - 1]) % Mod;
				}
			}
		}
	}
```
这样转移的时间复杂度肯定是不满足要求的.

观察到在每次寻找k的时候都要从前王后遍历一遍,
而且找到的k满足pre\[i\]和pre\[k\]关于j同余,
所以想到可以开一个数组记录dp[k][j - 1]的和.

设same\[j\]\[m\]表示目前所有模j余m的pre[k]对应的dp[k][j - 1]的和,
每次转移前先处理出same就可以将时间复杂度讲到n方:
```c++
for (int i = 1; i <= n; i++)
	{
		dp[i][1] = 1;
		for (int j = 2; j <= i; j++)
		{
			same[j][pre[i - 1] % j] += dp[i - 1][j - 1];
			same[j][pre[i - 1] % j] %= Mod;
		}

		for (int j = 2; j <= i; j++)
		{
			dp[i][j] += same[j][pre[i] % j];
			dp[i][j] %= Mod;
			// same[j][pre[i] % j] 相当于对dp[k][j - 1]的求和
		}
	}
```
最后统计一下dp[n][j]就是答案.
