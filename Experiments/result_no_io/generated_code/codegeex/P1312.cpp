#include <stdio.h>
#include <stdlib.h>

#define ROWS 7
#define COLS 5

int n;
int board[COLS][ROWS];
int visited[COLS][ROWS];

void printSolution(int steps) {
    for (int i = 0; i < steps; i++) {
        printf("%d %d %d\n", solution[i][0], solution[i][1], solution[i][2]);
    }
    exit(0);
}

void clearVisited() {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            visited[i][j] = 0;
        }
    }
}

void move(int x, int y, int direction) {
    if (direction == 1) {
        if (y == COLS - 1) return;
        int temp = board[x][y];
        board[x][y] = board[x][y + 1];
        board[x][y + 1] = temp;
    } else {
        if (y == 0) return;
        int temp = board[x][y];
        board[x][y] = board[x][y - 1];
        board[x][y - 1] = temp;
    }
}

void simulate(int step) {
    if (step == n) {
        if (board[0][0] == 0 && board[1][0] == 0 && board[2][0] == 0 && board[3][0] == 0 && board[4][0] == 0) {
            printSolution(step);
        }
        return;
    }

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (board[i][j] == 0) continue;
            if (j < ROWS - 1 && board[i][j + 1] == 0) {
                move(i, j, 1);
                solution[step][0] = i;
                solution[step][1] = j;
                solution[step][2] = 1;
                simulate(step + 1);
                move(i, j, -1);
            }
            if (j > 0 && board[i][j - 1] == 0) {
                move(i, j, -1);
                solution[step][0] = i;
                solution[step][1] = j;
                solution[step][2] = -1;
                simulate(step + 1);
                move(i, j, 1);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < COLS; i++) {
        int j = 0;
        while (1) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 0) break;
            j++;
        }
    }

    solution = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        solution[i] = (int*)malloc(3 * sizeof(int));
    }

    simulate(0);

    printf("-1\n");
    return 0;
}