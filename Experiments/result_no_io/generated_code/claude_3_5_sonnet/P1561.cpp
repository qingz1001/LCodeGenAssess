#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    int U[MAX_N], D[MAX_N];
    int i, total_time = 0, down_time = 0;

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d %d", &U[i], &D[i]);
        total_time += U[i];
    }

    qsort(D, N, sizeof(int), compare);

    for (i = 0; i < N; i++) {
        if (down_time < total_time) {
            down_time += D[i];
        } else {
            down_time = total_time + D[i];
        }
    }

    printf("%d\n", down_time);

    return 0;
}