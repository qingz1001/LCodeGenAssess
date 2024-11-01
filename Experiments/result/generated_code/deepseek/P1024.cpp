#include <stdio.h>
#include <math.h>

double a, b, c, d;

double f(double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

void findRoots() {
    double x1, x2, x;
    int count = 0;

    for (x = -100; x <= 100; x += 0.01) {
        if (f(x) * f(x + 1) <= 0) {
            x1 = x;
            x2 = x + 1;
            while (x2 - x1 > 0.0001) {
                double mid = (x1 + x2) / 2;
                if (f(mid) * f(x1) <= 0) {
                    x2 = mid;
                } else {
                    x1 = mid;
                }
            }
            printf("%.2f ", x1);
            count++;
            if (count == 3) break;
        }
    }
}

int main() {
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    findRoots();
    return 0;
}