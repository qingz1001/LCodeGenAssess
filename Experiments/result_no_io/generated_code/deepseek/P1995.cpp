#include <stdio.h>
#include <math.h>

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

double calculate_time(int n, Rectangle rects[], int xS, int yS, int xT, int yT, double v) {
    double distance = sqrt((xT - xS) * (xT - xS) + (yT - yS) * (yT - yS));
    return distance / v;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Rectangle rects[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &rects[i].x1, &rects[i].y1, &rects[i].x2, &rects[i].y2);
    }
    
    int xS, yS, xT, yT;
    scanf("%d %d", &xS, &yS);
    scanf("%d %d", &xT, &yT);
    
    double v;
    scanf("%lf", &v);
    
    double time = calculate_time(n, rects, xS, yS, xT, yT, v);
    printf("%.6f\n", time);
    
    return 0;
}