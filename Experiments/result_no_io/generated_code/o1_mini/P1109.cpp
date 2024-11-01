#include<stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    long long a[50];
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    long long L, R;
    scanf("%lld %lld", &L, &R);
    if(n ==1){
        if(a[0] >= L && a[0] <= R){
            printf("0");
        }
        else{
            printf("-1");
        }
    }
    else{
        long long surplus=0, deficit=0;
        for(int i=0;i<n;i++){
            if(a[i] > R) surplus += (a[i] - R);
            if(a[i] < L) deficit += (L - a[i]);
        }
        if(surplus >= deficit){
            printf("%lld", deficit);
        }
        else{
            printf("-1");
        }
    }
}