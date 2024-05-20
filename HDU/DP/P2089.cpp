#include <cstring>	// memset
#include<iostream>
using namespace std;
const int N = 1e6, LEN = 6;
int digit[LEN+5], dp[LEN+5][10];  //dp[i][j] i位数中首位是j的符合条件的数的个数
void init()
{
	dp[0][0] = 1;
	for (int i = 1; i <= LEN; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				if (j != 4 && (j != 6 || k != 2))
					dp[i][j] += dp[i - 1][k];
}

int solve(int num)
{
	int len = 0;
	memset(digit, 0, sizeof digit);
	while (num)
	{
		digit[++len] = num % 10;
		num /= 10;
	}
	int ans = 1;
	// 此计算[0,n-1)的值,所以在初始时假设n是符合条件的数并初始化ans为1
	for (int i = len; i; i--)
	{
		for (int j = 0; j < digit[i]; j++)
			if (j != 4 && (j != 2 || digit[i + 1] != 6))
				ans += dp[i][j];
		// 若发现n是不符合条件的数,则ans--(因为一开始把n看作了符合条件的数 )
		if (digit[i] == 4 || digit[i] == 2 && digit[i + 1] == 6)
		{
			ans--;
			break;
		}
	}
	return ans;
}

int main()
{
	int n, m;
	init();
	while ((cin >> n >> m) && m)
		cout << solve(m) - solve(n - 1);
	return 0;
}
