#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void find_sequence(int n, int sum) {
    int *seq = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        seq[i] = i + 1;
    }

    while (n > 1) {
        int new_sum = 0;
        for (int i = 0; i < n - 1; i++) {
            new_sum += seq[i];
        }
        if (new_sum != sum) {
            free(seq);
            printf("\n");
            return;
        }
        n--;
    }

    qsort(seq, n, sizeof(int), compare);
    for (int i = 0; i < n; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");

    free(seq);
}

int main() {
    int n, sum;
    scanf("%d %d", &n, &sum);
    find_sequence(n, sum);
    return 0;
}