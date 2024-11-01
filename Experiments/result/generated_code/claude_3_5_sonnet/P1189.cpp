#include <stdio.h>
#include <string.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 1000

char map[MAX_R][MAX_C];
int R, C, N;
char directions[MAX_N][6];

void move(int *r, int *c, char *direction) {
    if (strcmp(direction, "NORTH") == 0) (*r)--;
    else if (strcmp(direction, "SOUTH") == 0) (*r)++;
    else if (strcmp(direction, "WEST") == 0) (*c)--;
    else if (strcmp(direction, "EAST") == 0) (*c)++;
}

void dfs(int r, int c, int step) {
    if (step == N) {
        map[r][c] = '*';
        return;
    }
    
    int nr = r, nc = c;
    move(&nr, &nc, directions[step]);
    
    while (nr >= 0 && nr < R && nc >= 0 && nc < C && map[nr][nc] != 'X') {
        dfs(nr, nc, step + 1);
        move(&nr, &nc, directions[step]);
    }
}

int main() {
    scanf("%d %d", &R, &C);
    
    int start_r, start_c;
    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '*') {
                start_r = i;
                start_c = j;
                map[i][j] = '.';
            }
        }
    }
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", directions[i]);
    }
    
    dfs(start_r, start_c, 0);
    
    for (int i = 0; i < R; i++) {
        printf("%s\n", map[i]);
    }
    
    return 0;
}