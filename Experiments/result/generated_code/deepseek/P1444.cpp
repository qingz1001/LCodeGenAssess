#include <stdio.h>
#include <stdlib.h>

#define MAXN 12

typedef struct {
    int x, y;
} Point;

Point holes[MAXN];
int pairs[MAXN];
int n;

int cmp(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->y == p2->y) return p1->x - p2->x;
    return p1->y - p2->y;
}

int is_cycle(int a, int b) {
    int pos = a;
    for (int i = 0; i < n; i++) {
        pos = pairs[pos];
        if (pos == b) return 1;
        pos = (pos + 1) % n;
        while (holes[pos].y != holes[pairs[pos]].y) pos = (pos + 1) % n;
    }
    return 0;
}

int count_cycles() {
    int i, j;
    for (i = 0; i < n; i++) {
        if (pairs[i] == -1) break;
    }
    if (i == n) {
        for (i = 0; i < n; i++) {
            if (is_cycle(i, pairs[i])) return 1;
        }
        return 0;
    }
    int count = 0;
    for (j = i + 1; j < n; j++) {
        if (pairs[j] == -1) {
            pairs[i] = j;
            pairs[j] = i;
            count += count_cycles();
            pairs[i] = pairs[j] = -1;
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &holes[i].x, &holes[i].y);
        pairs[i] = -1;
    }
    qsort(holes, n, sizeof(Point), cmp);
    printf("%d\n", count_cycles());
    return 0;
}