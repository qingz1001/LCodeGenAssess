#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    double phi = (1 + sqrt(5)) / 2;
    double psi = (1 - sqrt(5)) / 2;
    double result = (pow(phi, n) - pow(psi, n)) / sqrt(5);
    
    printf("%.2f\n", result);
    
    return 0;
}