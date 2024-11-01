#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double w;
    double x;
    double y;
    double p;
    double q;
    int id;
} Shrimp;

typedef struct {
    double t;
    double x;
    double y;
    int s;
} EatEvent;

int compare(const void *a, const void *b) {
    Shrimp *sa = (Shrimp *)a;
    Shrimp *sb = (Shrimp *)b;
    if (sa->w < sb->w) return -1;
    if (sa->w > sb->w) return 1;
    return 0;
}

int main() {
    double w0, V, T, x0, y0;
    scanf("%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);
    int n;
    scanf("%d", &n);
    Shrimp shrimps[n];
    for(int i=0;i<n;i++) {
        scanf("%lf %lf %lf %lf %lf", &shrimps[i].w, &shrimps[i].x, &shrimps[i].y, &shrimps[i].p, &shrimps[i].q);
        shrimps[i].id = i+1;
    }
    qsort(shrimps, n, sizeof(Shrimp), compare);
    double current_t = 0.0, current_x = x0, current_y = y0, current_w = w0;
    int eaten[n];
    for(int i=0;i<n;i++) eaten[i] = 0;
    EatEvent events[n];
    int k = 0;
    while(1) {
        double min_t = T+1;
        int selected = -1;
        double sel_x, sel_y;
        for(int i=0;i<n;i++) {
            if(eaten[i]) continue;
            if(shrimps[i].w >= current_w) continue;
            // Position of shrimp at time t: (x + p*t, y + q*t)
            // Distance to travel: sqrt((x + p*t - current_x)^2 + (y + q*t - current_y)^2)
            // Time available: t - current_t
            // Distance <= V * (t - current_t)
            // Find t such that distance = V*(t - current_t)
            // This is a nonlinear equation. Solve for t numerically.
            // Initial guess t = current_t
            double left = current_t;
            double right = T;
            double t_eat = -1;
            for(int iter=0; iter<50; iter++) {
                double mid = (left + right)/2;
                double sx = shrimps[i].x + shrimps[i].p * mid;
                double sy = shrimps[i].y + shrimps[i].q * mid;
                double dist = sqrt((sx - current_x)*(sx - current_x) + (sy - current_y)*(sy - current_y));
                double time_needed = mid - current_t;
                if(time_needed <= 0) {
                    dist = INFINITY;
                }
                if(dist <= V * time_needed) {
                    right = mid;
                }
                else {
                    left = mid;
                }
            }
            double sx = shrimps[i].x + shrimps[i].p * right;
            double sy = shrimps[i].y + shrimps[i].q * right;
            double dist = sqrt((sx - current_x)*(sx - current_x) + (sy - current_y)*(sy - current_y));
            double time_needed = right - current_t;
            if(dist <= V * time_needed && right <= T) {
                if(right < min_t) {
                    min_t = right;
                    selected = i;
                    sel_x = sx;
                    sel_y = sy;
                }
            }
        }
        if(selected == -1 || min_t > T) break;
        events[k].t = min_t;
        events[k].x = sel_x;
        events[k].y = sel_y;
        events[k].s = shrimps[selected].id;
        current_t = min_t;
        current_x = sel_x;
        current_y = sel_y;
        current_w += shrimps[selected].w;
        eaten[selected] = 1;
        k++;
    }
    double total_w = 0.0;
    for(int i=0;i<k;i++) {
        // Find shrimp weight
        for(int j=0;j<n;j++) {
            if(shrimps[j].id == events[i].s){
                total_w += shrimps[j].w;
                break;
            }
        }
    }
    printf("%d\n", k);
    printf("%.6lf\n", total_w);
    for(int i=0;i<k;i++) {
        printf("%.6lf %.6lf %.6lf %d\n", events[i].t, events[i].x, events[i].y, events[i].s);
    }
    return 0;
}