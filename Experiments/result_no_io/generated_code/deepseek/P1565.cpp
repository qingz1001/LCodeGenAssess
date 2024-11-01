#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int **a = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        a[i] = (int *)malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int max_area = 0;

    for (int i = 0; i < N; i++) {
        int *sum = (int *)calloc(M, sizeof(int));
        for (int j = i; j < N; j++) {
            for (int k = 0; k < M; k++) {
                sum[k] += a[j][k];
            }

            int current_sum = 0;
            int start = 0;
            for (int k = 0; k < M; k++) {
                current_sum += sum[k];
                while (current_sum < 0 && start <= k) {
                    current_sum -= sum[start];
                    start++;
                }
                if (start <= k) {
                    max_area = MAX(max_area, (j - i + 1) * (k - start + 1));
                }
            }
        }
        free(sum);
    }

    for (int i = 0; i < N; i++) {
        free(a[i]);
    }
    free(a);

    printf("%d\n", max_area);
    return 0;
}