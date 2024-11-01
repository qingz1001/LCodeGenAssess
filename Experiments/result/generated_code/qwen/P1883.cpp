#include <stdio.h>
#include <math.h>

double f(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

double findMinValue(int n, double coefficients[][3]) {
    double left = 0, right = 1000;
    while (right - left > 1e-6) {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        double value1 = 0, value2 = 0;
        for (int i = 0; i < n; i++) {
            value1 = max(value1, f(mid1, coefficients[i][0], coefficients[i][1], coefficients[i][2]));
            value2 = max(value2, f(mid2, coefficients[i][0], coefficients[i][1], coefficients[i][2]));
        }
        if (value1 < value2) {
            right = mid2;
        } else {
            left = mid1;
        }
    }
    return left;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        double coefficients[n][3];
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &coefficients[i][0], &coefficients[i][1], &coefficients[i][2]);
        }
        printf("%.4f\n", findMinValue(n, coefficients));
    }
    return 0;
}