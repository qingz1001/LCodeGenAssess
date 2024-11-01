#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define MAXK 300005
#define MAXQ 300005
#define INF 100000000

typedef struct {
    int x, t, a, b;
} Store;

typedef struct {
    int l, y;
} Query;

Store stores[MAXN];
Query queries[MAXQ];
int n, k, q;
int results[MAXQ];

void quickSortStores(int left, int right) {
    int i = left, j = right;
    Store temp = stores[(left + right) / 2];
    while (i <= j) {
        while (stores[i].x < temp.x) i++;
        while (stores[j].x > temp.x) j--;
        if (i <= j) {
            Store t = stores[i];
            stores[i] = stores[j];
            stores[j] = t;
            i++;
            j--;
        }
    }
    if (left < j) quickSortStores(left, j);
    if (i < right) quickSortStores(i, right);
}

void quickSortQueries(int left, int right) {
    int i = left, j = right;
    Query temp = queries[(left + right) / 2];
    while (i <= j) {
        while (queries[i].l < temp.l) i++;
        while (queries[j].l > temp.l) j--;
        if (i <= j) {
            Query t = queries[i];
            queries[i] = queries[j];
            queries[j] = t;
            i++;
            j--;
        }
    }
    if (left < j) quickSortQueries(left, j);
    if (i < right) quickSortQueries(i, right);
}

int main() {
    scanf("%d %d %d", &n, &k, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &stores[i].x, &stores[i].t, &stores[i].a, &stores[i].b);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].y);
    }

    quickSortStores(0, n - 1);
    quickSortQueries(0, q - 1);

    int j = 0;
    for (int i = 0; i < q; i++) {
        int maxDist = -1;
        int validTypes = 0;
        for (int t = 1; t <= k; t++) {
            int minDist = INF;
            while (j < n && stores[j].x <= queries[i].l) {
                if (stores[j].t == t && stores[j].a <= queries[i].y && stores[j].b >= queries[i].y) {
                    minDist = stores[j].x - queries[i].l;
                    break;
                }
                j++;
            }
            if (minDist != INF) {
                validTypes++;
                if (minDist > maxDist) maxDist = minDist;
            }
        }
        if (validTypes == 0) {
            results[i] = -1;
        } else {
            results[i] = maxDist;
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n", results[i]);
    }

    return 0;
}