#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 200010

typedef struct {
    int x, h;
} Point;

Point points[MAX_M];
int heights[MAX_M];

int cmp(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p2->h - p1->h;
}

int main() {
    int n, count = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int h, l, r;
        scanf("%d %d %d", &h, &l, &r);
        points[count].x = l;
        points[count++].h = h;
        points[count].x = r;
        points[count++].h = -h;
    }

    qsort(points, count, sizeof(Point), cmp);

    int m = 0, prev_height = 0;
    memset(heights, 0, sizeof(heights));

    printf("%d\n", points[0].x);
    for (int i = 0; i < count; i++) {
        if (points[i].h > 0) {
            if (heights[points[i].h] == 0 && points[i].h > prev_height) {
                printf("%d %d\n", points[i].x, points[i].h);
                prev_height = points[i].h;
            }
            heights[points[i].h]++;
        } else {
            heights[-points[i].h]--;
            if (heights[-points[i].h] == 0) {
                int max_height = 0;
                for (int j = 1; j < MAX_M; j++) {
                    if (heights[j] > 0) {
                        max_height = j;
                    }
                }
                if (max_height != prev_height) {
                    printf("%d %d\n", points[i].x, max_height);
                    prev_height = max_height;
                }
            }
        }
    }

    return 0;
}