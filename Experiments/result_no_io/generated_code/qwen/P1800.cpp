#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int **times = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        times[i] = (int *)malloc(2 * sizeof(int));
        scanf("%d %d", &times[i][0], &times[i][1]);
    }

    int max_time = 0;
    for (int i = 0; i < n; i++) {
        int total_time = 0;
        for (int j = 0; j < m; j++) {
            if (j % 2 == 0) {
                total_time += times[i][0];
            } else {
                total_time += times[i][1];
            }
        }
        if (total_time > max_time) {
            max_time = total_time;
        }
    }

    printf("%d\n", max_time);

    for (int i = 0; i < n; i++) {
        free(times[i]);
    }
    free(times);

    return 0;
}