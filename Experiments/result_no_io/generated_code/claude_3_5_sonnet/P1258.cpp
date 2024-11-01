#include <stdio.h>
#include <math.h>

double minTime(double s, double a, double b) {
    if (a >= b || a == 0 || b == 0) {
        return s / a;
    }
    
    double t = s / (b + sqrt(b * a));
    return t;
}

int main() {
    double s, a, b;
    scanf("%lf %lf %lf", &s, &a, &b);
    
    double result = minTime(s, a, b);
    printf("%.6f\n", result);
    
    return 0;
}