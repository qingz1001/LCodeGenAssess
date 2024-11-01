#include <stdio.h>
#include <stdlib.h>

#define MAX_N 400005

int n, k;
int a[MAX_N];

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int check(int x) {
    int operations = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < x) {
            operations++;
            i++;
            while (i < n && a[i] < x) i++;
        }
    }
    return operations <= k;
}

int binary_search() {
    int left = 0, right = 1000000000;
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    qsort(a, n, sizeof(int), cmp);
    
    printf("%d\n", binary_search());
    
    return 0;
}