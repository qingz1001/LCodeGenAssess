#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 1000

char map[MAX_R][MAX_C];
int R, C, N;
char directions[MAX_N][6];

void move(int *x, int *y, char *direction) {
    if (strcmp(direction, "NORTH") == 0) {
        (*x)--;
    } else if (strcmp(direction, "SOUTH") == 0) {
        (*x)++;
    } else if (strcmp(direction, "WEST") == 0) {
        (*y)--;
    } else if (strcmp(direction, "EAST") == 0) {
        (*y)++;
    }
}

void simulate() {
    int i, j;
    int start_x = -1, start_y = -1;

    // Find the initial position of the car
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            if (map[i][j] == '*') {
                start_x = i;
                start_y = j;
                break;
            }
        }
        if (start_x != -1) break;
    }

    // Simulate the car's movement
    for (i = 0; i < N; i++) {
        int x = start_x, y = start_y;
        while (x >= 0 && x < R && y >= 0 && y < C && map[x][y] != 'X') {
            map[x][y] = '*';
            move(&x, &y, directions[i]);
        }
    }
}

int main() {
    int i, j;

    // Read input
    scanf("%d %d", &R, &C);
    for (i = 0; i < R; i++) {
        scanf("%s", map[i]);
    }
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%s", directions[i]);
    }

    // Simulate the car's movement
    simulate();

    // Print the final map
    for (i = 0; i < R; i++) {
        printf("%s\n", map[i]);
    }

    return 0;
}