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
int results[MAXQ];

int compareShops(const void *a, const void *b) {
    return ((Shop *)a)->x - ((Shop *)b)->x;
}

int compareQueries(const void *a, const void *b) {
    return ((Query *)a)->y - ((Query *)b)->y;
}

void update(int *tree, int index, int value) {
    for (; index > 0; index -= index & (-index)) {
        tree[index] += value;
    }
}

int query(int *tree, int index) {
    int sum = 0;
    for (; index < 100000000 + 10; index += index & (-index)) {
        sum += tree[index];
    }
    return sum;
}

int main() {
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &shops[i].x, &shops[i].t, &shops[i].a, &shops[i].b);
    }

    for (int i = 0; i < q; ++i) {
        scanf("%d %d", &queries[i].l, &queries[i].y);
    }

    qsort(shops, n, sizeof(Shop), compareShops);
    qsort(queries, q, sizeof(Query), compareQueries);

    int shopIndex = 0;
    int resultIndex = 0;
    int *trees = (int *)calloc(100000000 + 10, sizeof(int));
    int *lastOpen = (int *)calloc(k + 1, sizeof(int));

    for (int i = 0; i < q; ++i) {
        while (shopIndex < n && shops[shopIndex].x <= queries[i].l) {
            if (shops[shopIndex].a <= queries[i].y && queries[i].y <= shops[shopIndex].b) {
                update(trees, shops[shopIndex].t, 1);
                lastOpen[shops[shopIndex].t] = queries[i].y;
            }
            shopIndex++;
        }

        int minDistance = INT_MAX;
        for (int j = 1; j <= k; ++j) {
            if (lastOpen[j] == 0) continue;
            int distance = abs(lastOpen[j] - queries[i].y);
            minDistance = fmin(minDistance, distance);
        }

        if (minDistance == INT_MAX) {
            results[resultIndex++] = -1;
        } else {
            results[resultIndex++] = minDistance;
        }
    }

    for (int i = 0; i < q; ++i) {
        printf("%d ", results[i]);
    }
    printf("\n");

    free(trees);
    free(lastOpen);
    return 0;
}