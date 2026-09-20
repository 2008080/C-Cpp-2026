#include<bits/stdc++.h>
using namespace std;
int a;
bool check(int x){
    if(x<2)return false;
    for(int i=2;i<=x/i;i++){
        if(x%i==0)return false;
    }
    return true;
}
int main(){
    scanf("%d",&a);
    if(check(a))puts("Yes");
    else puts("No");
}
