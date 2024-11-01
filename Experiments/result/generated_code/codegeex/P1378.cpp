#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    int x;
    int y;
} Point;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

double distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    int N;
    scanf("%d", &N);

    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    Point points[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int xMin = min(x1, x2);
    int xMax = max(x1, x2);
    int yMin = min(y1, y2);
    int yMax = max(y1, y2);

    double totalArea = 0;
    for (int i = 0; i < N; i++) {
        double maxRadius = -1;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                double dist = distance(points[i], points[j]);
                maxRadius = max(maxRadius, dist);
            }
        }
        maxRadius = min(maxRadius, min(xMax - points[i].x, points[i].x - xMin));
        maxRadius = min(maxRadius, min(yMax - points[i].y, points[i].y - yMin));
        totalArea += PI * pow(maxRadius, 2);
    }

    int rectArea = (xMax - xMin) * (yMax - yMin);
    int remainingArea = rectArea - (int)(totalArea + 0.5);

    printf("%d\n", remainingArea);

    return 0;
}