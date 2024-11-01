#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long scores[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &scores[i]);
    }

    // Sort the scores
    qsort(scores, n, sizeof(long long), (void *)cmp);

    // Calculate initial sum without highest and lowest scores
    long long total_sum = 0;
    for (int i = 1; i < n - 1; ++i) {
        total_sum += scores[i];
    }

    // Try to maximize the final score by increasing the lowest scores
    for (int i = 0; i < m && i < n - 2; ++i) {
        if (scores[i] < scores[i + 1]) {
            total_sum += 1;
        }
    }

    printf("%lld\n", total_sum * (n - 2));
    return 0;
}

// Comparator function for qsort
int cmp(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}