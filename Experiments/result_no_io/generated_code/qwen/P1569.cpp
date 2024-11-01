#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    scanf("%d", &n);
    long long a[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    long long sum = 0;
    int groups = 0;
    bool possible = true;

    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (sum < 0) {
            if (possible) {
                possible = false;
                groups++;
                sum = a[i];
            } else {
                printf("Impossible\n");
                return 0;
            }
        }
    }

    if (sum >= 0) {
        groups++;
    } else {
        printf("Impossible\n");
        return 0;
    }

    printf("%d\n", groups);
    return 0;
}