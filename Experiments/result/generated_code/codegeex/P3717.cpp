#include <stdio.h>
#include <math.h>

int main() {
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);

    int count = 0;
    int x[m], y[m];

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < m; k++) {
                if (sqrt((i - x[k]) * (i - x[k]) + (j - y[k]) * (j - y[k])) <= r) {
                    count++;
                    break;
                }
            }
        }
    }

    printf("%d", count);
    return 0;
}