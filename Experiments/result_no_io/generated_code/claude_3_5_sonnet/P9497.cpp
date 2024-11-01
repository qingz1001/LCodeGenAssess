#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1003
#define MAX_Q 500005

int n, q;
int a[MAX_N][MAX_N];
int max_per_row[MAX_N];
int sorted_max[MAX_N];

int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int binary_search(int v) {
    int left = 0, right = n - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (sorted_max[mid] >= v) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &q);
    
    for (int i = 0; i < n; i++) {
        max_per_row[i] = 0;
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] > max_per_row[i]) {
                max_per_row[i] = a[i][j];
            }
        }
        sorted_max[i] = max_per_row[i];
    }
    
    qsort(sorted_max, n, sizeof(int), compare);
    
    for (int i = 0; i < q; i++) {
        int v;
        scanf("%d", &v);
        printf("%d\n", binary_search(v));
    }
    
    return 0;
}