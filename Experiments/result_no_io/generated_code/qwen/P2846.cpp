#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *lights = (int *)calloc(N + 1, sizeof(int));
    int *prefix_sum = (int *)calloc(N + 1, sizeof(int));

    for (int i = 1; i <= M; i++) {
        int op, S, E;
        scanf("%d %d %d", &op, &S, &E);
        if (op == 0) {
            prefix_sum[S]++;
            if (E + 1 <= N) {
                prefix_sum[E + 1]--;
            }
        } else if (op == 1) {
            int count = prefix_sum[E];
            if (S > 1) {
                count -= prefix_sum[S - 1];
            }
            printf("%d\n", count);
        }
    }

    free(lights);
    free(prefix_sum);

    return 0;
}