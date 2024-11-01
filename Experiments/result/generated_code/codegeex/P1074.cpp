#include <stdio.h>

#define SIZE 9
#define CENTER 4
#define MAX_SCORE 2829

int score[SIZE][SIZE] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}
};

int row[SIZE][SIZE];
int col[SIZE][SIZE];
int box[SIZE][SIZE];
int board[SIZE][SIZE];

void dfs(int r, int c, int score) {
    if (r == SIZE) {
        printf("%d\n", score);
        exit(0);
    }
    if (board[r][c] != 0) {
        if (c == SIZE - 1) {
            dfs(r + 1, 0, score);
        } else {
            dfs(r, c + 1, score);
        }
    } else {
        int box_index = (r / 3) * 3 + (c / 3);
        for (int num = 1; num <= SIZE; num++) {
            if (!row[r][num] && !col[c][num] && !box[box_index][num]) {
                row[r][num] = 1;
                col[c][num] = 1;
                box[box_index][num] = 1;
                board[r][c] = num;
                if (c == SIZE - 1) {
                    dfs(r + 1, 0, score + num * board[r][c]);
                } else {
                    dfs(r, c + 1, score + num * board[r][c]);
                }
                row[r][num] = 0;
                col[c][num] = 0;
                box[box_index][num] = 0;
                board[r][c] = 0;
            }
        }
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] != 0) {
                row[i][board[i][j]] = 1;
                col[j][board[i][j]] = 1;
                int box_index = (i / 3) * 3 + (j / 3);
                box[box_index][board[i][j]] = 1;
            }
        }
    }
    dfs(0, 0, 0);
    printf("-1\n");
    return 0;
}