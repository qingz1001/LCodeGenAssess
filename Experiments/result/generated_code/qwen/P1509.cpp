#include <stdio.h>
#include <stdlib.h>

#define MAXN 105

typedef struct {
    int rmb;
    int rp;
    int time;
} MM;

int compare(const void *a, const void *b) {
    MM *mmA = (MM *)a;
    MM *mmB = (MM *)b;
    if (mmA->rp != mmB->rp) return mmB->rp - mmA->rp;
    return mmB->time - mmA->time;
}

int main() {
    int n, m, r;
    scanf("%d", &n);
    MM mm[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &mm[i].rmb, &mm[i].rp, &mm[i].time);
    }
    scanf("%d %d", &m, &r);

    qsort(mm, n, sizeof(MM), compare);

    int count = 0, total_time = 0;
    for (int i = 0; i < n && m >= mm[i].rmb && r >= mm[i].rp; i++) {
        m -= mm[i].rmb;
        r -= mm[i].rp;
        total_time += mm[i].time;
        count++;
    }

    printf("%d\n", total_time);

    return 0;
}