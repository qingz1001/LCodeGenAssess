#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int main() {
    int n, i;
    long long a[MAX_N + 1], sum = 0;
    int count = 0;

    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    for (i = 1; i <= n; i++) {
        sum += a[i];
        if (sum >= 0) {
            count++;
            sum = 0;
        }
    }

    if (sum < 0) {
        printf("Impossible\n");
    } else {
        printf("%d\n", count);
    }

    return 0;
}