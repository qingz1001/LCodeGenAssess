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
    double currentTime = 0.0;
    for (int i = 0; i < n; i++) {
        double travelTime = locations[i].s / speed;
        currentTime += travelTime;
        if (currentTime > locations[i].y) {
            return 0;
        }
        if (currentTime < locations[i].x) {
            currentTime = locations[i].x;
        }
    }
    return 1;
}

double binarySearch(double left, double right) {
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        if (canDeliverWithSpeed(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return (left + right) / 2;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &locations[i].x, &locations[i].y, &locations[i].s);
    }

    double maxSpeed = binarySearch(0.0, 1e8);
    printf("%.2f\n", maxSpeed);

    return 0;
}