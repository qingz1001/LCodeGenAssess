#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005
#define MAXQ 300005

typedef struct {
    int x, t, a, b;
} Shop;

typedef struct {
    int l, y;
} Query;

Shop shops[MAXN];
Query queries[MAXQ];

int n, k, q;

int cmp_shop(const void *a, const void *b) {
    return ((Shop *)a)->x - ((Shop *)b)->x;
}

int cmp_query(const void *a, const void *b) {
    return ((Query *)a)->y - ((Query *)b)->y;
}

void solve() {
    qsort(shops, n, sizeof(Shop), cmp_shop);
    qsort(queries, q, sizeof(Query), cmp_query);

    int shop_index = 0;
    int query_index = 0;
    int result[MAXQ];
    for (int i = 0; i < q; ++i) {
        while (shop_index < n && shops[shop_index].a <= queries[i].y) {
            // Add shop to the set of open shops in the current year
            shop_index++;
        }
        if (shop_index == 0) {
            result[i] = -1;
            continue;
        }
        int min_distance = INT_MAX;
        for (int j = 0; j < k; ++j) {
            int closest_distance = INT_MAX;
            int left = 0, right = shop_index - 1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (shops[mid].t == j + 1) {
                    closest_distance = shops[mid].x;
                    break;
                } else if (shops[mid].t < j + 1) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            if (closest_distance != INT_MAX) {
                min_distance = fmin(min_distance, abs(closest_distance - queries[i].l));
            }
        }
        result[i] = min_distance;
    }

    for (int i = 0; i < q; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d %d %d", &n, &k, &q);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &shops[i].x, &shops[i].t, &shops[i].a, &shops[i].b);
    }
    for (int i = 0; i < q; ++i) {
        scanf("%d %d", &queries[i].l, &queries[i].y);
    }
    solve();
    return 0;
}