#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    double expected_local_maxima = (double)n / 2.0 + 0.5;
    printf("%.8f\n", expected_local_maxima);
    return 0;
}