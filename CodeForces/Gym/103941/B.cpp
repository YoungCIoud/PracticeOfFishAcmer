#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod=998244353;
#define IOS ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

void solve() {
    int n;
    string s;
    cin>>s;
    n=s.length();
    s=" "+s+s;
    
    map<char,int>mp;
    mp['a']=1;
    mp['e']=2;
    mp['h']=3;
    mp['n']=4;
    int ans=0;
    for(int k=1;k<=min(15ll,n);k++){
            vector<int>dp(2*n+1,0);
            int m=min(n,k);
        for(int i=m;i<m+n;i++){
                int cur=0;
                int d=1;
                for(int j=i;j>=max(m,i-15);j--){
                        cur=(cur+mp[s[j]]*d)%mod;
                        d*=31;
                        dp[i]=max(dp[j-1]+cur,dp[i]);
                }
                //if(m==5) cout<<i<<": "<<dp[i]<<"\n";


            }
            //cout<<dp[m+n-1]<<'\n';
            ans=max(dp[n+m-1],ans);
    }
    
    cout<<ans<<"\n";

}
signed main() {
    IOS;
    
    int t = 1;
    //cin >> t;

    while (t--) {
        solve();
    }
}