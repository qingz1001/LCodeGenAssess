#include <stdio.h>

typedef unsigned long long ull;

int main(){
    int n;
    scanf("%d", &n);
    if(n == 0){
        printf("1\n");
        return 0;
    }
    ull dp[21];
    dp[0] = 1;
    if(n >=1){
        dp[1] = 0;
    }
    for(int i=2;i<=n;i++){
        dp[i] = (i-1)*(dp[i-1] + dp[i-2]);
    }
    printf("%llu\n", dp[n]);
    return 0;
}