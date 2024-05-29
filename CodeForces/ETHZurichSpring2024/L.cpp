#include<iostream>
#include<map>
#include<unordered_map>
#include<string>
#include<math.h>
#include<stack>
#include<vector>

//#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
using ll = long long;
const int N = 1e5, Inf = (1ll << 31) - 1, Mod = 1e9 + 7;

int main()
{
	int n;
	cin >> n;
	stack<int> A, B;
	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		A.push(a);
	}
	vector<string> ans;
	int cur = 1;
	while (!A.empty())
	{
		while (!B.empty() && B.top() == cur)
		{
			//cout << "B C" << endl;
			ans.push_back("B C");
			B.pop();
			cur++;
		}
		while (!A.empty() && A.top() != cur)
		{
			//cout << "A B" << endl;
			ans.push_back("A B");
			B.push(A.top());
			A.pop();
		}
		if (!A.empty())
		{
			A.pop();
			//cout << "A C" << endl;
			ans.push_back("A C");
			cur++;
		}
	}
	while (!B.empty() && B.top() == cur)
	{
		//cout << "B C" << endl;
		ans.push_back("B C");
		B.pop();
		cur++;
	}
	if (cur == n + 1)
	{
		cout << ans.size() << endl;
		for (auto s : ans)
		{
			cout << s << endl;
		}
	}
	else
	{
		cout << -1 << endl;
	}

	return 0;
}
