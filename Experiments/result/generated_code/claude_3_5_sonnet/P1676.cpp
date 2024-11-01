#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int n, m;
int positions[MAX_N];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int check(int distance) {
    int count = 1;
    int last = positions[0];
    
    for (int i = 1; i < n; i++) {
        if (positions[i] - last >= distance) {
            count++;
            last = positions[i];
        }
        if (count >= m) return 1;
    }
    return 0;
}

int binary_search() {
    int left = 0;
    int right = positions[n-1] - positions[0];
    int result = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }
    
    qsort(positions, n, sizeof(int), compare);
    
    int max_min_distance = binary_search();
    
    printf("%d\n", max_min_distance);
    
    return 0;
}