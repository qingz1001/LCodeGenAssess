#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

long long trees[MAX_N];

int compare(const void *a, const void *b) {
    return (*(long long*)b - *(long long*)a);
}

long long calculate_wood(long long height, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        if (trees[i] > height) {
            sum += trees[i] - height;
        } else {
            break;
        }
    }
    return sum;
}

long long binary_search(int n, long long m) {
    long long left = 0, right = trees[0], mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        long long wood = calculate_wood(mid, n);
        if (wood == m) return mid;
        if (wood > m) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}

int main() {
    int n;
    long long m;
    scanf("%d %lld", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &trees[i]);
    }

    qsort(trees, n, sizeof(long long), compare);

    long long result = binary_search(n, m);
    printf("%lld\n", result);

    return 0;
}