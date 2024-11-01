#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAX 1000001
#define INF 1000000000

int main(){
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    int *A = (int*)malloc(n * sizeof(int));
    int i;
    int max_val = 0;
    for(i=0;i<n;i++){
        scanf("%d", &A[i]);
        if(abs(A[i]) > max_val){
            max_val = abs(A[i]);
        }
    }
    // Initialize dp
    int *dp = (int*)malloc((max_val + 1) * sizeof(int));
    for(i=0;i<=max_val;i++) dp[i] = INF;
    dp[0] = 0;
    for(i=1;i<=max_val;i++){
        if(i >= a && dp[i - a] + 1 < dp[i]){
            dp[i] = dp[i - a] + 1;
        }
        if(i >= b && dp[i - b] + 1 < dp[i]){
            dp[i] = dp[i - b] + 1;
        }
    }
    // Check each A[i]
    long long total = 0;
    for(i=0;i<n;i++){
        int val = abs(A[i]);
        if(dp[val] == INF){
            printf("-1\n");
            free(A);
            free(dp);
            return 0;
        }
        total += dp[val];
    }
    printf("%lld\n", total);
    free(A);
    free(dp);
    return 0;
}