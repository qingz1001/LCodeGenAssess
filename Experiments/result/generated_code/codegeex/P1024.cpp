#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, d;
    double x1, x2, x3;

    // 输入方程的系数
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    // 计算判别式
    double discriminant = 18 * a * b * c * d - 4 * b * b * b * d + b * b * c * c - 4 * a * c * c * c - 27 * a * a * d * d;

    // 判别式大于0，有3个实根
    if (discriminant > 0) {
        double q = (3 * a * c - b * b) / (9 * a * a);
        double r = (9 * a * b * c - 27 * a * a * d - 2 * b * b * b) / (54 * a * a * a);
        double theta = acos(r / sqrt(-q * q * q));
        double sqrt_q = sqrt(-q);
        x1 = -2 * sqrt_q * cos(theta / 3) - b / (3 * a);
        x2 = -2 * sqrt_q * cos((theta + 2 * M_PI) / 3) - b / (3 * a);
        x3 = -2 * sqrt_q * cos((theta - 2 * M_PI) / 3) - b / (3 * a);
    }
    // 判别式等于0，有两个实根
    else if (discriminant == 0) {
        x1 = x2 = -b / (3 * a);
        x3 = 2 * sqrt(-b * b / (27 * a * a) - c / (3 * a)) - b / (3 * a);
    }
    // 判别式小于0，有一个实根，两个共轭复根
    else {
        double q = (3 * a * c - b * b) / (9 * a * a);
        double r = (9 * a * b * c - 27 * a * a * d - 2 * b * b * b) / (54 * a * a * a);
        double i = sqrt(-q * q * q);
        double s = sqrt(-q) * cos(acos(r / i) / 3);
        double t = sqrt(-q) * cos((acos(r / i) + 2 * M_PI) / 3);
        x1 = 2 * s - b / (3 * a);
        x2 = -s - t - b / (3 * a);
        x3 = -s + t - b / (3 * a);
    }

    // 排序并输出结果
    if (x1 > x2) {
        double temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (x2 > x3) {
        double temp = x2;
        x2 = x3;
        x3 = temp;
    }
    if (x1 > x2) {
        double temp = x1;
        x1 = x2;
        x2 = temp;
    }

    printf("%.2lf %.2lf %.2lf\n", x1, x2, x3);

    return 0;
}