#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 300005
#define MAX_K 300005

typedef struct {
    int x, t, a, b;
} Shop;

typedef struct {
    int l, y;
} Query;

Shop shops[MAX_N];
Query queries[MAX_N];
int n, k, q;

int cmp_shop(const void *a, const void *b) {
    return ((Shop*)a)->x - ((Shop*)b)->x;
}

int cmp_query(const void *a, const void *b) {
    return ((Query*)a)->y - ((Query*)b)->y;
}

int binary_search(int target, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (shops[mid].x == target) return mid;
        if (shops[mid].x < target) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

int main() {
    scanf("%d %d %d", &n, &k, &q);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &shops[i].x, &shops[i].t, &shops[i].a, &shops[i].b);
    }
    
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i].l, &queries[i].y);
    }
    
    qsort(shops, n, sizeof(Shop), cmp_shop);
    qsort(queries, q, sizeof(Query), cmp_query);
    
    int shop_index = 0;
    int type_count[MAX_K] = {0};
    int left[MAX_K], right[MAX_K];
    
    for (int i = 0; i < q; i++) {
        int y = queries[i].y;
        int l = queries[i].l;
        
        while (shop_index < n && shops[shop_index].a <= y) {
            if (shops[shop_index].b >= y) {
                type_count[shops[shop_index].t]++;
            }
            shop_index++;
        }
        
        for (int j = 1; j <= k; j++) {
            left[j] = right[j] = -1;
        }
        
        int pos = binary_search(l, 0, n - 1);
        for (int j = pos - 1; j >= 0; j--) {
            if (shops[j].a <= y && shops[j].b >= y) {
                if (left[shops[j].t] == -1) {
                    left[shops[j].t] = l - shops[j].x;
                }
            }
        }
        
        for (int j = pos; j < n; j++) {
            if (shops[j].a <= y && shops[j].b >= y) {
                if (right[shops[j].t] == -1) {
                    right[shops[j].t] = shops[j].x - l;
                }
            }
        }
        
        int max_distance = -1;
        for (int j = 1; j <= k; j++) {
            if (type_count[j] == 0) {
                max_distance = -1;
                break;
            }
            int min_distance = (left[j] == -1 || (right[j] != -1 && right[j] < left[j])) ? right[j] : left[j];
            if (min_distance > max_distance) {
                max_distance = min_distance;
            }
        }
        
        printf("%d ", max_distance);
    }
    
    return 0;
}