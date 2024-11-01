#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000000
#define MAX_M 1000

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *walls = (int *)calloc(N + 1, sizeof(int));
    for (int i = 0; i < M; ++i) {
        int A, B;
        scanf("%d %d", &A, &B);
        walls[A]++;
        walls[B + 1]--;
    }

    int count = 0, visible = 0;
    for (int i = 1; i <= N; ++i) {
        count += walls[i];
        if (count > 0) {
            visible++;
        }
    }

    printf("%d\n", visible);

    free(walls);
    return 0;
}