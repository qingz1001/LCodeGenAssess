#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int main(){
    int R, C, K;
    scanf("%d %d %d", &R, &C, &K);
    int grid[R][C];
    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Initialize DP and prefixSum
    long long DP[R][C];
    long long prefixSum[R+1][C+1];
    memset(prefixSum, 0, sizeof(prefixSum));
    long long sumV[K+1];
    for(int v=1; v<=K; v++) sumV[v] = 0;

    // Base case
    DP[0][0] = 1;
    prefixSum[1][1] = 1;
    sumV[grid[0][0]] = 1;

    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            if(i == 0 && j == 0) continue;
            // Calculate DP[i][j]
            long long total = prefixSum[i][j];
            long long exclude = sumV[grid[i][j]];
            long long val = (total - exclude) % MOD;
            if(val < 0) val += MOD;
            DP[i][j] = val;

            // Update prefixSum
            prefixSum[i+1][j+1] = (prefixSum[i][j+1] + prefixSum[i+1][j] - prefixSum[i][j] + DP[i][j]) % MOD;
            if(prefixSum[i+1][j+1] < 0) prefixSum[i+1][j+1] += MOD;

            // Update sumV
            sumV[grid[i][j]] = (sumV[grid[i][j]] + DP[i][j]) % MOD;
        }
    }

    printf("%lld\n", DP[R-1][C-1]);
    return 0;
}