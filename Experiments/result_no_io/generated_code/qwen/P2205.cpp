#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_MOVE 1000000000

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int *positions = (int *)calloc(MAX_MOVE + 1, sizeof(int));
    int max_pos = 0;

    for (int i = 0; i < N; i++) {
        char direction[2];
        int distance;
        scanf("%d %s", &distance, direction);
        if (direction[0] == 'L') {
            positions[max_pos - distance]++;
        } else {
            positions[max_pos + distance]++;
        }
        max_pos += distance;
    }

    int count = 0;
    for (int i = 0; i <= max_pos; i++) {
        if (positions[i] >= K) {
            count++;
        }
    }

    printf("%d\n", count);

    free(positions);
    return 0;
}