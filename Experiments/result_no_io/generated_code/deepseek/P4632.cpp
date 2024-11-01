#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300005
#define MAXK 300005
#define MAXQ 300005

typedef struct {
    int x, t, a, b;
} Shop;

typedef struct {
    int l, y;
} Query;

Shop shops[MAXN];
Query queries[MAXQ];
int result[MAXQ];
int n, k, q;

int compare_shops(const void *a, const void *b) {
    return ((Shop *)a)->x - ((Shop *)b)->x;
}

int compare_queries(const void *a, const void *b) {
    return ((Query *)a)->l - ((Query *)b)->l;
}

int main() {
    scanf("%d %d %d", &n, &k, &q);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &shops[i].x, &shops[i].t, &shops[i].a, &shops[i].b);
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].y);
    }

    qsort(shops, n, sizeof(Shop), compare_shops);
    qsort(queries, q, sizeof(Query), compare_queries);

    for (int i = 0; i < q; i++) {
        int l = queries[i].l;
        int y = queries[i].y;
        int max_distance = -1;
        int type_count[MAXK] = {0};
        int type_found = 0;

        for (int j = 0; j < n; j++) {
            if (shops[j].a <= y && y <= shops[j].b) {
                if (type_count[shops[j].t] == 0) {
                    type_found++;
                }
                type_count[shops[j].t]++;
            }
        }

        if (type_found < k) {
            result[i] = -1;
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (shops[j].a <= y && y <= shops[j].b) {
                int distance = abs(shops[j].x - l);
                if (distance > max_distance) {
                    max_distance = distance;
                }
            }
        }

        result[i] = max_distance;
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}