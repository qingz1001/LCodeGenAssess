#include <stdio.h>
#include <math.h>

int main() {
    double s, a, b;
    scanf("%lf %lf %lf", &s, &a, &b);

    double t_car = s / b;  // 车单独到达B地的时间
    double t_walk = s / a; // 人步行到达B地的时间

    // 设车先带甲走x距离，然后返回接乙，最后再带乙到B地
    // 设车带甲走x距离的时间为t1，返回接乙的时间为t2，带乙到B地的时间为t3
    // t1 = x / b
    // t2 = (x - x / b * a) / b
    // t3 = (s - x) / b

    // 设车带甲走x距离后，甲步行到B地的时间为t4
    // t4 = (s - x) / a

    // 设车返回接乙的时间为t5
    // t5 = (x - x / b * a) / b

    // 设车带乙到B地的时间为t6
    // t6 = (s - x) / b

    // 两人同时到达B地的时间为t_total
    // t_total = max(t4, t6)

    // 通过二分法求解x，使得t_total最小
    double left = 0, right = s;
    double eps = 1e-8;
    while (right - left > eps) {
        double x = (left + right) / 2;
        double t1 = x / b;
        double t2 = (x - t1 * a) / b;
        double t3 = (s - x) / b;
        double t4 = (s - x) / a;
        double t5 = (x - t1 * a) / b;
        double t6 = (s - x) / b;
        double t_total = fmax(t4, t6);

        if (t4 < t6) {
            left = x;
        } else {
            right = x;
        }
    }

    double x = (left + right) / 2;
    double t1 = x / b;
    double t2 = (x - t1 * a) / b;
    double t3 = (s - x) / b;
    double t4 = (s - x) / a;
    double t5 = (x - t1 * a) / b;
    double t6 = (s - x) / b;
    double t_total = fmax(t4, t6);

    printf("%.6f\n", t_total);

    return 0;
}