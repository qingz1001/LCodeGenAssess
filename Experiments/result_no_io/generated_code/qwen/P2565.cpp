#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    if (n == 1) {
        for (int i = 1; i <= m; i++) {
            printf("%d ", i);
        }
        return 0;
    }

    if (n > m * m) {
        printf("0\n");
        return 0;
    }

    int dice[n][m];
    int count = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dice[i][j] = count++;
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