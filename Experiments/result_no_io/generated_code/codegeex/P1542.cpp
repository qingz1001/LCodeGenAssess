#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
    int s;
} Location;

int compare(const void *a, const void *b) {
    Location *locA = (Location *)a;
    Location *locB = (Location *)b;
    return locA->x - locB->x;
}

int canDeliver(Location *locations, int n, double maxSpeed) {
    double currentTime = 0.0;
    for (int i = 0; i < n; i++) {
        // Calculate the earliest time to reach the current location
        double earliestArrival = currentTime + (double)locations[i].s / maxSpeed;
        
        // If the arrival time is before the earliest sign-in time, we need to wait
        if (earliestArrival < locations[i].x) {
            currentTime = locations[i].x;
        }
        
        // If the arrival time is after the latest sign-in time, it's not possible to deliver
        if (currentTime > locations[i].y) {
            return 0;
        }
        
        // Update the current time to be the latest possible time to reach the next location
        currentTime = locations[i].y;
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Location *locations = (Location *)malloc(n * sizeof(Location));
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &locations[i].x, &locations[i].y, &locations[i].s);
    }
    
    // Sort locations by the earliest sign-in time
    qsort(locations, n, sizeof(Location), compare);
    
    double left = 0.0, right = 1e9;
    while (right - left > 1e-5) {
        double mid = (left + right) / 2.0;
        if (canDeliver(locations, n, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    printf("%.2f\n", right);
    free(locations);
    return 0;
}