#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
void solve(int n,char a,char b,char c) {
    if (n==1) {
        printf("%c -> %c\n",a,c);
        return ;
    }
    solve(n-1,a,c,b);
    printf("%c -> %c\n",a,c);
    solve(n-1,b,a,c);
}

int main(){
    char a='A',b='B',c='C';
    solve(64,a,b,c);
}
