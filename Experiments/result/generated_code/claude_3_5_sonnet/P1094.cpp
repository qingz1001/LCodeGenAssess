#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30000

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int w, n, prices[MAX_N];
    int left = 0, right, groups = 0;

    scanf("%d", &w);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    qsort(prices, n, sizeof(int), compare);

    right = n - 1;

    while (left <= right) {
        if (left == right) {
            groups++;
            break;
        }
        
        if (prices[left] + prices[right] <= w) {
            left++;
            right--;
            groups++;
        } else {
            left++;
            groups++;
        }
    }

    printf("%d\n", groups);

    return 0;
}