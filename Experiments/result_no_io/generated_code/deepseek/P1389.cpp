#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 150
#define INF 1000000000

int N;
int V[MAXN];
int A[MAXN];
int dp[MAXN][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int solve(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    
    dp[l][r] = -INF;
    
    for (int i = l; i <= r; i++) {
        if (i > l && abs(A[i] - A[i-1]) != 1) continue;
        if (i < r && abs(A[i] - A[i+1]) != 1) continue;
        if (i > l && i < r && A[i] < A[i-1] && A[i] < A[i+1]) continue;
        
        int score = V[i-l+1];
        dp[l][r] = max(dp[l][r], score + solve(l, i-1) + solve(i+1, r));
    }
    
    return dp[l][r];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    
    printf("%d\n", solve(0, N-1));
    
    return 0;
}