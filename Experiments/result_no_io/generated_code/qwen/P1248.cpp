#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);

    int A[MAX_N], B[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    qsort(A, n, sizeof(int), compare);
    qsort(B, n, sizeof(int), compare);

    int total_time = 0;
    int max_time = 0;

    for (int i = 0; i < n; i++) {
        max_time = (max_time > A[i] + B[i]) ? max_time : A[i] + B[i];
        total_time += A[i];
    }

    printf("%d\n", max_time);

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", i + 1);
    }
    printf("\n");

    return 0;
}