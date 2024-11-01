#include <stdio.h>
#include <stdlib.h>

#define N 5
#define K 10

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

void find_best_split(int times[N][K], int distances[], int total_time) {
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            for (int k = 1; k <= 10; k++) {
                for (int l = 1; l <= 10; l++) {
                    for (int m = 1; m <= 10; m++) {
                        if (i + j + k + l + m == 25) {
                            int current_time = times[0][i-1] + times[1][j-1] + times[2][k-1] + times[3][l-1] + times[4][m-1];
                            if (current_time < total_time) {
                                total_time = current_time;
                                distances[0] = i;
                                distances[1] = j;
                                distances[2] = k;
                                distances[3] = l;
                                distances[4] = m;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int times[N][K];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            scanf("%d", &times[i][j]);
        }
    }

    int distances[N];
    int total_time = INT_MAX;

    find_best_split(times, distances, total_time);

    printf("%d\n", total_time);
    for (int i = 0; i < N; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");

    return 0;
}