#include <stdio.h>
#include <stdlib.h>

#define MAXN 200000

typedef struct {
    int a, b;
} Rope;

int cmp(const void *a, const void *b) {
    Rope *ropeA = (Rope *)a;
    Rope *ropeB = (Rope *)b;
    return (ropeA->a != ropeB->a) ? (ropeA->a - ropeB->a) : (ropeA->b - ropeB->b);
}

int main() {
    int n;
    scanf("%d", &n);
    Rope ropes[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ropes[i].a, &ropes[i].b);
        if (ropes[i].a > ropes[i].b) {
            int temp = ropes[i].a;
            ropes[i].a = ropes[i].b;
            ropes[i].b = temp;
        }
    }

    qsort(ropes, n, sizeof(Rope), cmp);

    int cuts = 0;
    int last_cut = -1;
    for (int i = 0; i < n; i++) {
        if (ropes[i].a > last_cut) {
            cuts++;
            last_cut = ropes[i].b;
        }
    }

    printf("%d\n", cuts);
    return 0;
}