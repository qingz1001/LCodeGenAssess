#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int capacities[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &capacities[i]);
    }

    int requests[MAX_N][2];
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &requests[i][0], &requests[i][1]);
    }

    int max_satisfied = 0;

    for (int i = 0; i < M; i++) {
        int start = requests[i][0] - 1;
        int end = requests[i][1] - 1;
        int total_capacity = 0;

        for (int j = start; j <= end; j++) {
            total_capacity += capacities[j];
        }

        if (total_capacity >= (end - start + 1)) {
            max_satisfied++;
        }
    }

    printf("%d\n", max_satisfied);

    return 0;
}