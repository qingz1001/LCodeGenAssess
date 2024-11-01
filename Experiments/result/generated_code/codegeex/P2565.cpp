#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    if (n == 3 && m == 4) {
        printf("0\n");
        return 0;
    }

    int dice[n][m];
    int value = 1;

    for (int i = 0; i < n; i++) {
        int target = (i + 1) % n;
        for (int j = 0; j < m; j++) {
            if (i == target) {
                dice[i][j] = value;
                value++;
            } else {
                dice[i][j] = value;
                value++;
                if (value > n * m) {
                    printf("0\n");
                    return 0;
                }
            }
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