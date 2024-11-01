#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n == 0) {
        printf("0.00\n");
        return 0;
    }

    double phi = (1 + sqrt(5)) / 2;
    double psi = (1 - sqrt(5)) / 2;
    double Fn = (pow(phi, n) - pow(psi, n)) / sqrt(5);

    printf("%.2f\n", Fn);

    return 0;
}