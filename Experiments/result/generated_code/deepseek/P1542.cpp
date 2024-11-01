#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 200000

typedef struct {
    int x, y, s;
} Location;

Location locations[MAXN];

int n;

int canDeliverWithSpeed(double speed) {
    double current_time = 0.0;
    for (int i = 0; i < n; i++) {
        double travel_time = (double)locations[i].s / speed;
        current_time += travel_time;
        if (current_time < locations[i].x) {
            current_time = locations[i].x;
        }
        if (current_time > locations[i].y) {
            return 0;
        }
    }
    return 1;
}

double binarySearch(double left, double right) {
    while (right - left > 1e-6) {
        double mid = (left + right) / 2.0;
        if (canDeliverWithSpeed(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &locations[i].x, &locations[i].y, &locations[i].s);
    }

    double max_speed = binarySearch(0.0, 1e8);
    printf("%.2f\n", max_speed);

    return 0;
}