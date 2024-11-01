#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 6
#define PI 3.14159265358979323846

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
Point box[2];
int N;
double max_area = 0;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double calculate_radius(Point p, int used[], int n) {
    double min_dist = 1e9;
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        min_dist = fmin(min_dist, distance(p, points[i]));
    }
    min_dist = fmin(min_dist, fmin(fabs(p.x - box[0].x), fabs(p.x - box[1].x)));
    min_dist = fmin(min_dist, fmin(fabs(p.y - box[0].y), fabs(p.y - box[1].y)));
    return min_dist;
}

void dfs(int depth, double area, int used[]) {
    if (depth == N) {
        max_area = fmax(max_area, area);
        return;
    }
    for (int i = 0; i < N; i++) {
        if (used[i]) continue;
        used[i] = 1;
        double radius = calculate_radius(points[i], used, N);
        dfs(depth + 1, area + PI * radius * radius, used);
        used[i] = 0;
    }
}

int main() {
    scanf("%d", &N);
    scanf("%d %d %d %d", &box[0].x, &box[0].y, &box[1].x, &box[1].y);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int used[MAX_N] = {0};
    dfs(0, 0, used);

    double box_area = fabs((box[1].x - box[0].x) * (box[1].y - box[0].y));
    int result = round(box_area - max_area);
    printf("%d\n", result);

    return 0;
}