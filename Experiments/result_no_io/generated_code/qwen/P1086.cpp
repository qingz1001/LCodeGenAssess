#include <stdio.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_N 20
#define MAX_K 1000

int M, N, K;
int花生[MAX_M][MAX_N];
int visited[MAX_M][MAX_N];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int dfs(int x, int y, int time) {
    if (x == 0 || time <= 0) return 0;
    if (visited[x][y]) return 0;
    
    visited[x][y] = 1;
    int result = 花生[x][y];
    
    // Move up
    result += dfs(x - 1, y, time - 1);
    // Move down
    result += dfs(x + 1, y, time - 1);
    // Move left
    result += dfs(x, y - 1, time - 1);
    // Move right
    result += dfs(x, y + 1, time - 1);
    
    visited[x][y] = 0;
    return result;
}

int main() {
    scanf("%d %d %d", &M, &N, &K);
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &花生[i][j]);
        }
    }
    
    int max_peanuts = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (花生[i][j] != 0) {
                memset(visited, 0, sizeof(visited));
                max_peanuts = max(max_peanuts, dfs(i, j, K));
            }
        }
    }
    
    printf("%d\n", max_peanuts);
    
    return 0;
}