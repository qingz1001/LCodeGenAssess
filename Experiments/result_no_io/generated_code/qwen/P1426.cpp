#include <stdio.h>
#include <math.h>

int main() {
    double s, x;
    scanf("%lf %lf", &s, &x);

    double distance = 0.0;
    double speed = 7.0;

    for (int i = 1; i <= 100; ++i) {
        distance += speed;
        if (distance >= s - x && distance <= s + x) {
            if (i == 1 || distance > s + x) {
                printf("n\n");
                return 0;
            } else {
                printf("y\n");
                return 0;
            }
        }
        speed *= 0.98;
    }

    printf("n\n");
    return 0;
}