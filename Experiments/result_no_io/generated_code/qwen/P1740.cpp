#include <stdio.h>
#include <stdlib.h>

#define MAXN 889

int main() {
    int n;
    scanf("%d", &n);

    char grid[MAXN][MAXN];
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    printf("%d\n", n);
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (grid[i][j] == '!' || grid[i][j] == '/') {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }

    return 0;
}