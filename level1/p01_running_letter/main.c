#include<bits/stdc++.h>
#include<cstdlib>
#include<windows.h>
using namespace std;
int main(){
    while (1) {
        int i=0;
        while(i<=50) {
            system("cls");
            for (int j=0;j<=i;j++) printf(" ");
            printf("hello world!\n");
            i+=1;
            Sleep(10);
        }
        while(i>=0) {
            system("cls");
            for (int j=0;j<=i;j++) printf(" ");
            printf("hello world!\n");
            i-=1;
            Sleep(10);
        }
    }
    //system("pause");
    return 0;
}
