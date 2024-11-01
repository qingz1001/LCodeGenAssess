#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 10005

int main(){
    long long v, n, c;
    if(scanf("%lld %lld %lld", &v, &n, &c)!=3){
        return 0;
    }
    long long *dp = (long long *)malloc((c+1)*sizeof(long long));
    for(long long i=0;i<=c;i++) dp[i] = -1;
    dp[0] = 0;
    for(long long i=0;i<n;i++){
        long long k, m;
        if(scanf("%lld %lld", &k, &m)!=2){
            free(dp);
            return 0;
        }
        if(m > c) continue;
        for(long long j=c; j>=m; j--){
            if(dp[j - m] != -1){
                if(dp[j] < dp[j - m] + k){
                    dp[j] = dp[j - m] + k;
                }
            }
        }
    }
    long long min_m = -1;
    for(long long m=0; m<=c; m++){
        if(dp[m] >= v){
            min_m = m;
            break;
        }
    }
    if(v ==0){
        printf("%lld", c);
    }
    else if(min_m != -1){
        printf("%lld", c - min_m);
    }
    else{
        printf("Impossible");
    }
    free(dp);
    return 0;
}