#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);
    int citations[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &citations[i]);
    }

    qsort(citations, N, sizeof(int), cmp);

    int h = 0;
    while (h < N && citations[h] > h) {
        h++;
    }

    int max_h = h;
    int used_references = 0;
    for (int i = h; i < N && used_references < L; i++) {
        if (citations[i] >= max_h + 1) {
            max_h++;
            used_references++;
        }
    }

    printf("%d\n", max_h);
    return 0;
}