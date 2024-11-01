#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort and bsearch
int cmp(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    if (int_a < int_b)
        return -1;
    else if (int_a > int_b)
        return 1;
    else
        return 0;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int *A = NULL, *B = NULL;
    if (n > 0) {
        A = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) {
            if(scanf("%d", &A[i]) != 1){
                free(A);
                return 0;
            }
        }
    }

    if (m > 0) {
        B = (int*)malloc(m * sizeof(int));
        for(int i = 0; i < m; i++) {
            if(scanf("%d", &B[i]) != 1){
                free(A);
                free(B);
                return 0;
            }
        }
        qsort(B, m, sizeof(int), cmp);
    }

    int first = 1;
    for(int i = 0; i < n; i++) {
        if (m > 0 && bsearch(&A[i], B, m, sizeof(int), cmp) != NULL) {
            if (!first) {
                printf(" ");
            }
            printf("%d", A[i]);
            first = 0;
        }
    }
    printf("\n");

    free(A);
    free(B);
    return 0;
}