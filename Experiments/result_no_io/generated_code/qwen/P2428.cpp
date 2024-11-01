#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 100000

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    double debt[MAX_N] = {0.0};
    int reported[MAX_N][MAX_N] = {0};

    for (int i = 0; i < M; ++i) {
        int a, b, sum;
        scanf("%d %d %d", &a, &b, &sum);
        --a; --b;

        if (reported[a][b]) {
            printf("IMPOSSIBLE\n");
            return 0;
        }

        debt[a] += sum / 2.0;
        debt[b] -= sum / 2.0;
        reported[a][b] = 1;
    }

    for (int i = 0; i < N; ++i) {
        printf("%.2f\n", debt[i]);
    }

    return 0;
}