#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double start;
    double end;
    int distance;
} Location;

int compare(const void *a, const void *b) {
    return ((Location *)a)->start - ((Location *)b)->start > 0 ? 1 : -1;
}

double min_speed(int n, Location locations[]) {
    qsort(locations, n, sizeof(Location), compare);

    double left = 0.0, right = 1e8;
    while (right - left > 1e-9) {
        double mid = (left + right) / 2.0;
        double current_time = 0.0;
        for (int i = 0; i < n; i++) {
            if (current_time + (double)locations[i].distance / mid > locations[i].end) {
                left = mid;
                break;
            }
            current_time += (double)locations[i].distance / mid;
            if (current_time < locations[i].start) {
                current_time = locations[i].start;
            }
        }
        if (i == n) {
            right = mid;
        }
    }
    return right;
}

int main() {
    int n;
    scanf("%d", &n);
    Location *locations = (Location *)malloc(n * sizeof(Location));
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %d", &locations[i].start, &locations[i].end, &locations[i].distance);
    }

    printf("%.2f\n", min_speed(n, locations));

    free(locations);
    return 0;
}