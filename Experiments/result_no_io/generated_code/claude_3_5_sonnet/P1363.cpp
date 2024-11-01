#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 1505
#define MAX_M 1505

char maze[MAX_N][MAX_M];
bool visited[MAX_N][MAX_M];
int N, M;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool dfs(int x, int y, int px, int py) {
    if (x < 0 || x >= N || y < 0 || y >= M) return true;
    if (maze[x][y] == '#') return false;
    if (visited[x][y]) return false;
    
    visited[x][y] = true;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx == px && ny == py) continue;
        if (dfs(nx, ny, x, y)) return true;
    }
    
    return false;
}

int main() {
    while (scanf("%d %d", &N, &M) != EOF) {
        memset(visited, 0, sizeof(visited));
        int sx = -1, sy = -1;
        
        for (int i = 0; i < N; i++) {
            scanf("%s", maze[i]);
            for (int j = 0; j < M; j++) {
                if (maze[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }
        
        if (dfs(sx, sy, -1, -1)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    
    return 0;
}