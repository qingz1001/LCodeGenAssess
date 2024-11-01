#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *w = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    int *time = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int min_index = 0;
        for (int j = 1; j < m; j++) {
            if (time[j] < time[min_index]) {
                min_index = j;
            }
        }
        time[min_index] += w[i];
    }

    int max_time = 0;
    for (int i = 0; i < m; i++) {
        if (time[i] > max_time) {
            max_time = time[i];
        }
    }

    printf("%d\n", max_time);

    free(w);
    free(time);
    return 0;
}