#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_B 20

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);

    int preferences[MAX_N][MAX_B];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < B; j++) {
            scanf("%d", &preferences[i][j]);
        }
    }

    int capacities[MAX_B];
    for (int i = 0; i < B; i++) {
        scanf("%d", &capacities[i]);
    }

    int assignments[MAX_N];
    for (int i = 0; i < N; i++) {
        assignments[i] = -1;
    }

    int result = 1000000;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < B; j++) {
            int barn = preferences[i][j];
            if (assignments[barn - 1] != -1) continue;

            int rank = j + 1;
            int low_rank = 1000000;
            int high_rank = 0;

            for (int k = 0; k < N; k++) {
                if (assignments[preferences[k][j] - 1] == -1) {
                    assignments[preferences[k][j] - 1] = rank;
                    low_rank = rank;
                    high_rank = rank;
                    break;
                } else {
                    low_rank = fmin(low_rank, assignments[preferences[k][j] - 1]);
                    high_rank = fmax(high_rank, assignments[preferences[k][j] - 1]);
                }
            }

            if (high_rank - low_rank + 1 < result && high_rank - low_rank + 1 <= capacities[barn - 1]) {
                result = high_rank - low_rank + 1;
            }

            for (int k = 0; k < N; k++) {
                if (assignments[preferences[k][j] - 1] == rank) {
                    assignments[preferences[k][j] - 1] = -1;
                    break;
                }
            }
        }
    }

    printf("%d\n", result);

    return 0;
}