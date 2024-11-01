#include <stdio.h>
#include <math.h>

#define MAX_N 5000

typedef struct {
    double x, y;
} Point;

Point points[MAX_N];
int n;

double max(double a, double b) {
    return a > b ? a : b;
}

double getAngle(Point p1, Point p2) {
    return atan2(p2.y - p1.y, p2.x - p1.x);
}

double solve() {
    double left = 0, right = 1e6;
    
    for (int iter = 0; iter < 100; iter++) {
        double mid = (left + right) / 2;
        double maxAngle = -1e9;
        int valid = 1;
        
        for (int i = 0; i < n; i++) {
            double angle = getAngle((Point){points[i].x, mid}, points[i]);
            if (angle > maxAngle) {
                maxAngle = angle;
            } else {
                valid = 0;
                break;
            }
        }
        
        if (valid) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    return left;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    
    printf("%.2f\n", solve());
    
    return 0;
}