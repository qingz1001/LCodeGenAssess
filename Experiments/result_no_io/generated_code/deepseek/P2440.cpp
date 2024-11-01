#include <stdio.h>
#include <stdlib.h>

int canCut(int *lengths, int n, int k, int l) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += lengths[i] / l;
        if (count >= k) return 1;
    }
    return 0;
}

int maxLength(int *lengths, int n, int k) {
    int left = 1, right = 1e8;
    int max_l = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canCut(lengths, n, k, mid)) {
            max_l = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return max_l;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int *lengths = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    int result = maxLength(lengths, n, k);
    printf("%d\n", result);

    free(lengths);
    return 0;
}