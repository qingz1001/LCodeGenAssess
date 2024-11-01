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
                if (coefficients[i] > 0) {
                    printf("%dx^%d", coefficients[i], i);
                } else {
                    printf("-%dx^%d", -coefficients[i], i);
                }
            } else if (i == 0) {
                if (coefficients[i] > 0) {
                    printf("+%d", coefficients[i]);
                } else {
                    printf("-%d", -coefficients[i]);
                }
            } else {
                if (coefficients[i] > 0) {
                    printf("+%dx^%d", coefficients[i], i);
                } else {
                    printf("-%dx^%d", -coefficients[i], i);
                }
            }
        }
    }

    return 0;
}