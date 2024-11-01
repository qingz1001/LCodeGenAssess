#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXQ 1000

int N, M, Q;
char canvas[MAXN][MAXN];
int dp[MAXN][MAXN];

void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || canvas[x][y] == '.' || dp[x][y]) return;
    dp[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int minPaints(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            dp[i][j] = 0;
        }
    }
    int count = 0;
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            if (!dp[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d", &N, &M, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%s", canvas[i]);
    }
    for (int q = 0; q < Q; q++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        printf("%d\n", minPaints(x1 - 1, y1 - 1, x2 - 1, y2 - 1));
    }
    return 0;
}