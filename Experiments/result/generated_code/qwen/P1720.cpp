#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    double golden_ratio = (1 + sqrt(5)) / 2;
    double F_n = (pow(golden_ratio, n) - pow((1 - sqrt(5)) / 2, n)) / sqrt(5);
    printf("%.2f\n", F_n);
    return 0;
}