#include <stdio.h>

int main() {
    long long n;
    scanf("%lld", &n);

    double expected_local_maxima = (double)n / 2.0;

    printf("%.8f\n", expected_local_maxima);

    return 0;
}