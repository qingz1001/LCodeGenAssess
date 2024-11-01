#include <stdio.h>
#include <stdlib.h>

#define MAX_N 65
#define MAX_LEN 50

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int lengths[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    qsort(lengths, n, sizeof(int), compare);

    int dp[MAX_LEN + 1];
    for (int i = 0; i <= MAX_LEN; i++) {
        dp[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = MAX_LEN; j >= lengths[i]; j--) {
            dp[j] = min(dp[j], dp[j - lengths[i]] + lengths[i]);
        }
    }

    printf("%d\n", dp[MAX_LEN]);

    return 0;
}