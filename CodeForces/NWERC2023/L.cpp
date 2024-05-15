#include<iostream>
using namespace std;
int n, k;
int shoot(int x, int y)
{
	string s;
	for (int i = max(x - 4, 1); i <= min(n, x + 4); i++)
	{
		cout << i << " " << y << endl;
		cin >> s;
		if (s == "sunk") return 1;
	}
		
	for (int j = max(y - 4, 1); j <= min(n, j + 4); j++)
	{
		cout << x << " " << j << endl;
		cin >> s;
		if (s == "sunk") return 1;
	}
	return 1;
}
 
int main()
{
	cin >> n >> k;
	string s;
	for (int i = 1; i <= n && k; i++)
		for (int j = (i % 5 == 0 ? 5 : i % 5); j <= n && k; j += 5)
		{
			cout << i << " " << j << endl;
			cin >> s;
			if (s == "hit")
				k -= shoot(i, j);
		}
	return 0;
}
