#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l, r, x;
} Query;

int compare(const void *a, const void *b) {
    Query *queryA = (Query *)a;
    Query *queryB = (Query *)b;
    if (queryA->x == queryB->x) {
        return queryA->r - queryB->r;
    }
    return queryA->x - queryB->x;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    Query queries[q];
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &queries[i].l, &queries[i].r, &queries[i].x);
    }

    qsort(queries, q, sizeof(Query), compare);

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