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

    int min_range = N;

    // Try all possible assignments
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < B; j++) {
            if (assignments[preferences[i][j] - 1] == -1 && capacities[j] > 0) {
                assignments[preferences[i][j] - 1] = i + 1;
                capacities[j]--;
                break;
            }
        }
    }

    for (int i = 0; i < B; i++) {
        if (capacities[i] != 0) {
            printf("Error: Barn %d has remaining capacity.\n", i + 1);
            return 1;
        }
    }

    for (int i = 0; i < B; i++) {
        int max_rank = 0;
        int min_rank = N + 1;
        for (int j = 0; j < N; j++) {
            if (assignments[j] == i + 1) {
                if (preferences[j][0] < min_rank) {
                    min_rank = preferences[j][0];
                }
                if (preferences[j][B-1] > max_rank) {
                    max_rank = preferences[j][B-1];
                }
            }
        }
        int range = max_rank - min_rank + 1;
        if (range < min_range) {
            min_range = range;
        }
    }

    printf("%d\n", min_range);

    return 0;
}