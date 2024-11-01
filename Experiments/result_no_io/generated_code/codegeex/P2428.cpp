#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b, sum;
} Report;

int cmp(const void *a, const void *b) {
    Report *reportA = (Report *)a;
    Report *reportB = (Report *)b;
    return reportA->sum - reportB->sum;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Report *reports = (Report *)malloc(M * sizeof(Report));
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &reports[i].a, &reports[i].b, &reports[i].sum);
    }

    qsort(reports, M, sizeof(Report), cmp);

    double *debt = (double *)calloc(N + 1, sizeof(double));
    int *parent = (int *)calloc(N + 1, sizeof(int));
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    int a, b, sum;
    for (int i = 0; i < M; i++) {
        a = reports[i].a;
        b = reports[i].b;
        sum = reports[i].sum;

        int rootA = a;
        while (rootA != parent[rootA]) {
            rootA = parent[rootA];
        }

        int rootB = b;
        while (rootB != parent[rootB]) {
            rootB = parent[rootB];
        }

        if (rootA != rootB) {
            if (debt[rootA] == 0 && debt[rootB] == 0) {
                debt[rootA] = (double)sum / 2;
                debt[rootB] = (double)sum / 2;
            } else if (debt[rootA] == 0) {
                debt[rootA] = sum - debt[rootB];
            } else if (debt[rootB] == 0) {
                debt[rootB] = sum - debt[rootA];
            } else {
                printf("IMPOSSIBLE");
                return 0;
            }

            parent[rootB] = rootA;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (debt[i] == 0) {
            printf("IMPOSSIBLE");
            return 0;
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("%.2f\n", debt[i]);
    }

    free(reports);
    free(debt);
    free(parent);

    return 0;
}