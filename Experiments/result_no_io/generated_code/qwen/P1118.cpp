#include <stdio.h>
#include <stdlib.h>

#define MAX_N 13

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void find_sequence(int n, int sum, int *sequence) {
    if (n == 1) {
        if (sum == 1) {
            for (int i = 0; i < n; i++) {
                printf("%d ", i + 1);
            }
            printf("\n");
        }
        return;
    }

    for (int i = 1; i <= n; i++) {
        sequence[n - 1] = i;
        int new_sum = 0;
        for (int j = 0; j < n - 1; j++) {
            new_sum += sequence[j];
        }
        if (new_sum == sum) {
            find_sequence(n - 1, sum - i, sequence);
        } else if (new_sum > sum) {
            break;
        }
    }
}

int main() {
    int n, sum;
    scanf("%d %d", &n, &sum);

    int *sequence = (int *)malloc(n * sizeof(int));
    qsort(sequence, n, sizeof(int), compare);

    find_sequence(n, sum, sequence);

    free(sequence);
    return 0;
}