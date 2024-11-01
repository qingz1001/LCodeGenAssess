#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    double x1, x2, x3;
    // Using the Cardano's formula to solve the cubic equation
    double q = (3 * b - pow(c, 2)) / (9 * a);
    double r = (9 * a * b * c - 27 * a * d - 2 * pow(c, 3)) / (54 * pow(a, 2));
    double discriminant = q * q * q + r * r;

    if (discriminant > 0) {
        double sqrt_discriminant = sqrt(discriminant);
        x1 = -r / 2 + sqrt_discriminant;
        x2 = -r / 2 - sqrt_discriminant;
        x3 = -(q + x1 * x2) / 3;
    } else if (discriminant == 0) {
        x1 = -pow(-r / 3, 1.0/3.0);
        x2 = x1;
        x3 = x1;
    } else {
        double theta = acos(r / sqrt(-(q * q * q)));
        double sqrt_neg_q = sqrt(-q);
        x1 = 2 * sqrt_neg_q * cos(theta / 3.0) - c / (3 * a);
        x2 = 2 * sqrt_neg_q * cos((theta + 2 * M_PI) / 3.0) - c / (3 * a);
        x3 = 2 * sqrt_neg_q * cos((theta + 4 * M_PI) / 3.0) - c / (3 * a);
    }

    printf("%.2f %.2f %.2f\n", x1, x2, x3);

    return 0;
}