#include <stdio.h>
#include <math.h>

double fibonacci(int n) {
    double sqrt5 = sqrt(5);
    double phi = (1 + sqrt5) / 2;
    double psi = (1 - sqrt5) / 2;
    return (pow(phi, n) - pow(psi, n)) / sqrt5;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%.2f\n", fibonacci(n));
    return 0;
}