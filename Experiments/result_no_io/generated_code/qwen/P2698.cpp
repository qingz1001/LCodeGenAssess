#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_D 1000000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N, D;
    scanf("%d %d", &N, &D);

    int drops[MAX_N];
    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        drops[i] = x + y;
    }

    qsort(drops, N, sizeof(int), compare);

    int min_width = -1;
    for (int i = 0; i <= N - 2; i++) {
        if (drops[i + 1] - drops[i] >= D) {
            min_width = drops[i + 1] - drops[i] - D;
            break;
        }
    }

    printf("%d\n", min_width);
    return 0;
}