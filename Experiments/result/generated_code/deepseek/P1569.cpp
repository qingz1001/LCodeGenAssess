#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int count = 0;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (sum < 0) {
            printf("Impossible\n");
            free(a);
            return 0;
        }
        if (sum == 0) {
            count++;
        }
    }

    if (sum != 0) {
        printf("Impossible\n");
    } else {
        printf("%d\n", count);
    }

    free(a);
    return 0;
}