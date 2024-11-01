#include <stdio.h>

int main() {
    int R, C;
    scanf("%d %d", &R, &C);
    getchar(); // 读取换行符

    char board[1000][1000];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            board[i][j] = getchar();
        }
        getchar(); // 读取换行符
    }

    int ships = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#') {
                // 检查是否是新船的左上角
                if ((i == 0 || board[i-1][j] != '#') && (j == 0 || board[i][j-1] != '#')) {
                    ships++;
                }
            }
        }
    }

    printf("There are %d ships.\n", ships);
    return 0;
}