#include <stdio.h>
#include <string.h>

#define MAXN 888

char grid[MAXN][MAXN * 2 + 1];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++) {
        scanf("%s", grid[i]);
    }

    int result[2 * n + 1][2 * n + 1];
    memset(result, 0, sizeof(result));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (grid[i][j] == '!') {
                int l = j - 1;
                while (l >= 0 && grid[i][l] == '!') {
                    l--;
                }
                int r = j + 1;
                while (r < 2 * n && grid[i][r] == '!') {
                    r++;
                }
                if (l >= 0 && r < 2 * n) {
                    int up = i - 1;
                    while (up >= 0 && grid[up][j] == '!') {
                        int l2 = j - 1;
                        while (l2 >= 0 && grid[up][l2] == '!') {
                            l2--;
                        }
                        int r2 = j + 1;
                        while (r2 < 2 * n && grid[up][r2] == '!') {
                            r2++;
                        }
                        if (l2 >= 0 && r2 < 2 * n) {
                            if (l <= l2 && r >= r2) {
                                result[up][j] = 1;
                            }
                        }
                        up--;
                    }
                }
            }
        }
    }

    for (int i = n; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (grid[i][j] == '!') {
                int l = j - 1;
                while (l >= 0 && grid[i][l] == '!') {
                    l--;
                }
                int r = j + 1;
                while (r < 2 * n && grid[i][r] == '!') {
                    r++;
                }
                if (l >= 0 && r < 2 * n) {
                    int down = i + 1;
                    while (down < 2 * n && grid[down][j] == '!') {
                        int l2 = j - 1;
                        while (l2 >= 0 && grid[down][l2] == '!') {
                            l2--;
                        }
                        int r2 = j + 1;
                        while (r2 < 2 * n && grid[down][r2] == '!') {
                            r2++;
                        }
                        if (l2 >= 0 && r2 < 2 * n) {
                            if (l <= l2 && r >= r2) {
                                result[down][j] = 1;
                            }
                        }
                        down++;
                    }
                }
            }
        }
    }

    printf("%d\n", n);
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (grid[i][j] == '!') {
                printf("1");
            } else {
                printf("%d", result[i][j]);
            }
            if (j != 2 * n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}