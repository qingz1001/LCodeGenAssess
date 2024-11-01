#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);
    int *c = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }

    qsort(c, N, sizeof(int), compare);

    int h = 0;
    for (int i = 0; i < N; i++) {
        if (c[i] >= h + 1) {
            h++;
        } else {
            break;
        }
    }

    if (L > 0) {
        for (int i = 0; i < N && L > 0; i++) {
            if (c[i] < h + 1) {
                int diff = h + 1 - c[i];
                if (L >= diff) {
                    L -= diff;
                    c[i] = h + 1;
                } else {
                    c[i] += L;
                    L = 0;
                }
            }
        }

        qsort(c, N, sizeof(int), compare);

        h = 0;
        for (int i = 0; i < N; i++) {
            if (c[i] >= h + 1) {
                h++;
            } else {
                break;
            }
        }
    }

    printf("%d\n", h);

    free(c);
    return 0;
}