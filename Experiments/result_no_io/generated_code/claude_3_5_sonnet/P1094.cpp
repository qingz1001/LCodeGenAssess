#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int w, n;
    scanf("%d", &w);
    scanf("%d", &n);

    int prices[30000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    qsort(prices, n, sizeof(int), compare);

    int left = 0, right = n - 1;
    int groups = 0;

    while (left <= right) {
        if (left == right) {
            groups++;
            break;
        }
        if (prices[left] + prices[right] <= w) {
            left++;
            right--;
        } else {
            left++;
        }
        groups++;
    }

    printf("%d\n", groups);

    return 0;
}