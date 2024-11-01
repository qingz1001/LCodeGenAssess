#include <stdio.h>
#include <stdlib.h>

#define MAX_DISHES 200000
#define MAX_PEOPLE 50000

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m, p, q;
    scanf("%d %d %d %d", &n, &m, &p, &q);

    int dishes[MAX_DISHES][2];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &dishes[i][0], &dishes[i][1]);
    }

    int挑剔[MAX_PEOPLE];
    for (int i = 0; i < p; i++) {
        scanf("%d", &挑剔[i]);
    }

    int贫穷[MAX_PEOPLE];
    for (int i = 0; i < q; i++) {
        scanf("%d", &贫穷[i]);
    }

    qsort(dishes, m, sizeof(int) * 2, cmp);
    qsort(挑剔, p, sizeof(int), cmp);
    qsort(贫穷, q, sizeof(int), cmp);

    int count = 0;
    int j = 0;
    for (int i = 0; i < m; i++) {
        if (dishes[i][0] >=挑剔[j] && dishes[i][1] <=贫穷[j]) {
            count++;
            j++;
            if (j == p && j == q) {
                break;
            }
        }
    }

    if (count == 0) {
        printf("-1\n");
    } else {
        printf("%d\n", (p + q + count - 1) / count);
    }

    return 0;
}