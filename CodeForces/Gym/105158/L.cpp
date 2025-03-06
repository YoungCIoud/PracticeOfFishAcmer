#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define IOS ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
void solve() {
       int n,m;
       cin>>n>>m;
       vector<int>a(m+1);
       for(int i=1;i<=m;i++) cin>>a[i];
       vector<int>b(22,0);
       for(int i=1;i<=21;i++) b[i]=pow(i,4);
       int mx=m;
       for(int i=1;i<=m;i++) mx+=a[i];

       vector<int> dp(m+1,mx);
       dp[0]=0;
       dp[1]=1+a[1];
       for(int i=2;i<=m;i++){
          for(int j=1;j<=std::min(21ll, i);j++){
               dp[i]=min(dp[i],dp[i-j]+b[j]+a[i]);
          }
       }
       cout<<dp[m]<<"\n";
}
signed main() {
    IOS;
    
    int t = 1;
    //cin >> t;

    while (t--) {
        solve();
    }
}