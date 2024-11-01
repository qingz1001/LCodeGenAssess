#include <stdio.h>
#include <math.h>

#define EPSILON 0.01

typedef struct {
    double x;
    double y;
} Point;

double min(double a, double b) {
    return (a < b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

double calculateY(Point p1, Point p2, double x) {
    if (p2.x == p1.x) return p1.y; // Vertical line
    return p1.y + (x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[N];
    
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    
    double leftmost = points[0].x;
    double rightmost = points[N-1].x;
    double ymin = 0.0;
    
    for (double x = leftmost; x <= rightmost; x += EPSILON) {
        double current_ymin = 0.0;
        for (int i = 0; i < N; i++) {
            if (i == 0 || i == N-1) continue; // Skip the endpoints
            double y = calculateY(points[i-1], points[i], x);
            current_ymin = max(current_ymin, y);
        }
        ymin = max(ymin, current_ymin);
    }
    
    printf("%.2f\n", ymin);
    
    return 0;
}