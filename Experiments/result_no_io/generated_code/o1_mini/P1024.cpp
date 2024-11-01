#include <stdio.h>
#include <math.h>

double f(double a, double b, double c, double d, double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

double find_root(double a, double b, double c, double d, double left, double right) {
    double mid;
    while (right - left > 1e-7) {
        mid = (left + right) / 2.0;
        double f_left = f(a, b, c, d, left);
        double f_mid = f(a, b, c, d, mid);
        if (f_left * f_mid <= 0)
            right = mid;
        else
            left = mid;
    }
    return (left + right) / 2.0;
}

int main(){
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    double roots[3];
    int count = 0;
    double x = -100.0;
    double step = 0.5;
    while (x < 100.0 && count < 3){
        double f_x = f(a, b, c, d, x);
        double f_next = f(a, b, c, d, x + step);
        if (f_x * f_next <= 0){
            roots[count++] = find_root(a, b, c, d, x, x + step);
        }
        x += step;
    }
    // Sort the roots
    double temp;
    if (roots[0] > roots[1]){
        temp = roots[0];
        roots[0] = roots[1];
        roots[1] = temp;
    }
    if (roots[1] > roots[2]){
        temp = roots[1];
        roots[1] = roots[2];
        roots[2] = temp;
    }
    if (roots[0] > roots[1]){
        temp = roots[0];
        roots[0] = roots[1];
        roots[1] = temp;
    }
    printf("%.2lf %.2lf %.2lf\n", roots[0], roots[1], roots[2]);
    return 0;
}