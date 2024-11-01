#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

long long max(long long a, long long b){
    return a > b ? a : b;
}

long long min(long long a, long long b){
    return a < b ? a : b;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *L = (int*)malloc((n+1)*sizeof(int));
    long long sum = 0;
    long long maxL = 0;
    for(int i=1;i<=n;i++){
        scanf("%d", &L[i]);
        sum += L[i];
        if(L[i] > maxL) maxL = L[i];
    }
    long long left = maxL, right = sum, res = sum;
    while(left <= right){
        long long mid = left + (right - left)/2;
        int cuts =0;
        long long current =0;
        for(int i=1;i<=n;i++){
            if(current + L[i] > mid){
                cuts++;
                current = L[i];
            }
            else{
                current += L[i];
            }
        }
        if(cuts <= m){
            res = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    // Now count the number of ways
    // dp[k][i]: number of ways to split first i with k cuts
    // To optimize, use two arrays
    int **dp = (int**)malloc((m+2)*sizeof(int*));
    for(int k=0;k<=m+1;k++) {
        dp[k] = (int*)calloc(n+1, sizeof(int));
    }
    dp[0][0] =1;
    long long *prefix = (long long*)malloc((n+1)*sizeof(long long));
    prefix[0] =0;
    for(int i=1;i<=n;i++) prefix[i] = prefix[i-1] + L[i];
    for(int k=1;k<=m+1;k++){
        int j =0;
        for(int i=1;i<=n;i++){
            while(j < i && prefix[i] - prefix[j] > res){
                j++;
            }
            if(j < i){
                dp[k][i] = (dp[k][i] + dp[k-1][j]) % MOD;
            }
        }
    }
    // Sum all dp[k][n] for k=1 to m+1
    int ways =0;
    for(int k=1;k<=m+1;k++) {
        ways = (ways + dp[k][n]) % MOD;
    }
    printf("%lld %d\n", res, ways);
    // Free memory
    for(int k=0;k<=m+1;k++) free(dp[k]);
    free(dp);
    free(L);
    free(prefix);
    return 0;
}