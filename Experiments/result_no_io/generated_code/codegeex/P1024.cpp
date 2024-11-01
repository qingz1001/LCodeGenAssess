#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, d;
    double x1, x2, x3;
    double p, q, r;
    double delta, theta;

    // 读取输入
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    // 计算判别式
    p = (3 * c / a - pow(b, 2) / (a * a)) / 3;
    q = (2 * pow(b, 3) / (a * a * a) - 9 * b * c / (a * a) + 27 * d / a) / 27;
    r = pow(q, 2) / 4 + pow(p, 3) / 27;

    // 判断根的情况
    if (r > 0) {
        delta = sqrt(r);
        theta = acos(-q / (2 * delta));
        x1 = -2 * delta * cos(theta / 3) - b / (3 * a);
        x2 = -2 * delta * cos((theta + 2 * M_PI) / 3) - b / (3 * a);
        x3 = -2 * delta * cos((theta - 2 * M_PI) / 3) - b / (3 * a);
    } else {
        delta = sqrt(-p / 3);
        theta = acos(-q / (2 * pow(delta, 3)));
        x1 = 2 * delta * cos(theta / 3) - b / (3 * a);
        x2 = 2 * delta * cos((theta + 2 * M_PI) / 3) - b / (3 * a);
        x3 = 2 * delta * cos((theta - 2 * M_PI) / 3) - b / (3 * a);
    }

    // 按照从小到大的顺序输出根
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

    // 输出结果
    printf("%.2lf %.2lf %.2lf\n", x1, x2, x3);

    return 0;
}