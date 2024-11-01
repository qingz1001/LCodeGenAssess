#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000
#define MAX_COORD 1000000000

typedef struct {
    long long x, y;
    char dir;
} Mirror;

Mirror mirrors[MAX_N];
int N;
long long Bx, By;

int cmp(const void *a, const void *b) {
    Mirror *m1 = (Mirror *)a;
    Mirror *m2 = (Mirror *)b;
    if (m1->y != m2->y) return m1->y - m2->y;
    return m1->x - m2->x;
}

int main() {
    scanf("%d %lld %lld", &N, &Bx, &By);
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld %c", &mirrors[i].x, &mirrors[i].y, &mirrors[i].dir);
    }

    qsort(mirrors, N, sizeof(Mirror), cmp);

    long long count = 0;
    long long x = 0, y = 0;
    int idx = 0;

    while (y <= MAX_COORD) {
        if (idx < N && mirrors[idx].y == y) {
            if (mirrors[idx].x > x) {
                count += mirrors[idx].x - x;
            }
            if (mirrors[idx].dir == '/') {
                x = 2 * mirrors[idx].x - x;
                y++;
            } else {
                x = mirrors[idx].x;
                y = mirrors[idx].y;
            }
            idx++;
        } else {
            if (y == By && x < Bx) {
                count += Bx - x;
            }
            x++;
            y++;
        }
    }

    printf("%lld\n", count);
    return 0;
}