#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXN 6
#define PI 3.14159265358979323846

typedef struct {
    int x, y;
} Point;

int N;
Point box[4];
Point points[MAXN];

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double min(double a, double b) {
    return a < b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

double calculate_radius(int i, int *visited) {
    double min_dist = 1e9;
    for (int j = 0; j < N; j++) {
        if (visited[j] && j != i) {
            min_dist = min(min_dist, distance(points[i], points[j]));
        }
    }
    min_dist = min(min_dist, points[i].x - box[0].x);
    min_dist = min(min_dist, box[1].x - points[i].x);
    min_dist = min(min_dist, points[i].y - box[0].y);
    min_dist = min(min_dist, box[2].y - points[i].y);
    return min_dist;
}

double calculate_area(int *order) {
    int visited[MAXN] = {0};
    double total_area = 0.0;
    for (int i = 0; i < N; i++) {
        visited[order[i]] = 1;
        double radius = calculate_radius(order[i], visited);
        total_area += PI * radius * radius;
    }
    return total_area;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *order, int l, int r, double *min_area) {
    if (l == r) {
        double area = calculate_area(order);
        *min_area = max(*min_area, area);
    } else {
        for (int i = l; i <= r; i++) {
            swap((order + l), (order + i));
            permute(order, l + 1, r, min_area);
            swap((order + l), (order + i));
        }
    }
}

int main() {
    scanf("%d", &N);
    scanf("%d %d %d %d", &box[0].x, &box[0].y, &box[1].x, &box[2].y);
    box[1].y = box[0].y;
    box[2].x = box[0].x;
    box[3].x = box[1].x;
    box[3].y = box[2].y;

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int order[MAXN];
    for (int i = 0; i < N; i++) {
        order[i] = i;
    }

    double min_area = 0.0;
    permute(order, 0, N - 1, &min_area);

    double box_area = (box[1].x - box[0].x) * (box[2].y - box[0].y);
    double remaining_area = box_area - min_area;
    printf("%.0lf\n", round(remaining_area));

    return 0;
}