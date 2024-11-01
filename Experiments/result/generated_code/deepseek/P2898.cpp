#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXQ 25000

typedef struct {
    int l, r, x;
} Query;

Query queries[MAXQ];
int n, q;

int compare(const void *a, const void *b) {
    Query *qa = (Query *)a;
    Query *qb = (Query *)b;
    if (qa->x != qb->x) return qb->x - qa->x; // Sort by x in descending order
    if (qa->l != qb->l) return qa->l - qb->l; // Sort by l in ascending order
    return qa->r - qb->r; // Sort by r in ascending order
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &queries[i].l, &queries[i].r, &queries[i].x);
    }

    qsort(queries, q, sizeof(Query), compare);

    for (int i = 0; i < q; i++) {
        for (int j = i + 1; j < q; j++) {
            if (queries[i].x == queries[j].x && queries[i].r >= queries[j].l) {
                printf("%d\n", j + 1);
                return 0;
            }
        }
    }

    printf("0\n");
    return 0;
}