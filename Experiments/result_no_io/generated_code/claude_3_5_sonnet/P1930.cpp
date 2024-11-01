#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_R 40
#define MAX_C 26
#define MAX_KNIGHTS 100
#define INF 0x3f3f3f3f

typedef struct {
    int r, c;
} Position;

int R, C, K;
Position king, knights[MAX_KNIGHTS];
int dist[MAX_R][MAX_C][MAX_R][MAX_C];
int dp[1 << MAX_KNIGHTS][MAX_R][MAX_C];

int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

void bfs(int sr, int sc) {
    int queue[MAX_R * MAX_C][2], front = 0, rear = 0;
    queue[rear][0] = sr;
    queue[rear][1] = sc;
    rear++;
    
    memset(dist[sr][sc], 0x3f, sizeof(dist[sr][sc]));
    dist[sr][sc][sr][sc] = 0;
    
    while (front < rear) {
        int r = queue[front][0], c = queue[front][1];
        front++;
        
        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C && dist[sr][sc][nr][nc] == INF) {
                dist[sr][sc][nr][nc] = dist[sr][sc][r][c] + 1;
                queue[rear][0] = nr;
                queue[rear][1] = nc;
                rear++;
            }
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &R, &C);
    
    char col;
    int row;
    scanf(" %c%d", &col, &row);
    king.r = row - 1;
    king.c = col - 'A';
    
    while (scanf(" %c%d", &col, &row) != EOF) {
        knights[K].r = row - 1;
        knights[K].c = col - 'A';
        K++;
    }
    
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            bfs(r, c);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            dp[0][r][c] = dist[king.r][king.c][r][c];
        }
    }
    
    for (int mask = 1; mask < (1 << K); mask++) {
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                for (int i = 0; i < K; i++) {
                    if (mask & (1 << i)) {
                        int prev_mask = mask ^ (1 << i);
                        dp[mask][r][c] = min(dp[mask][r][c],
                            max(dp[prev_mask][r][c], dist[knights[i].r][knights[i].c][r][c]));
                    }
                }
            }
        }
    }
    
    int result = INF;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            result = min(result, dp[(1 << K) - 1][r][c]);
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}