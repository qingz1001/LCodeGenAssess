#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    long long *a = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += a[i];
    }
    if (total % n != 0) {
        printf("-1\n");
        free(a);
        return 0;
    }

    long long target = total / n;
    long long moves = 0;
    for (int i = 0; i < n; i++) {
        moves += abs(a[i] - target);
    }

    printf("%lld\n", moves / 2);

    free(a);
    return 0;
}