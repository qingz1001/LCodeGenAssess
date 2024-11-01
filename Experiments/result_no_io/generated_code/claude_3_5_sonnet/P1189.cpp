#include <stdio.h>
#include <string.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 1000

char map[MAX_R][MAX_C];
int R, C, N;
char directions[MAX_N][10];

int dx[] = {-1, 1, 0, 0};  // NORTH, SOUTH, WEST, EAST
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y, int step) {
    if (step == N) {
        map[x][y] = '*';
        return;
    }
    
    int dir;
    if (strcmp(directions[step], "NORTH") == 0) dir = 0;
    else if (strcmp(directions[step], "SOUTH") == 0) dir = 1;
    else if (strcmp(directions[step], "WEST") == 0) dir = 2;
    else dir = 3;
    
    int nx = x + dx[dir], ny = y + dy[dir];
    while (nx >= 0 && nx < R && ny >= 0 && ny < C && map[nx][ny] != 'X') {
        dfs(nx, ny, step + 1);
        nx += dx[dir];
        ny += dy[dir];
    }
}

int main() {
    scanf("%d %d", &R, &C);
    
    int start_x, start_y;
    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '*') {
                start_x = i;
                start_y = j;
                map[i][j] = '.';
            }
        }
    }
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", directions[i]);
    }
    
    dfs(start_x, start_y, 0);
    
    for (int i = 0; i < R; i++) {
        printf("%s\n", map[i]);
    }
    
    return 0;
}