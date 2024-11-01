#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int *lights = (int *)calloc(N + 1, sizeof(int));
    for (int i = 0; i < M; i++) {
        int op, S, E;
        scanf("%d %d %d", &op, &S, &E);
        if (op == 0) {
            for (int j = S; j <= E; j++) {
                lights[j] = !lights[j];
            }
        } else if (op == 1) {
            int count = 0;
            for (int j = S; j <= E; j++) {
                if (lights[j]) {
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }
    free(lights);
    return 0;
}