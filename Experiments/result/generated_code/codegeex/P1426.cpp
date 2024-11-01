#include <stdio.h>

int main() {
    double s, x;
    scanf("%lf %lf", &s, &x);

    double distance = 0.0;
    double speed = 7.0;

    for (int t = 1; distance <= s + x; t++) {
        if (distance <= s) {
            distance += speed;
        } else {
            printf("y\n");
            return 0;
        }
        speed *= 0.98;
    }

    printf("n\n");
    return 0;
}