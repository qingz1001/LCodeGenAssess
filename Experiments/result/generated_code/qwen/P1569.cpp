#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int groups = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (sum < 0) {
            printf("Impossible\n");
            return 0;
        } else if (sum == 0) {
            groups++;
            sum = 0;
        }
    }

    if (groups > 0) {
        printf("%d\n", groups);
    } else {
        printf("Impossible\n");
    }

    return 0;
}