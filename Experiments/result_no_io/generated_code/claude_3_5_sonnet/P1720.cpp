#include <stdio.h>
#include <math.h>

double calculateFn(int n) {
    const double phi = (1 + sqrt(5)) / 2;
    const double psi = (1 - sqrt(5)) / 2;
    return (pow(phi, n) - pow(psi, n)) / sqrt(5);
}

int main() {
    int n;
    scanf("%d", &n);
    
    double result = calculateFn(n);
    printf("%.2f\n", result);
    
    return 0;
}