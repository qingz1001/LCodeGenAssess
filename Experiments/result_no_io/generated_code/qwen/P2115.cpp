#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *m = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &m[i]);
    }

    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += m[i];
    }

    double min_avg = total_sum / (double)n;
    for (int i = 1; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            long long sum = 0;
            for (int k = 0; k < n; k++) {
                if (k < i || k >= j) {
                    sum += m[k];
                }
            }
            double avg = (double)sum / (n - (j - i));
            if (avg < min_avg) {
                min_avg = avg;
            }
        }
    }

    printf("%.3f\n", min_avg);

    free(m);
    return 0;
}