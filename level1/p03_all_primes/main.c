#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int n;
bool st[1010];
vector<int>primes;
DWORD start,yend;
int main(){
    start=GetTickCount();
    n=1000;
    for(int i=2;i<=n;i++){
        if(!st[i]) primes.push_back(i);
        for(auto prime : primes ){
            if(prime>n/i) break;
            st[prime*i]=true;
            if(i%prime==0) break;
        }
    }
    for (auto i:primes) printf("%d ",i);
    yend=GetTickCount();
    printf("\n%dms",yend-start);
}
