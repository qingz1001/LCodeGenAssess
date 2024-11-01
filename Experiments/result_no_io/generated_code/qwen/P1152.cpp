#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n == 1) {
        printf("Jolly\n");
        return 0;
    }

    int *diff = (int *)malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &diff[i]);
    }

    int max_diff = 0;
    for (int i = 0; i < n - 1; i++) {
        if (diff[i] < 0) diff[i] = -diff[i];
        if (diff[i] > n - 1) {
            free(diff);
            printf("Not jolly\n");
            return 0;
        }
        max_diff = (diff[i] > max_diff) ? diff[i] : max_diff;
    }

    int *visited = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        visited[diff[i]] = 1;
    }

    for (int i = 1; i <= max_diff; i++) {
        if (!visited[i]) {
            free(diff);
            free(visited);
            printf("Not jolly\n");
            return 0;
        }
    }

    free(diff);
    free(visited);
    printf("Jolly\n");

    return 0;
}