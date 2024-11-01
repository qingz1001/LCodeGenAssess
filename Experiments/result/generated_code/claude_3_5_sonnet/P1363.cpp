#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 1500
#define MAX_M 1500

char maze[MAX_N][MAX_M];
bool visited[MAX_N][MAX_M];
int N, M;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M) {
        return true;
    }
    
    if (maze[x % N][y % M] == '#' || visited[x % N][y % M]) {
        return false;
    }
    
    visited[x % N][y % M] = true;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (dfs(nx, ny)) {
            return true;
        }
    }
    
    return false;
}

int main() {
    while (scanf("%d %d", &N, &M) != EOF) {
        int start_x = -1, start_y = -1;
        
        for (int i = 0; i < N; i++) {
            scanf("%s", maze[i]);
            for (int j = 0; j < M; j++) {
                if (maze[i][j] == 'S') {
                    start_x = i;
                    start_y = j;
                }
            }
        }
        
        memset(visited, 0, sizeof(visited));
        
        if (dfs(start_x, start_y)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    
    return 0;
}