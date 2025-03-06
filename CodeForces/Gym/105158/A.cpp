#include<bits/stdc++.h>
using namespace std;
//#define int long long 
using i128=__int128_t;
using i64=long long;
#define IOS ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

void solve() {
       int n,d;
       cin>>n>>d;
       i64 cur=1234567890ll+d;
       int nn=n;
       while(nn){
           cur=cur*10;
           nn=nn/10;
       }
       i64 k=cur%n;
       k=n-k;
       cur+=k;
       i64 ans=cur/n;
       cout<<ans<<'\n';
}
signed main() {
    IOS;
    
    int t = 1;
    cin >> t;

    while (t--) {
        solve();
    }
}