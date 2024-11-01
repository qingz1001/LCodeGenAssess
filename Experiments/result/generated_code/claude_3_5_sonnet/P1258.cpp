#include <stdio.h>
#include <math.h>

double solve(double s, double a, double b) {
    if (a >= b || s == 0 || a == 0) {
        return s / a;
    }
    
    double t = s / (b + a);
    double x = t * (b - a);
    
    return t + x / b;
}

int main() {
    double s, a, b;
    scanf("%lf %lf %lf", &s, &a, &b);
    
    double result = solve(s, a, b);
    
    printf("%.6f\n", result);
    
    return 0;
}