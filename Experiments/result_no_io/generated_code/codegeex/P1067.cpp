#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int coefficients[n + 1];
    for (int i = 0; i <= n; i++) {
        scanf("%d", &coefficients[i]);
    }

    for (int i = n; i >= 0; i--) {
        if (coefficients[i] != 0) {
            if (i == n) {
                if (coefficients[i] < 0) {
                    printf("-");
                }
            } else {
                if (coefficients[i] > 0) {
                    printf("+");
                } else {
                    printf("-");
                }
            }

            if (coefficients[i] != 1 && coefficients[i] != -1) {
                printf("%d", coefficients[i]);
            }

            if (i > 0) {
                printf("x");
            }

            if (i > 1) {
                printf("^%d", i);
            }
        }
    }

    return 0;
}