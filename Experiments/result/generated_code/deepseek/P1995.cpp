#include <stdio.h>
#include <math.h>

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    int n;
    scanf("%d", &n);

    Rectangle rectangles[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
    }

    int xS, yS, xT, yT;
    scanf("%d %d", &xS, &yS);
    scanf("%d %d", &xT, &yT);

    double v;
    scanf("%lf", &v);

    double totalDistance = distance(xS, yS, xT, yT);
    double time = totalDistance / v;

    printf("%.8f\n", time);

    return 0;
}