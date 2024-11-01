#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500
#define MAX_COORD 10000

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
int C, N;

int compare(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if (pa->x != pb->x) return pa->x - pb->x;
    return pa->y - pb->y;
}

int count_points(int x1, int y1, int side) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (points[i].x >= x1 && points[i].x <= x1 + side &&
            points[i].y >= y1 && points[i].y <= y1 + side) {
            count++;
        }
    }
    return count;
}

int solve() {
    int min_side = 10001;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int left = points[i].x;
            int bottom = points[j].y;
            int right = left + min_side - 1;
            int top = bottom + min_side - 1;
            
            while (right >= left && top >= bottom) {
                int side = right - left + 1;
                if (count_points(left, bottom, side) >= C) {
                    if (side < min_side) min_side = side;
                    break;
                }
                right--;
                top--;
            }
        }
    }
    return min_side;
}

int main() {
    scanf("%d %d", &C, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    qsort(points, N, sizeof(Point), compare);
    
    printf("%d\n", solve());
    
    return 0;
}