#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int used;
} Rectangle;

int n, k;
Point points[50];
int best = INT32_MAX;
Rectangle rects[4];

int overlap(Rectangle a, Rectangle b) {
    if (!a.used || !b.used) return 0;
    if (a.max_x < b.min_x || b.max_x < a.min_x) return 0;
    if (a.max_y < b.min_y || b.max_y < a.min_y) return 0;
    return 1;
}

int calculate_area(Rectangle r) {
    if (!r.used) return 0;
    return (r.max_x - r.min_x) * (r.max_y - r.min_y);
}

int compare(const void *a, const void *b) {
    Point *p1 = (Point*)a;
    Point *p2 = (Point*)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p1->y - p2->y;
}

void backtrack(int index, int current_sum) {
    if (current_sum >= best) return;
    if (index == n) {
        if (current_sum < best) best = current_sum;
        return;
    }
    for(int i = 0; i < k; i++) {
        int prev_min_x = rects[i].min_x;
        int prev_max_x = rects[i].max_x;
        int prev_min_y = rects[i].min_y;
        int prev_max_y = rects[i].max_y;
        int was_used = rects[i].used;
        if (!was_used) {
            rects[i].min_x = points[index].x;
            rects[i].max_x = points[index].x;
            rects[i].min_y = points[index].y;
            rects[i].max_y = points[index].y;
            rects[i].used = 1;
        }
        else {
            rects[i].min_x = (points[index].x < rects[i].min_x) ? points[index].x : rects[i].min_x;
            rects[i].max_x = (points[index].x > rects[i].max_x) ? points[index].x : rects[i].max_x;
            rects[i].min_y = (points[index].y < rects[i].min_y) ? points[index].y : rects[i].min_y;
            rects[i].max_y = (points[index].y > rects[i].max_y) ? points[index].y : rects[i].max_y;
        }
        int valid = 1;
        for(int j = 0; j < k; j++) {
            if (i == j) continue;
            if (overlap(rects[i], rects[j])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            int added_area = 0;
            if (was_used) {
                added_area = (rects[i].max_x - rects[i].min_x) * (rects[i].max_y - rects[i].min_y);
                int prev_area = (prev_max_x - prev_min_x) * (prev_max_y - prev_min_y);
                added_area -= prev_area;
            }
            else {
                added_area = 0;
            }
            backtrack(index + 1, current_sum + added_area);
        }
        rects[i].min_x = prev_min_x;
        rects[i].max_x = prev_max_x;
        rects[i].min_y = prev_min_y;
        rects[i].max_y = prev_max_y;
        rects[i].used = was_used;
    }
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    qsort(points, n, sizeof(Point), compare);
    backtrack(0, 0);
    printf("%d\n", best);
    return 0;
}