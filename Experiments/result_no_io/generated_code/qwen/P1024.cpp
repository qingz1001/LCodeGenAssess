#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    // 计算判别式
    double delta = 18 * a * b * c * d - 4 * pow(b * b, 3) - 4 * pow(c * c, 1) * a * a + 18 * a * c * b * b - 27 * d * d * a;

    if (delta > 0) {
        // 三个不同的实根
        double p = (-b * b * b + 3 * a * b * c - 9 * a * c * c + 27 * a * d) / (27 * a * a);
        double q = (2 * pow(b * b, 3) - 9 * a * b * c * b + 27 * a * c * c * b - 27 * a * d * b) / (54 * a * a * a);
        double r = acos(q / sqrt(-p * p * p / 27.0)) / 3.0;
        double s = -sqrt(-p / 3.0);
        double t = cos(r);
        double u = sin(r) * sqrt(3.0);
        double v = b / (3.0 * a);

        double root1 = s * t - u + v;
        double root2 = -s * t / 2.0 + u * sqrt(3.0) / 2.0 + v;
        double root3 = -s * t / 2.0 - u * sqrt(3.0) / 2.0 + v;

        printf("%.2f %.2f %.2f\n", root1, root2, root3);
    } else if (delta == 0) {
        // 一个实根和两个相同的虚根
        double root = -b / (3.0 * a);
        printf("%.2f %.2f %.2f\n", root, root, root);
    } else {
        // 三个不同的实根
        double p = (-b * b * b + 3 * a * b * c - 9 * a * c * c + 27 * a * d) / (27 * a * a);
        double q = (2 * pow(b * b, 3) - 9 * a * b * c * b + 27 * a * c * c * b - 27 * a * d * b) / (54 * a * a * a);
        double r = acosh(fabs(q) / sqrt(-p * p * p / 27.0)) / 3.0;
        double s = -sqrt(-p / 3.0);
        double t = cosh(r);
        double u = sinh(r) * sqrt(3.0);
        double v = b / (3.0 * a);

        double root1 = s * t - u + v;
        double root2 = -s * t / 2.0 + u * sqrt(3.0) / 2.0 + v;
        double root3 = -s * t / 2.0 - u * sqrt(3.0) / 2.0 + v;

        printf("%.2f %.2f %.2f\n", root1, root2, root3);
    }

    return 0;
}