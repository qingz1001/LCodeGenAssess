#include <stdio.h>
#include <math.h>

int main(){
    int n;
    scanf("%d", &n);
    double sqrt5 = sqrt(5.0);
    double phi = (1.0 + sqrt5)/2.0;
    double psi = (1.0 - sqrt5)/2.0;
    double Fn = (pow(phi, n) - pow(psi, n)) / sqrt5;
    printf("%.2lf\n", Fn);
    return 0;
}