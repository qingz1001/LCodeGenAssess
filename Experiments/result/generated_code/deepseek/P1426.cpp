#include <stdio.h>

int main() {
    double s, x;
    scanf("%lf %lf", &s, &x);

    double distance = 7.0;
    double total_distance = 0.0;

    while (total_distance < s - x) {
        total_distance += distance;
        distance *= 0.98;
    }

    if (total_distance + distance > s + x) {
        printf("n\n");
    } else {
        printf("y\n");
    }

    return 0;
}