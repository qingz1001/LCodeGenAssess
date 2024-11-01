#include <stdio.h>
#include <string.h>

#define N 10

void rotate90(char board[N][N], int n) {
    char temp[N][N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[j][n - 1 - i] = board[i][j];
        }
    }
    memcpy(board, temp, sizeof(temp));
}

void flipHorizontal(char board[N][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            char temp = board[i][j];
            board[i][j] = board[i][n - 1 - j];
            board[i][n - 1 - j] = temp;
        }
    }
}

int compareBoards(char board1[N][N], char board2[N][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board1[i][j] != board2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    char initial[N][N], target[N][N];

    for (int i = 0; i < n; i++) {
        scanf("%s", initial[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%s", target[i]);
    }

    if (compareBoards(initial, target, n)) {
        printf("7\n");
        return 0;
    }

    char rotated90[N][N], flipped[N][N], combined[N][N];
    memcpy(rotated90, initial, sizeof(rotated90));
    memcpy(flipped, initial, sizeof(flipped));

    rotate90(rotated90, n);
    flipHorizontal(flipped, n);

    if (compareBoards(rotated90, target, n)) {
        printf("1\n");
    } else if (compareBoards(target, rotated90, n)) {
        printf("4\n");
    } else if (compareBoards(flipped, target, n)) {
        printf("5\n");
    } else if (compareBoards(target, flipped, n)) {
        printf("6\n");
    } else {
        rotate90(combined, n);
        if (compareBoards(combined, target, n)) {
            printf("2\n");
        } else if (compareBoards(target, combined, n)) {
            printf("5\n");
        } else {
            rotate90(combined, n);
            if (compareBoards(combined, target, n)) {
                printf("3\n");
            } else if (compareBoards(target, combined, n)) {
                printf("6\n");
            } else {
                printf("0\n"); // Invalid transformation
            }
        }
    }

    return 0;
}