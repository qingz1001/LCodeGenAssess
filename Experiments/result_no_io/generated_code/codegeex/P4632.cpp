#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 300005
#define MAXK 1005

int n, k, q;
int x[MAXN], t[MAXN], a[MAXN], b[MAXN];
int l[MAXN], y[MAXN];

typedef struct {
    int x, t;
} Store;

Store stores[MAXN];
int compare(const void *a, const void *b) {
    Store *storeA = (Store *)a;
    Store *storeB = (Store *)b;
    if (storeA->x == storeB->x) return storeA->t - storeB->t;
    return storeA->x - storeB->x;
}

int main() {
    scanf("%d %d %d", &n, &k, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x[i], &t[i], &a[i], &b[i]);
        stores[i] = (Store){x[i], t[i]};
    }
    qsort(stores, n, sizeof(Store), compare);

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &l[i], &y[i]);
    }

    for (int i = 0; i < q; i++) {
        int minDist[MAXK] = {INT_MAX};
        int maxDist = -1;
        bool hasStore[MAXK] = {false};

        // Binary search for the first store with x >= l[i]
        int left = 0, right = n - 1, mid;
        while (left < right) {
            mid = (left + right) / 2;
            if (stores[mid].x < l[i]) left = mid + 1;
            else right = mid;
        }
        int start = left;

        // Binary search for the last store with x <= l[i]
        left = 0, right = n - 1;
        while (left < right) {
            mid = (left + right + 1) / 2;
            if (stores[mid].x > l[i]) right = mid - 1;
            else left = mid;
        }
        int end = right;

        // Check stores within the range [start, end]
        for (int j = start; j <= end; j++) {
            if (a[j] <= y[i] && y[i] <= b[j]) {
                hasStore[stores[j].t] = true;
                minDist[stores[j].t] = l[i] - stores[j].x;
                maxDist = maxDist > minDist[stores[j].t] ? maxDist : minDist[stores[j].t];
            }
        }

        // Check stores before the range [start, end]
        for (int j = start - 1; j >= 0; j--) {
            if (stores[j].x > l[i]) break;
            if (a[j] <= y[i] && y[i] <= b[j]) {
                hasStore[stores[j].t] = true;
                minDist[stores[j].t] = min(minDist[stores[j].t], stores[j].x - l[i]);
                maxDist = maxDist > minDist[stores[j].t] ? maxDist : minDist[stores[j].t];
            }
        }

        // Check stores after the range [start, end]
        for (int j = end + 1; j < n; j++) {
            if (stores[j].x < l[i]) break;
            if (a[j] <= y[i] && y[i] <= b[j]) {
                hasStore[stores[j].t] = true;
                minDist[stores[j].t] = min(minDist[stores[j].t], l[i] - stores[j].x);
                maxDist = maxDist > minDist[stores[j].t] ? maxDist : minDist[stores[j].t];
            }
        }

        // Check if there is at least one store of each type
        bool allStoresPresent = true;
        for (int j = 1; j <= k; j++) {
            if (!hasStore[j]) {
                allStoresPresent = false;
                break;
            }
        }

        if (!allStoresPresent) {
            printf("-1 ");
        } else {
            printf("%d ", maxDist);
        }
    }
    printf("\n");
    return 0;
}