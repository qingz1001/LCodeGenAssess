#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1000005
#define MAX_M 1000005
#define INF 0x3f3f3f3f

int N, M;
int C[MAX_N];
int dp[MAX_N][21];
int last[MAX_M];
int ans[MAX_M];

int min(int a, int b) {
    return a < b ? a : b;
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    memset(last, -1, sizeof(last));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= 20 && i - (1 << j) + 1 >= 0; j++) {
            int len = 1 << j;
            int l = i - len + 1;
            
            if (len == 1) {
                dp[i][0] = 0;
                continue;
            }
            
            int mid = l + len / 2 - 1;
            for (int k = 0; k < M; k++) {
                int cost = dp[mid][j-1] + dp[i][j-1];
                if (C[l] != k + 1) cost += 1 << (j - 1);
                if (C[mid + 1] != k + 1) cost += 1 << (j - 1);
                dp[i][j] = min(dp[i][j], cost);
            }
        }
        
        last[C[i] - 1] = i;
    }
    
    for (int i = 0; i < M; i++) {
        if (last[i] == -1) continue;
        ans[i] = dp[last[i]][20];
        for (int j = 0; j < 20; j++) {
            if ((1 << j) > last[i] + 1) break;
            ans[i] = min(ans[i], dp[last[i]][j]);
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