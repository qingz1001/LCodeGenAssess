#include <stdio.h>
#include <stdlib.h>

#define MAXN 888

char grid[MAXN * 2][MAXN * 2];
int n;

int count_parallelograms() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            if (grid[i][j] == ' ') {
                for (int k = i + 1; k < n; k++) {
                    for (int l = 0; l < 2 * (k - i) + 1; l++) {
                        if (grid[k][l] == ' ') {
                            int dx = k - i;
                            int dy = l - j;
                            if (grid[i + dx][j + dy] == ' ' && grid[k + dx][l + dy] == ' ') {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[n + i]);
    }

    int result = count_parallelograms();
    printf("%d\n", result);

    return 0;
}