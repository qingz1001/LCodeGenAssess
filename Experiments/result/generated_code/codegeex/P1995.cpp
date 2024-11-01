#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000

struct Rectangle {
    int x1, y1, x2, y2;
};

double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int n;
    scanf("%d", &n);

    struct Rectangle rectangles[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
    }

    int startX, startY, endX, endY;
    scanf("%d %d", &startX, &startY);
    scanf("%d %d", &endX, &endY);

    double speed;
    scanf("%lf", &speed);

    double minTime = INFINITY;

    // Calculate the minimum time to reach each rectangle
    for (int i = 0; i < n; i++) {
        double timeToStart = calculateDistance(rectangles[i].x1, rectangles[i].y1, startX, startY) / speed;
        double timeToEnd = calculateDistance(rectangles[i].x1, rectangles[i].y1, endX, endY) / speed;
        double totalTime = timeToStart + timeToEnd;

        if (totalTime < minTime) {
            minTime = totalTime;
        }
    }

    printf("%.6lf\n", minTime);
    return 0;
}