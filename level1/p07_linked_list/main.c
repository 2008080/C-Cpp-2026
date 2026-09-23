#include<bits/stdc++.h>
using namespace std;
const int N=110;
int e[N],h,ne[N],n=100;
int main(){
    h=1;
    for(int i=1;i<=n;i++){
        e[i]=rand()%10+1;
        ne[i]=i+1;
    }
    ne[n]=-1;
    for(int i=h;i!=-1;i=ne[i]){
        printf("%d ",e[i]);
    }
    int p,q=h;
    for(int i=ne[h];i!=-1;){
        p=i;
        int t=ne[p];
        ne[p]=q;
        i=t;
        q=p;
    }
    ne[h]=-1;
    h=p;
    int res=-1;
    for(int i=h;i!=-1;i=ne[i]){
        if(e[i]==5){
            res=i;
            break;
        }
    }
    printf("\n%d\n",res);
    if(res==-1){
        printf("%d\n",res);
        return 0;
    }
    int ans=-1;
    for(int i=ne[res];i!=-1;i=ne[i]){
        if(e[i]==5){
            ans=i;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
