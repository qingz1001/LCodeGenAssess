#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int t, n;
    scanf("%d %d", &t, &n);
    
    int *x = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }
    
    qsort(x, n, sizeof(int), cmp);
    
    int max = 0;
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int timeLeft = abs(x[left]) * 2;
        int timeRight = abs(x[right]) * 2;
        
        if (timeLeft <= t && timeRight <= t) {
            max = (left + 1 + right + 1 > max) ? (left + 1 + right + 1) : max;
            left++;
            right--;
        } else if (timeLeft <= t) {
            left++;
        } else {
            right--;
        }
    }
    
    printf("%d\n", max);
    
    free(x);
    return 0;
}