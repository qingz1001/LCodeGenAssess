#include <stdio.h>
#include <math.h>

#define MAX_P 500
#define MAX_S 100

typedef struct {
    int x;
    int y;
} Point;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int S, P;
    scanf("%d %d", &S, &P);

    Point sentinel[MAX_P];
    for (int i = 0; i < P; i++) {
        scanf("%d %d", &sentinel[i].x, &sentinel[i].y);
    }

    double max_distance = 0.0;
    for (int i = 0; i < P; i++) {
        for (int j = i + 1; j < P; j++) {
            double d = distance(sentinel[i], sentinel[j]);
            if (d > max_distance) {
                max_distance = d;
            }
        }
    }

    printf("%.2f\n", max_distance);

    return 0;
}