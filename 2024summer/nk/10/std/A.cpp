#include<bits/stdc++.h>
using namespace std;
int ycnt, ncnt;
char ss[10];
int main(){
    cin >> ss;
    for(int i = 0; i <= 4; i++){
        if(ss[i] == 'Y') ycnt++;
        else if(ss[i] == 'N') ncnt++;
    }
    if(ycnt >= 4) cout << "1\n";
    else if(ncnt >= 2) cout << "-1\n";
    else cout << "0\n";
    return 0;
}