#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l, r, x;
} Query;

int cmp(const void *a, const void *b) {
    Query *q1 = (Query *)a;
    Query *q2 = (Query *)b;
    return q1->x - q2->x;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    Query queries[25001];
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &queries[i].l, &queries[i].r, &queries[i].x);
    }

    qsort(queries, q, sizeof(Query), cmp);

    int left = 1, right = n;
    for (int i = 0; i < q; i++) {
        if (queries[i].x < left || queries[i].x > right) {
            printf("%d\n", i + 1);
            return 0;
        }
        left = queries[i].l;
        right = queries[i].r;
    }

    printf("0\n");
    return 0;
}