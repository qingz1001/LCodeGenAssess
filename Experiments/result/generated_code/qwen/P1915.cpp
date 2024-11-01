#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-4

typedef struct {
    double w;
    double x, y;
    double p, q;
} Shrimp;

typedef struct {
    double t;
    double x, y;
    int s;
} Action;

int main() {
    double w0, V, T, x0, y0;
    scanf("%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);
    
    int n;
    scanf("%d", &n);
    Shrimp shrimps[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf %lf %lf %lf", &shrimps[i].w, &shrimps[i].x, &shrimps[i].y, &shrimps[i].p, &shrimps[i].q);
    }
    
    // Initialize the result
    int k = 0;
    double w = w0;
    Action actions[n];
    
    // Simulate Nemo's movement and eating
    for (double t = 0; t <= T; t += EPS) {
        for (int i = 0; i < n; ++i) {
            double xt = shrimps[i].x + shrimps[i].p * t;
            double yt = shrimps[i].y + shrimps[i].q * t;
            if (fabs(xt - x0) <= EPS && fabs(yt - y0) <= EPS && shrimps[i].w < w) {
                w += shrimps[i].w;
                actions[k++] = (Action){t, xt, yt, i};
            }
        }
        x0 += V * EPS;
        y0 += V * EPS;
    }
    
    // Output the result
    printf("%d\n", k);
    printf("%.6f\n", w);
    for (int i = 0; i < k; ++i) {
        printf("%.6f %.6f %.6f %d\n", actions[i].t, actions[i].x, actions[i].y, actions[i].s);
    }
    
    return 0;
}