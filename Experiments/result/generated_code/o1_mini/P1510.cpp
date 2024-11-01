#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int v,n,c;
    scanf("%d %d %d", &v, &n, &c);
    int *dp = (int*)malloc((c+1)*sizeof(int));
    for(int i=0;i<=c;i++) dp[i] = -1;
    dp[0]=0;
    for(int i=0;i<n;i++){
        int k,m;
        scanf("%d %d", &k, &m);
        if(m > c) continue;
        for(int e = c; e >= m; e--){
            if(dp[e - m] != -1){
                if(dp[e] < dp[e - m] + k){
                    dp[e] = dp[e - m] + k;
                }
            }
        }
    }
    int res = -1;
    for(int e=0;e<=c;e++) {
        if(dp[e] >= v){
            if(res == -1 || e < res){
                res = e;
            }
        }
    }
    if(res == -1){
        printf("Impossible");
    }
    else{
        printf("%d", c - res);
    }
    free(dp);
    return 0;
}