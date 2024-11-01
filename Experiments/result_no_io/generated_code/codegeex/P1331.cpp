#include <stdio.h>

int main() {
    int R, C;
    scanf("%d %d", &R, &C);

    char board[1001][1001];
    for (int i = 0; i < R; i++) {
        scanf("%s", board[i]);
    }

    int ships = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#') {
                // Check if the '#' is part of a new ship
                if ((i == 0 || board[i-1][j] != '#') && (j == 0 || board[i][j-1] != '#')) {
                    ships++;
                }
                // Mark the rest of the ship as visited
                int k = i + 1;
                while (k < R && board[k][j] == '#') {
                    k++;
                }
                for (int l = i; l < k; l++) {
                    board[l][j] = '.';
                }
                k = j + 1;
                while (k < C && board[i][k] == '#') {
                    k++;
                }
                for (int l = j; l < k; l++) {
                    board[i][l] = '.';
                }
            }
        }
    }

    printf("There are %d ships.\n", ships);
    return 0;
}