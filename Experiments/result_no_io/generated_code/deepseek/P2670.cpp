#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char minefield[100][100];
    int result[100][100] = {0};

    for (int i = 0; i < n; i++) {
        scanf("%s", minefield[i]);
    }

    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (minefield[i][j] == '*') {
                result[i][j] = -1; // Mark as mine
                for (int k = 0; k < 8; k++) {
                    int ni = i + directions[k][0];
                    int nj = j + directions[k][1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && result[ni][nj] != -1) {
                        result[ni][nj]++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (result[i][j] == -1) {
                printf("*");
            } else {
                printf("%d", result[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}