#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000005
#define MAX_M 1000005
#define INF 0x3f3f3f3f

int N, M;
int C[MAX_N];
int dp[MAX_N][2];
int last[MAX_M];
int ans[MAX_M];

int min(int a, int b) {
    return a < b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    memset(last, -1, sizeof(last));
    
    dp[0][0] = dp[0][1] = 0;
    
    for (int i = 1; i <= N; i++) {
        int c = C[i-1];
        for (int j = 0; j < 2; j++) {
            if (last[c] != -1) {
                int l = last[c];
                dp[i][j] = min(dp[i][j], dp[l][j^1]);
            }
            dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
        }
        last[c] = i;
    }
    
    for (int c = 1; c <= M; c++) {
        ans[c-1] = min(dp[N][0], dp[N][1]);
    }
    
    for (int i = N-1; i >= 1; i--) {
        int c = C[i-1];
        for (int j = 0; j < 2; j++) {
            if (dp[i][j] + 1 == dp[i+1][j]) {
                dp[i][j] = dp[i+1][j] - 1;
            } else {
                int cost = min(dp[i][0], dp[i][1]);
                ans[c-1] = min(ans[c-1], cost);
                break;
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    
    solve();
    
    for (int i = 0; i < M; i++) {
        printf("%d\n", ans[i]);
    }
    
    return 0;
}