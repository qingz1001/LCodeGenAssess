#include <stdio.h>
#include <math.h>

int main() {
    double s, x;
    scanf("%lf %lf", &s, &x);

    double distance = 0.0;
    for (int i = 1; i <= 100; ++i) {
        distance += 7 * pow(0.98, i - 1);
        if (distance >= s && distance <= s + x) {
            printf("y\n");
            return 0;
        }
        if (distance > s + x) {
            printf("n\n");
            return 0;
        }
    }

    printf("n\n");
    return 0;
}