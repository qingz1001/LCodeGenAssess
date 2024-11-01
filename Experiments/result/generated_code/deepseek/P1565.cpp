#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int a[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int max_area = 0;

    for (int i = 0; i < N; i++) {
        int sum[M];
        for (int j = 0; j < M; j++) {
            sum[j] = 0;
        }

        for (int k = i; k < N; k++) {
            for (int j = 0; j < M; j++) {
                sum[j] += a[k][j];
            }

            int current_sum = 0;
            int min_sum = 0;
            int current_length = 0;

            for (int j = 0; j < M; j++) {
                current_sum += sum[j];
                current_length++;

                if (current_sum - min_sum > 0) {
                    max_area = MAX(max_area, current_length * (k - i + 1));
                }

                min_sum = MIN(min_sum, current_sum);
            }
        }
    }

    printf("%d\n", max_area);
    return 0;
}