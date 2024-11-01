#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    int a[MAX_N];
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    qsort(a, n, sizeof(int), compare);
    
    int max_min_group = 1;
    int left = 1, right = n;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int count = 1;
        int max_count = 1;
        
        for (int i = 1; i < n; i++) {
            if (a[i] == a[i-1]) {
                count = 1;
            } else {
                count++;
            }
            
            if (count == mid) {
                max_count = mid;
                count = 0;
            }
        }
        
        if (max_count == mid) {
            max_min_group = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    printf("%d\n", max_min_group);
    
    return 0;
}