#include <stdio.h>

#define MAX_N 3000

int main() {
    int n, m;
    int a[MAX_N];
    int sum = 0, min_sum;

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Calculate initial sum of first m elements
    for (int i = 0; i < m; i++) {
        sum += a[i];
    }
    min_sum = sum;

    // Sliding window approach
    for (int i = m; i < n; i++) {
        sum = sum - a[i-m] + a[i];
        if (sum < min_sum) {
            min_sum = sum;
        }
    }

    printf("%d\n", min_sum);

    return 0;
}