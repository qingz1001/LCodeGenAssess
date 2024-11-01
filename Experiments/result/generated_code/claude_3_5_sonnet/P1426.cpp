#include <stdio.h>
#include <math.h>

int main() {
    double s, x;
    scanf("%lf %lf", &s, &x);

    double distance = 0;
    double speed = 7;
    int seconds = 0;

    while (distance < s - x) {
        distance += speed;
        speed *= 0.98;
        seconds++;
    }

    double remaining_distance = s + x - distance;
    double next_second_distance = speed;

    if (remaining_distance <= next_second_distance) {
        printf("n\n");
    } else {
        printf("y\n");
    }

    return 0;
}