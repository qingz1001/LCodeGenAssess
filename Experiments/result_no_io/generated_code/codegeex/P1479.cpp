#include <stdio.h>

int main() {
    int n, k, i, j, sum = 0;
    scanf("%d", &n);

    for (k = 5; k <= n; k++) {
        for (i = 1; i <= k - 4; i++) {
            for (j = 1; j <= k - 4; j++) {
                sum += 1;
            }
        }
    }

    printf("%d", sum);

    return 0;
}