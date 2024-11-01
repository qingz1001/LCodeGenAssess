#include <stdio.h>

int main() {
    double s, a, b;
    scanf("%lf %lf %lf", &s, &a, &b);

    double t1, t2;
    if (a < b / 2) {
        t1 = s / b;
        t2 = s / b;
    } else {
        t1 = s / (a + b) + s / a;
        t2 = s / (a + b);
    }

    printf("%.6lf\n", t1 > t2 ? t2 : t1);
    return 0;
}