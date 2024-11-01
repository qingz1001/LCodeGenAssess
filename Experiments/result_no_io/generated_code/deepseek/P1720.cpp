#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    double sqrt5 = sqrt(5);
    double phi = (1 + sqrt5) / 2;
    double psi = (1 - sqrt5) / 2;

    double Fn = (pow(phi, n) - pow(psi, n)) / sqrt5;

    printf("%.2f\n", Fn);

    return 0;
}