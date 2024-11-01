#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000
#define MAXM 800

struct Tower {
    int x;
    int y;
};

double dist(struct Tower a, struct Tower b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    struct Tower towers[MAXM];
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &towers[i].x, &towers[i].y);
    }

    double min_radius = 0;
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            double radius = dist(towers[i], towers[j]) / 2.0;
            if (radius > min_radius) {
                min_radius = radius;
            }
        }
    }

    printf("%.2lf\n", min_radius);
    return 0;
}