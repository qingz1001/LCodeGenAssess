#include <stdio.h>
#include <math.h>

#define MAX_N 20000
#define EPS 1e-6

typedef struct {
    double x, y;
} Point;

Point points[MAX_N];
int n;

int main() {
    scanf("%d", &n);
    
    double sum_x = 0, sum_y = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
        sum_x += points[i].x;
        sum_y += points[i].y;
    }
    
    double center_x = sum_x / n;
    double center_y = sum_y / n;
    
    int is_symmetric = 1;
    for (int i = 0; i < n; i++) {
        double opposite_x = 2 * center_x - points[i].x;
        double opposite_y = 2 * center_y - points[i].y;
        
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (fabs(points[j].x - opposite_x) < EPS && fabs(points[j].y - opposite_y) < EPS) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            is_symmetric = 0;
            break;
        }
    }
    
    if (is_symmetric) {
        printf("V.I.P. should stay at (%.1f,%.1f).\n", center_x, center_y);
    } else {
        printf("This is a dangerous situation!\n");
    }
    
    return 0;
}