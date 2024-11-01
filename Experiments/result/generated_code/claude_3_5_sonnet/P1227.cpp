#include <stdio.h>
#include <math.h>

#define MAX_N 20000
#define EPS 1e-6

typedef struct {
    double x, y;
} Point;

Point points[MAX_N];
int n;

int is_symmetric(double cx, double cy) {
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (fabs(points[i].x - cx - (cx - points[j].x)) < EPS &&
                fabs(points[i].y - cy - (cy - points[j].y)) < EPS) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    double sum_x = 0, sum_y = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
        sum_x += points[i].x;
        sum_y += points[i].y;
    }
    
    double cx = sum_x / n;
    double cy = sum_y / n;
    
    if (is_symmetric(cx, cy)) {
        printf("V.I.P. should stay at (%.1f,%.1f).\n", cx, cy);
    } else {
        printf("This is a dangerous situation!\n");
    }
    
    return 0;
}