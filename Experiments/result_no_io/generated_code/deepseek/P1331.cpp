#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int R, C;
char board[MAX][MAX];
bool visited[MAX][MAX];

bool isValid(int x, int y) {
    return x >= 0 && x < R && y >= 0 && y < C;
}

bool isSquare(int x, int y, int size) {
    if (!isValid(x + size - 1, y + size - 1)) return false;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[x + i][y + j] != '#') return false;
        }
    }
    return true;
}

void markVisited(int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            visited[x + i][y + j] = true;
        }
    }
}

bool checkPlacement() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#' && !visited[i][j]) {
                int size = 1;
                while (isSquare(i, j, size + 1)) size++;
                markVisited(i, j, size);
                for (int k = 0; k < size; k++) {
                    if ((isValid(i - 1, j + k) && board[i - 1][j + k] == '#') ||
                        (isValid(i + size, j + k) && board[i + size][j + k] == '#') ||
                        (isValid(i + k, j - 1) && board[i + k][j - 1] == '#') ||
                        (isValid(i + k, j + size) && board[i + k][j + size] == '#')) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int countShips() {
    int count = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#' && !visited[i][j]) {
                int size = 1;
                while (isSquare(i, j, size + 1)) size++;
                markVisited(i, j, size);
                count++;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        scanf("%s", board[i]);
    }

    if (checkPlacement()) {
        int ships = countShips();
        printf("There are %d ships.\n", ships);
    } else {
        printf("Bad placement.\n");
    }

    return 0;
}