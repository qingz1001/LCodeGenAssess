#include <stdio.h>
#include <stdlib.h>

int main() {
    int v, n, c;
    scanf("%d %d %d", &v, &n, &c);

    if (c < n) {
        printf("Impossible\n");
        return 0;
    }

    int *volumes = (int *)malloc(n * sizeof(int));
    int *costs = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &volumes[i], &costs[i]);
        if (costs[i] > c) {
            printf("Impossible\n");
            free(volumes);
            free(costs);
            return 0;
        }
        c -= costs[i];
        v -= volumes[i];
    }

    printf("%d\n", c);

    free(volumes);
    free(costs);

    return 0;
}