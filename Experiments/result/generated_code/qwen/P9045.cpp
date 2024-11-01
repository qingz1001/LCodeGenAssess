#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int cost = 0;
    int count = 0;

    for (int i = 0; i < n - 1; i++) {
        if (a[i] == a[i + 1]) {
            count++;
            if (count >= k) {
                cost += count - k + 1;
                count -= count - k + 1;
            }
        } else {
            count = 0;
        }
    }

    if (count >= k) {
        cost += count - k + 1;
    }

    if (cost > n * (n - 1) / 2) {
        printf("-1\n");
    } else {
        printf("%d\n", cost);
    }

    return 0;
}