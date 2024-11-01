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
    int next = a;
    while (1) {
        int partner = pairs[next];
        if (partner == -1) return 0;
        next = (partner + 1) % n;
        if (next == a) return 1;
        if (holes[next].y != holes[partner].y) return 0;
    }
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
    int total = 0;
    for (j = i + 1; j < n; j++) {
        if (pairs[j] == -1) {
            pairs[i] = j;
            pairs[j] = i;
            total += count_cycles();
            pairs[i] = pairs[j] = -1;
        }
    }
    return total;
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