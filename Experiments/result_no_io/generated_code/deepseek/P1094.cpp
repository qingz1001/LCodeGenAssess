#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int w, n;
    scanf("%d", &w);
    scanf("%d", &n);
    
    int *prices = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }
    
    qsort(prices, n, sizeof(int), compare);
    
    int left = 0, right = n - 1;
    int groups = 0;
    
    while (left <= right) {
        if (prices[left] + prices[right] <= w) {
            left++;
        }
        right--;
        groups++;
    }
    
    printf("%d\n", groups);
    
    free(prices);
    return 0;
}