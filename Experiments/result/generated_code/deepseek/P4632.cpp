#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300005
#define MAXK 300005
#define MAXQ 300005

typedef struct {
    int x, t, a, b;
} Store;

typedef struct {
    int l, y;
} Query;

Store stores[MAXN];
Query queries[MAXQ];
int results[MAXQ];
int n, k, q;

int cmp(const void *a, const void *b) {
    Store *s1 = (Store *)a;
    Store *s2 = (Store *)b;
    if (s1->a != s2->a) return s1->a - s2->a;
    return s1->b - s2->b;
}

int main() {
    scanf("%d %d %d", &n, &k, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &stores[i].x, &stores[i].t, &stores[i].a, &stores[i].b);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].y);
    }

    qsort(stores, n, sizeof(Store), cmp);

    for (int i = 0; i < q; i++) {
        int l = queries[i].l;
        int y = queries[i].y;
        int max_distance = -1;
        int types[MAXK] = {0};
        int type_count = 0;

        for (int j = 0; j < n; j++) {
            if (stores[j].a <= y && y <= stores[j].b) {
                if (types[stores[j].t] == 0) {
                    types[stores[j].t] = 1;
                    type_count++;
                }
                int distance = abs(stores[j].x - l);
                if (max_distance == -1 || distance > max_distance) {
                    max_distance = distance;
                }
            }
        }

        if (type_count < k) {
            results[i] = -1;
        } else {
            results[i] = max_distance;
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n", results[i]);
    }

    return 0;
}