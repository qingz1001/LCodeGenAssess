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

    int total_time = 0;
    int next_student = m;

    while (next_student < n) {
        int min_time = time[0];
        for (int i = 1; i < m; i++) {
            if (time[i] < min_time) {
                min_time = time[i];
            }
        }

        total_time += min_time;

        for (int i = 0; i < m; i++) {
            time[i] -= min_time;
            if (time[i] == 0 && next_student < n) {
                time[i] = w[next_student];
                next_student++;
            }
        }
    }

    int max_remaining_time = 0;
    for (int i = 0; i < m; i++) {
        if (time[i] > max_remaining_time) {
            max_remaining_time = time[i];
        }
    }

    total_time += max_remaining_time;

    printf("%d\n", total_time);

    free(w);
    free(time);
    return 0;
}