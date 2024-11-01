#include <stdio.h>
#include <limits.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int min_sum = INT_MAX;
    for (int i = 0; i <= n - m; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += a[i + j];
        }
        if (sum < min_sum) {
            min_sum = sum;
        }
    }

    printf("%d\n", min_sum);
    return 0;
}