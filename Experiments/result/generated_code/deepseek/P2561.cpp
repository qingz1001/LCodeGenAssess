#include <stdio.h>
#include <gmp.h>

int main() {
    int n;
    scanf("%d", &n);

    mpz_t result;
    mpz_init(result);

    mpz_ui_pow_ui(result, 3, n);
    mpz_sub_ui(result, result, 1);
    mpz_div_ui(result, result, 2);

    gmp_printf("%Zd\n", result);

    mpz_clear(result);

    return 0;
}