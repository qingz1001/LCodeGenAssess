#include <stdio.h>

int main() {
    double s, x;
    scanf("%lf %lf", &s, &x);

    double distance = 0.0;
    double speed = 7.0;

    while (distance < s - x) {
        distance += speed;
        speed *= 0.98;
    }

    if (distance + speed > s + x) {
        printf("n\n");
    } else {
        printf("y\n");
    }

    return 0;
}