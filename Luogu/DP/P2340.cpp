#include<iostream>
using namespace std;
int dp[800000 + 5];
int main()
{
    memset(dp, -0x3f, sizeof dp);
    dp[400000] = 0;
    int n; cin >> n;
    for (int t = 1; t <= n; t++)
    {
        int a, b;
        cin >> a >> b;
        if (a < 0)
            for (int i = 0; i - a <= 800000; i++)
                dp[i] = max(dp[i], dp[i - a] + b);
        else
            for (int i = 800000; i >= a; i--)
                dp[i] = max(dp[i], dp[i - a] + b);
    }
    int ans = 0;
    for (int i = 400000; i <= 800000; i++)
        if(dp[i]>=0)
            ans = max(ans, i + dp[i] - 400000);
    cout << ans;
    return 0;
}
