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

int cmp_shop(const void* a, const void* b) {
    return ((Shop*)a)->x - ((Shop*)b)->x;
}

int cmp_query(const void* a, const void* b) {
    return ((Query*)a)->y - ((Query*)b)->y;
}

int find_nearest(int pos, int type, int year) {
    int left = 0, right = n - 1, nearest = INT_MAX;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (shops[mid].t == type && shops[mid].a <= year && year <= shops[mid].b) {
            nearest = abs(shops[mid].x - pos);
            if (shops[mid].x < pos) left = mid + 1;
            else right = mid - 1;
        } else if (shops[mid].x < pos) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return nearest;
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
    
    int results[MAX_N];
    int query_index = 0;
    
    for (int i = 0; i < q; i++) {
        int max_distance = -1;
        int all_types_present = 1;
        
        for (int j = 1; j <= k; j++) {
            int distance = find_nearest(queries[i].l, j, queries[i].y);
            if (distance == INT_MAX) {
                all_types_present = 0;
                break;
            }
            if (distance > max_distance) {
                max_distance = distance;
            }
        }
        
        results[i] = all_types_present ? max_distance : -1;
    }
    
    for (int i = 0; i < q; i++) {
        printf("%d ", results[i]);
    }
    
    return 0;
}