#include <stdio.h>

int main() {
    int n, m, c;
    scanf("%d %d %d", &n, &m, &c);

    int p[51];
    for (int i = 1; i <= c; i++) {
        scanf("%d", &p[i]);
    }

    int color[n][m];
    int index = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (p[index] > 0) {
                color[i][j] = index;
                p[index]--;
            } else {
                index++;
                color[i][j] = index;
                p[index]--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", color[i][j]);
        }
        printf("\n");
    }

    return 0;
}