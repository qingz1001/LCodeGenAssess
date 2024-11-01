#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long *holes = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &holes[i]);
    }

    long long min_sum = 0;
    for (int i = 0; i < m; i++) {
        if (i > 0) {
            min_sum += holes[i] - holes[i - 1];
        }
    }
    min_sum += holes[n - 1] - holes[m - 1];

    printf("%lld\n", min_sum);

    free(holes);
    return 0;
}