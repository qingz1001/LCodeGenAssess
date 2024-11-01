#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((long long)a[i] * a[j] <= k) {
                count++;
            }
        }
    }

    printf("%lld\n", count);

    return 0;
}