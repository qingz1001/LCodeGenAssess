#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);
    int citations[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &citations[i]);
    }

    qsort(citations, N, sizeof(int), compare);

    int h = 0;
    for (int i = 0; i < N; i++) {
        if (citations[i] >= i + 1) {
            h = i + 1;
        } else {
            break;
        }
    }

    if (L > 0) {
        for (int i = 0; i < N && L > 0; i++) {
            if (citations[i] < h) {
                int diff = h - citations[i];
                if (diff <= L) {
                    L -= diff;
                    citations[i] = h;
                } else {
                    citations[i] += L;
                    L = 0;
                }
            }
        }

        int new_h = 0;
        for (int i = 0; i < N; i++) {
            if (citations[i] >= i + 1) {
                new_h = i + 1;
            } else {
                break;
            }
        }
        h = new_h;
    }

    printf("%d\n", h);
    return 0;
}