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
    double min_radius = 1e9;
    
    // Check distance to box edges
    min_radius = fmin(min_radius, p.x - box[0].x);
    min_radius = fmin(min_radius, box[1].x - p.x);
    min_radius = fmin(min_radius, p.y - box[0].y);
    min_radius = fmin(min_radius, box[1].y - p.y);
    
    // Check distance to other used points
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            min_radius = fmin(min_radius, distance(p, points[i]));
        }
    }
    
    return min_radius;
}

void dfs(int depth, int used[], double current_area) {
    if (depth == N) {
        max_area = fmax(max_area, current_area);
        return;
    }
    
    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            used[i] = 1;
            double radius = calculate_radius(points[i], used, N);
            dfs(depth + 1, used, current_area + PI * radius * radius);
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &N);
    scanf("%d %d %d %d", &box[0].x, &box[0].y, &box[1].x, &box[1].y);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    int used[MAX_N] = {0};
    dfs(0, used, 0);
    
    double total_area = (box[1].x - box[0].x) * (box[1].y - box[0].y);
    double remaining_area = total_area - max_area;
    
    printf("%d\n", (int)round(remaining_area));
    
    return 0;
}