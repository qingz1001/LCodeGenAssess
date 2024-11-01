#include <stdio.h>
#include <stdlib.h>

void solve(int n, int sums[]) {
    int total_sums = n * (n - 1) / 2;
    int *result = (int *)malloc(n * sizeof(int));
    int i, j, k;

    // Initialize the result array with zeros
    for (i = 0; i < n; i++) {
        result[i] = 0;
    }

    // Start with the smallest number
    result[0] = 0;
    for (i = 1; i < n; i++) {
        result[i] = sums[0] - result[0];
        for (j = 1; j < i; j++) {
            result[i] -= result[j];
        }
    }

    // Check if the result is valid
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            int sum = 0;
            for (k = 0; k < n; k++) {
                if (k != i && k != j) {
                    sum += result[k];
                }
            }
            if (sum != sums[i * (n - 1) + j - (i + 1) * (i + 2) / 2]) {
                printf("Impossible\n");
                free(result);
                return;
            }
        }
    }

    // Print the result
    for (i = 0; i < n; i++) {
        printf("%d", result[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(result);
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int total_sums = n * (n - 1) / 2;
        int *sums = (int *)malloc(total_sums * sizeof(int));
        int i;

        for (i = 0; i < total_sums; i++) {
            scanf("%d", &sums[i]);
        }

        solve(n, sums);

        free(sums);
    }

    return 0;
}