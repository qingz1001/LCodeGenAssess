#include <stdio.h>
#include <stdlib.h>

void solve(int n, int sums[], int result[]) {
    int total_sums = n * (n - 1) / 2;
    int sum_of_all = 0;
    for (int i = 0; i < total_sums; i++) {
        sum_of_all += sums[i];
    }
    sum_of_all /= (n - 1);

    for (int i = 1; i < n; i++) {
        result[i] = (sums[i - 1] - sums[i]) / 2;
    }
    result[0] = sum_of_all - result[1];

    // Check if the solution is valid
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int sum = result[i] + result[j];
            int found = 0;
            for (int k = 0; k < total_sums; k++) {
                if (sums[k] == sum) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Impossible\n");
                return;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int total_sums = n * (n - 1) / 2;
        int *sums = (int *)malloc(total_sums * sizeof(int));
        int *result = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < total_sums; i++) {
            scanf("%d", &sums[i]);
        }

        solve(n, sums, result);

        free(sums);
        free(result);
    }
    return 0;
}