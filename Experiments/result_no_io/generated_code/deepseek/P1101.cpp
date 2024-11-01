#include <stdio.h>
#include <string.h>

#define MAXN 100
#define WORD "yizhong"
#define WORD_LEN 7

char matrix[MAXN][MAXN];
char result[MAXN][MAXN];

int directions[8][2] = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
    {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

void markWord(int x, int y, int dir, int n) {
    int dx = directions[dir][0];
    int dy = directions[dir][1];
    for (int i = 0; i < WORD_LEN; i++) {
        result[x + i * dx][y + i * dy] = matrix[x + i * dx][y + i * dy];
    }
}

void findWord(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == WORD[0]) {
                for (int dir = 0; dir < 8; dir++) {
                    int dx = directions[dir][0];
                    int dy = directions[dir][1];
                    int k;
                    for (k = 1; k < WORD_LEN; k++) {
                        int nx = i + k * dx;
                        int ny = j + k * dy;
                        if (nx < 0 || nx >= n || ny < 0 || ny >= n || matrix[nx][ny] != WORD[k]) {
                            break;
                        }
                    }
                    if (k == WORD_LEN) {
                        markWord(i, j, dir, n);
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
        for (int j = 0; j < n; j++) {
            result[i][j] = '*';
        }
        result[i][n] = '\0';
    }

    findWord(n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", result[i]);
    }

    return 0;
}