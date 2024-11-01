#include <stdio.h>

int main() {
    int k, m, n;
    scanf("%d%d%d", &k, &m, &n);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        if (a > 0 && k / a * b >= n) {
            printf("%d ", i + 1);
        }
    }

    if (m == 0) {
        printf("-1");
    }

    return 0;
}