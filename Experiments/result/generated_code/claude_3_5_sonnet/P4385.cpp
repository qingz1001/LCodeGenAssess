#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 1005
#define EPS 1e-9

typedef struct {
    long long x, y;
    char color;
} Point;

Point points[MAX_N];
int n;

int cmp(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if (pa->x != pb->x) return pa->x - pb->x;
    return pa->y - pb->y;
}

int count_red_between(int i, int j) {
    long long dx = points[j].x - points[i].x;
    long long dy = points[j].y - points[i].y;
    int count = 0;
    
    for (int k = 0; k < n; k++) {
        if (k == i || k == j) continue;
        long long cross = (points[k].x - points[i].x) * dy - (points[k].y - points[i].y) * dx;
        if (cross == 0) continue;
        if (cross > 0 && points[k].color == 'R') count++;
    }
    
    return count;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %c", &points[i].x, &points[i].y, &points[i].color);
    }
    
    qsort(points, n, sizeof(Point), cmp);
    
    int max_red = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int red_count = count_red_between(i, j);
            if (red_count > max_red) max_red = red_count;
        }
    }
    
    printf("%d\n", max_red);
    
    return 0;
}