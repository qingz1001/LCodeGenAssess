#include <stdio.h>
#include <math.h>

#define MAXN 5000

typedef struct {
    double x, y;
} Point;

Point points[MAXN];

double slope(Point a, Point b) {
    return (b.y - a.y) / (b.x - a.x);
}

int main() {
    int N;
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    
    double min_y = points[0].y;
    
    for (int i = 1; i < N; i++) {
        double max_slope = -INFINITY;
        for (int j = 0; j < i; j++) {
            double current_slope = slope(points[j], points[i]);
            if (current_slope > max_slope) {
                max_slope = current_slope;
            }
        }
        double y_intercept = points[i].y - max_slope * points[i].x;
        if (y_intercept < min_y) {
            min_y = y_intercept;
        }
    }
    
    printf("%.2f\n", min_y);
    
    return 0;
}