#include<iostream>
using namespace std;
const int N = 1e6;
int cnt[N + 5];

int main()
{
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a;
		scanf("%d", &a);
		cnt[a]++;
	}
	bool head = 0;
	// 处理1和2一起出现的
	while (cnt[1] && cnt[2])
	{
		if (cnt[1] == 2 && cnt[2] == 1)
		{
			cnt[1] = cnt[2] = 0;
			if (head) printf("*");
			printf("(1+1+2)");
		}
		else
		{
			cnt[1]--, cnt[2]--;
			if (head) printf("*");
			printf("(1+2)");
		}
		head = 1;
	}
	// 处理1
	while (cnt[1]>=3&&cnt[1]!=4)
	{
		if (head) printf("*");
		printf("(1+1+1)");
		cnt[1] -= 3;
		head = 1;
	}
	if (cnt[1] == 4)
	{
		if (head) printf("*");
		printf("(1+1+1+1)");
		cnt[1] = 0;
		head = 1;
	}
	else if (cnt[1] == 2)
	{
		if (head) printf("*");
		printf("(1+1)");
		cnt[1] = 0;
		head = 1;
	}
	else if (cnt[1] == 1)
	{
		for(int i=3;i<=N;i++)
			if (cnt[i])
			{
				cnt[i]--, cnt[1]--;
				if (head) printf("*");
				printf("(1+%d)",i);
				head = 1;
				break;
			}
	}
	for (int i = 1; i <= N; i++)
		while (cnt[i]--)
		{
			if (head) printf("*");
			printf("%d",i), head = 1;
		}
	return 0;
}
