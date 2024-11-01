#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SHRIMP 100

typedef struct {
    double weight;
    double x;
    double y;
    double vx;
    double vy;
} Shrimp;

typedef struct {
    double time;
    double x;
    double y;
    int shrimp_index;
} Event;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int compare(const void *a, const void *b) {
    Event *event_a = (Event *)a;
    Event *event_b = (Event *)b;
    if (event_a->time < event_b->time) return -1;
    if (event_a->time > event_b->time) return 1;
    return 0;
}

int main() {
    double w0, V, T, x0, y0;
    int n;
    Shrimp shrimp[MAX_SHRIMP];
    Event events[2 * MAX_SHRIMP];

    // Read input
    scanf("%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf %lf", &shrimp[i].weight, &shrimp[i].x, &shrimp[i].y, &shrimp[i].vx, &shrimp[i].vy);
    }

    // Initialize events
    int event_count = 0;
    for (int i = 0; i < n; i++) {
        double t = (w0 / shrimp[i].weight);
        events[event_count++] = (Event){t, shrimp[i].x, shrimp[i].y, i};
    }

    // Sort events
    qsort(events, event_count, sizeof(Event), compare);

    // Process events
    double current_time = 0.0;
    double current_x = x0;
    double current_y = y0;
    double current_weight = w0;
    int shrimp_eaten = 0;
    double total_weight = 0.0;

    for (int i = 0; i < event_count; i++) {
        double next_time = events[i].time;
        double next_x = events[i].x;
        double next_y = events[i].y;
        int shrimp_index = events[i].shrimp_index;

        double dist = distance(current_x, current_y, next_x, next_y);
        double time_to_reach = dist / V;

        if (time_to_reach <= next_time && current_weight > shrimp[shrimp_index].weight) {
            // Nemo can eat the shrimp
            printf("%.6lf %.6lf %.6lf %d\n", next_time, next_x, next_y, shrimp_index);
            current_weight += shrimp[shrimp_index].weight;
            total_weight += shrimp[shrimp_index].weight;
            shrimp_eaten++;
        }
    }

    // Output results
    printf("%d\n", shrimp_eaten);
    printf("%.6lf\n", total_weight);

    return 0;
}