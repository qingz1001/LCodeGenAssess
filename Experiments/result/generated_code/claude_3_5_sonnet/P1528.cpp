#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 1024

int cakes[MAX_N];
int mouths[MAX_M];
int n, m;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int can_satisfy(int mid) {
    int cake_idx = n - 1;
    int mouth_idx = mid - 1;
    
    while (cake_idx >= 0 && mouth_idx >= 0) {
        int pieces = cakes[cake_idx] / mouths[mouth_idx];
        cake_idx--;
        mouth_idx -= pieces;
    }
    
    return mouth_idx < 0;
}

int binary_search() {
    int left = 0, right = m;
    
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (can_satisfy(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    
    return left;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &cakes[i]);
    }
    
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &mouths[i]);
    }
    
    qsort(cakes, n, sizeof(int), compare);
    qsort(mouths, m, sizeof(int), compare);
    
    int result = binary_search();
    printf("%d\n", result);
    
    return 0;
}