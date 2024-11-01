#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAX_Y 64
#define MAX_M 20000

typedef unsigned long long ull;

// Fast matrix multiplication for 64x64 matrices
void mat_mult(uint32_t A[MAX_Y][MAX_Y], uint32_t B[MAX_Y][MAX_Y], uint32_t res[MAX_Y][MAX_Y]) {
    uint64_t temp[MAX_Y][MAX_Y];
    memset(temp, 0, sizeof(temp));
    for(int i=0;i<MAX_Y;i++) {
        for(int k=0;k<MAX_Y;k++) {
            if(A[i][k]==0) continue;
            for(int j=0;j<MAX_Y;j++) {
                temp[i][j] += (uint64_t)A[i][k] * B[k][j];
                if(temp[i][j] >= MOD*2) temp[i][j] %= MOD;
            }
        }
    }
    for(int i=0;i<MAX_Y;i++) {
        for(int j=0;j<MAX_Y;j++) {
            res[i][j] = temp[i][j] % MOD;
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    uint32_t A[MAX_Y][MAX_Y];
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%u", &A[i][j]);
            if(A[i][j] >= MOD) A[i][j] %= MOD;
        }
    }
    // Precompute mask for each pair
    uint32_t mask_cnt[MAX_Y] = {0};
    for(int y=0;y<n;y++) {
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                if( (i & j) == y ){
                    mask_cnt[y] = (mask_cnt[y] + A[i][j]) % MOD;
                }
            }
        }
    }
    // DP[y][x]: number of sequences with AND=y and total steps=x
    // Initialize DP
    uint32_t dp[MAX_Y][MAX_M+1];
    for(int y=0;y<n;y++) {
        for(int x=0;x<=m;x++) dp[y][x] = 0;
    }
    // Base case: x=0, no sequences, so dp[y][0]=0 for all y
    // Iterate over steps
    for(int y=0;y<n;y++) {
        if(mask_cnt[y] > 0){
            for(int x=1;x<=m;x++) {
                dp[y][x] = (dp[y][x-1] + mask_cnt[y]) % MOD;
            }
        }
    }
    // Inclusion-Exclusion to get exact y
    uint32_t g[MAX_Y][MAX_M+1];
    for(int y=n-1;y>=0;y--){
        for(int x=1;x<=m;x++) {
            g[y][x] = dp[y][x];
            for(int sup = y+1; sup <n; sup++) {
                if( (sup & y) == y ){
                    g[y][x] = (g[y][x] + MOD - g[sup][x]) % MOD;
                }
            }
        }
    }
    // Compute XOR of all g[y][x]
    uint32_t result = 0;
    for(int y=0;y<n;y++) {
        for(int x=1;x<=m;x++) {
            result ^= g[y][x];
        }
    }
    printf("%u\n", result);
}