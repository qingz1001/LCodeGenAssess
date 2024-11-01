#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

long long max_diff(long long *arr, int n, int m) {
    long long max_val = arr[0], min_val = arr[0];
    
    for (int i = 1; i < n; i++) {
        max_val = MAX(max_val, arr[i]);
        min_val = MIN(min_val, arr[i]);
    }
    
    for (int i = 0; i < m; i++) {
        long long new_max = max_val;
        new_max = MAX(new_max, max_val + 2);
        new_max = MAX(new_max, max_val * 2);
        max_val = new_max;
        
        long long new_min = min_val;
        new_min = MIN(new_min, min_val - 2);
        new_min = MIN(new_min, min_val / 2);
        min_val = new_min;
    }
    
    return max_val - min_val;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    long long *arr = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    
    long long result = max_diff(arr, n, m);
    printf("%lld\n", result);
    
    free(arr);
    return 0;
}