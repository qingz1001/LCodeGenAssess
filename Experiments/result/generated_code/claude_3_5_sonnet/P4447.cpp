#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int n, a[MAX_N];
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    qsort(a, n, sizeof(int), cmp);
    
    int left = 1, right = n;
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        int count = 1, last = a[0];
        int valid = 1;
        
        for (int i = 1; i < n; i++) {
            if (a[i] == last) {
                count++;
            } else {
                count = 1;
                last = a[i];
            }
            if (count > mid) {
                valid = 0;
                break;
            }
        }
        
        if (valid) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    
    printf("%d\n", left);
    
    return 0;
}