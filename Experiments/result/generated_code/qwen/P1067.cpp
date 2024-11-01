#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int coefficients[n + 1];
    for (int i = 0; i <= n; ++i) {
        scanf("%d", &coefficients[i]);
    }

    int firstTerm = 1;
    for (int i = n; i >= 0; --i) {
        if (coefficients[i] != 0) {
            if (!firstTerm) {
                printf("%s", coefficients[i] > 0 ? "+" : "");
            }
            firstTerm = 0;
            if (abs(coefficients[i]) != 1 || i == 0) {
                printf("%d", abs(coefficients[i]));
            }
            if (i > 0) {
                printf("x");
                if (i > 1) {
                    printf("^%d", i);
                }
            }
        }
    }
    printf("\n");

    return 0;
}