// 三个数的最小公倍数等于一个数与另外两个数的最小公倍数的最小公倍数
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;

int gcd(int x, int y) {
	return y ? gcd(y, x % y) : x;
}
int lcm(int x, int y) {
	return x * y / gcd(x, y);
}

signed main()
{
	int a, b, c;
	cin >> a >> b >> c;
	cout << lcm(a, lcm(b, c));
	return 0;
}
