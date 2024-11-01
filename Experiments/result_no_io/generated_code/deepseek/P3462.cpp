#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_M 100000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    int containers[MAX_N];
    int weights[MAX_M];
    int i, j;
    int count = 0;

    scanf("%d %d", &n, &m);

    for (i = 0; i < n; i++) {
        scanf("%d", &containers[i]);
    }

    for (i = 0; i < m; i++) {
        scanf("%d", &weights[i]);
    }

    qsort(containers, n, sizeof(int), compare);
    qsort(weights, m, sizeof(int), compare);

    j = 0;
    for (i = 0; i < m; i++) {
        while (j < n && containers[j] < weights[i]) {
            j++;
        }
        if (j < n) {
            count++;
            j++;
        } else {
            break;
        }
    }

    printf("%d\n", count);

    return 0;
}