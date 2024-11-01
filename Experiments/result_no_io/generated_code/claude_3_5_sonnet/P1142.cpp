#include <stdio.h>
#include <stdlib.h>

#define MAX_N 700

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
int n;

int compare(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if (pa->x != pb->x) return pa->x - pb->x;
    return pa->y - pb->y;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int max_points_on_line() {
    int max_points = 0;
    
    for (int i = 0; i < n; i++) {
        int same_point = 1;
        int vertical = 0;
        int counts[MAX_N] = {0};
        
        for (int j = i + 1; j < n; j++) {
            if (points[i].x == points[j].x && points[i].y == points[j].y) {
                same_point++;
            } else if (points[i].x == points[j].x) {
                vertical++;
            } else {
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                int g = gcd(abs(dx), abs(dy));
                dx /= g;
                dy /= g;
                counts[dx + 350] += 1;
            }
        }
        
        int local_max = vertical;
        for (int k = 0; k < MAX_N; k++) {
            if (counts[k] > local_max) {
                local_max = counts[k];
            }
        }
        local_max += same_point;
        
        if (local_max > max_points) {
            max_points = local_max;
        }
    }
    
    return max_points;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    qsort(points, n, sizeof(Point), compare);
    
    printf("%d\n", max_points_on_line());
    
    return 0;
}