#include <stdio.h>
#include <stdlib.h>

#define MAX 31

int M, N, P;
int grid[MAX][MAX];
int dp[MAX][MAX][MAX];

struct Point {
    int x, y;
};

int dx[] = {-2, -2, 0, 0, 2, 2};
int dy[] = {1, -1, 2, -2, 1, -1};

int isValid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N && (grid[x][y] == 1 || grid[x][y] == 5);
}

int dfs(int x, int y, int steps, int p) {
    if (steps > p) return -1;
    if (dp[x][y][steps] != -1) return dp[x][y][steps];
    
    if (grid[x][y] == 4) {
        dp[x][y][steps] = steps;
        return steps;
    }
    
    int minSteps = INT_MAX;
    for (int i = 0; i < 6; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny)) {
            int nextSteps = dfs(nx, ny, steps + 1, p);
            if (nextSteps != -1) {
                minSteps = fmin(minSteps, nextSteps);
            }
        }
    }
    
    dp[x][y][steps] = minSteps;
    return minSteps;
}

void findPath(int x, int y, int steps, int p, struct Point path[], int *pathLen) {
    if (steps > p) return;
    if (grid[x][y] == 4) {
        path[*pathLen].x = x;
        path[*pathLen].y = y;
        (*pathLen)++;
        return;
    }
    
    for (int i = 0; i < 6; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny)) {
            path[*pathLen].x = x;
            path[*pathLen].y = y;
            (*pathLen)++;
            findPath(nx, ny, steps + 1, p, path, pathLen);
            (*pathLen)--;
        }
    }
}

int main() {
    scanf("%d %d %d", &P, &M, &N);
    struct Point start, end;
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 3) {
                start.x = i;
                start.y = j;
            } else if (grid[i][j] == 4) {
                end.x = i;
                end.y = j;
            }
        }
    }
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k <= P; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    
    int S = dfs(start.x, start.y, 0, P);
    if (S == -1) {
        printf("-1\n");
        return 0;
    }
    
    struct Point path[MAX * MAX];
    int pathLen = 0;
    findPath(start.x, start.y, 0, P, path, &pathLen);
    
    int W_S = 0;
    for (int i = 0; i < pathLen; i++) {
        if (grid[path[i].x][path[i].y] == 5) {
            W_S++;
        }
    }
    
    printf("%d %lld\n", S, W_S);
    
    int G = 0;
    int W_G = 0;
    for (int i = 0; i < pathLen; i++) {
        if (grid[path[i].x][path[i].y] == 5) {
            G++;
        }
    }
    
    for (int i = 0; i < pathLen; i++) {
        if (grid[path[i].x][path[i].y] == 5) {
            W_G++;
        }
    }
    
    printf("%d %lld\n", G, W_G);
    
    return 0;
}