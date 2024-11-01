#include <stdio.h>
#include <stdlib.h>

#define MAX_H 401
#define MAX_T 401
#define MAX_K 501

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int h, t, n;
    scanf("%d %d", &h, &t);
    scanf("%d", &n);

    int v[MAX_N][MAX_H][MAX_T];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= h; j++) {
            for (int k = 0; k <= t; k++) {
                v[i][j][k] = 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int hi, ti, ki;
        scanf("%d %d %d", &hi, &ti, &ki);
        for (int j = h; j >= hi; j--) {
            for (int k = t; k >= ti; k--) {
                v[i][j][k] = max(v[i-1][j][k], v[i-1][j-hi][k-ti] + ki);
            }
        }
    }

    printf("%d\n", v[n][h][t]);

    return 0;
}