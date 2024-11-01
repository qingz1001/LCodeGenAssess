#include <stdio.h>
#include <stdlib.h>

#define MAX_N 9

void findZeroSumSequences(int n, int current[], int pos) {
    if (pos == n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += current[i];
        }
        if (sum == 0) {
            for (int i = 0; i < n - 1; i++) {
                printf("%d", current[i]);
                if (i % 2 == 0 && i != n - 2) {
                    printf(" ");
                } else {
                    printf("%c", (current[i + 1] > current[i]) ? '+' : '-');
                }
            }
            printf("%d\n", current[n - 1]);
        }
        return;
    }

    current[pos] = pos + 1;
    findZeroSumSequences(n, current, pos + 1);
}

int main() {
    int n;
    scanf("%d", &n);

    int *current = (int *)malloc(n * sizeof(int));
    if (current == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    findZeroSumSequences(n, current, 0);

    free(current);
    return 0;
}