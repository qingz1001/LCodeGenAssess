#include <stdio.h>

int main() {
    double s, a, b;
    scanf("%lf %lf %lf", &s, &a, &b);
    double time = (2 * s) / (3 * a + b);
    printf("%.6f\n", time);
    return 0;
}