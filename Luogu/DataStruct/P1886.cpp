// 单调队列
#include<iostream>
using namespace std;
int a[100000+5],p[100005],q[100005];
int n, k;

bool cmp1(int x, int y)
{
	return x >= y;
}

bool cmp2(int x, int y)
{
	return x <= y;
}

void solve(bool (*cmp)(int x,int y))
{
	int head = 1, tail = 0;
	for (int i = 1; i <= n; i++)
	{
		while (tail >= head && (*cmp)(p[tail], a[i])) tail--;
		p[++tail] = a[i], q[tail] = i;
		if (q[head] <= i - k) head++;
		if (i >= k) cout << p[head] << " ";
	}
	cout << endl;
}

int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	solve(cmp1), solve(cmp2);
	return 0;
}
