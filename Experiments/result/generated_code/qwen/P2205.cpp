#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_K 1000000000

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int positions[MAX_N + 2];
    for (int i = 0; i <= N + 1; i++) {
        positions[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        int distance;
        char direction[2];
        scanf("%d %s", &distance, direction);
        if (direction[0] == 'L') {
            positions[0]++;
            positions[-distance]--;
        } else {
            positions[0]++;
            positions[distance]--;
        }
    }

    int prefix_sum[MAX_N + 2];
    prefix_sum[0] = positions[0];
    for (int i = 1; i <= N + 1; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + positions[i];
    }

    int count = 0;
    for (int i = 0; i <= N + 1; i++) {
        if (prefix_sum[i] >= K) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}