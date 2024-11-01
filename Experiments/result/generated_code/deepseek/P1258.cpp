#include <stdio.h>
#include <math.h>

int main() {
    double s, a, b;
    scanf("%lf %lf %lf", &s, &a, &b);

    double t_car = s / b; // 车单独到达B地的时间
    double t_walk = s / a; // 人步行到达B地的时间

    // 计算两人同时到达的最短时间
    double t_min = (s * (b + a)) / (2 * b * a);

    printf("%.6f\n", t_min);

    return 0;
}