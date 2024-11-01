#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y, s;
} Location;

int compare(const void *a, const void *b) {
    return ((Location *)a)->x - ((Location *)b)->x;
}

double minSpeed(int n, Location locations[]) {
    qsort(locations, n, sizeof(Location), compare);

    double left = 0, right = 1e8;
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        int time = 0;

        for (int i = 0; i < n; ++i) {
            if (time < locations[i].x) {
                time += (locations[i].x - time) / mid;
            }
            time += locations[i].s / mid;
            if (time > locations[i].y) {
                left = mid;
                break;
            }
        }

        if (time <= locations[n-1].y) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return left;
}

int main() {
    int n;
    scanf("%d", &n);
    Location *locations = (Location *)malloc(n * sizeof(Location));

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &locations[i].x, &locations[i].y, &locations[i].s);
    }

    printf("%.2f\n", minSpeed(n, locations));

    free(locations);
    return 0;
}