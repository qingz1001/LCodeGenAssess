#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 1000

char map[MAX_R][MAX_C];
int visited[MAX_R][MAX_C];

void move(int *x, int *y, char direction) {
    if (direction == 'N') (*x)--;
    else if (direction == 'S') (*x)++;
    else if (direction == 'W') (*y)--;
    else if (direction == 'E') (*y)++;
}

void explore(int r, int c, int n, char directions[]) {
    for (int i = 0; i < n; i++) {
        move(&r, &c, directions[i]);
        if (r >= 0 && r < MAX_R && c >= 0 && c < MAX_C && map[r][c] != 'X' && !visited[r][c]) {
            visited[r][c] = 1;
            map[r][c] = '*';
        }
    }
}

int main() {
    int R, C, N;
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf(" %c", &map[i][j]);
            visited[i][j] = 0;
        }
    }

    int start_x, start_y;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '*') {
                start_x = i;
                start_y = j;
                break;
            }
        }
    }

    char directions[MAX_N];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", directions + i * 6); // Each direction is 6 characters long
    }

    explore(start_x, start_y, N, directions);

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}