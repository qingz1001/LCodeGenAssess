#include <stdio.h>

void print_polynomial(int n, int coefficients[]) {
    for (int i = 0; i <= n; i++) {
        int coeff = coefficients[i];
        int exp = n - i;

        if (coeff == 0) continue;

        if (i > 0) {
            if (coeff > 0) printf("+");
            else printf("-");
        } else if (coeff < 0) {
            printf("-");
        }

        if (coeff != 1 && coeff != -1 || exp == 0) {
            printf("%d", coeff > 0 ? coeff : -coeff);
        }

        if (exp > 0) {
            printf("x");
            if (exp > 1) {
                printf("^%d", exp);
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