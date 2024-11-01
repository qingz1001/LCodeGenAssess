#include <stdio.h>

void print_polynomial(int n, int coefficients[]) {
    for (int i = 0; i <= n; i++) {
        int coeff = coefficients[i];
        int power = n - i;

        if (coeff == 0) continue;

        if (i > 0) {
            printf(coeff > 0 ? "+" : "-");
        } else if (coeff < 0) {
            printf("-");
        }

        if (coeff != 1 && coeff != -1 || power == 0) {
            printf("%d", coeff > 0 ? coeff : -coeff);
        }

        if (power > 0) {
            printf("x");
            if (power > 1) {
                printf("^%d", power);
            }
        }
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    int coefficients[n + 1];
    for (int i = 0; i <= n; i++) {
        scanf("%d", &coefficients[i]);
    }
    print_polynomial(n, coefficients);
    return 0;
}