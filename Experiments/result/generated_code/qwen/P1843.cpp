#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500005

int n, a, b;
int w[MAX_N];

int compare(const void *x, const void *y) {
    return (*(int*)x - *(int*)y);
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    qsort(w, n, sizeof(int), compare);

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (w[i] > a + b) {
            time += (w[i] - (a + b) + b - 1) / b;
        }
    }

    printf("%d\n", time);

    return 0;
}