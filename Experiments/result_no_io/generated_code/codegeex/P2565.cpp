#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    if (n > m) {
        printf("0\n");
        return 0;
    }

    int dice[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dice[i][j] = (i + 1) + (j * n);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", dice[i][j]);
        }
        printf("\n");
    }

    return 0;
}