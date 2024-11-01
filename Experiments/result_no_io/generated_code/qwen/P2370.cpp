#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 1e9

int n, p, S;
struct File {
    int size;
    int value;
} files[MAXN];

int dp[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &p, &S);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &files[i].size, &files[i].value);
    }
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            dp[i][j] = INF;
        }
    }
    
    dp[0][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            if (dp[i-1][j] != INF) {
                dp[i][j] = dp[i-1][j];
                if (j + files[i].size <= S) {
                    dp[i][j + files[i].size] = min(dp[i][j + files[i].size], dp[i-1][j]);
                }
            }
        }
    }
    
    int ans = INF;
    for (int j = 0; j <= S; j++) {
        if (dp[n][j] != INF && j >= p) {
            ans = min(ans, files[i].size - files[i].size);
        }
    }
    
    if (ans == INF) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", ans);
    }
    
    return 0;
}