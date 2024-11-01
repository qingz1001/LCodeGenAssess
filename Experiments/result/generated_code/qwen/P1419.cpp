#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, S, T;
    scanf("%d %d", &n, &S);
    scanf("%d", &T);

    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    double max_avg = -1e9;
    for (int length = S; length <= T && length <= n; length++) {
        long long sum = 0;
        for (int i = 0; i < length; i++) {
            sum += a[i];
        }
        double avg = (double)sum / length;
        if (avg > max_avg) {
            max_avg = avg;
        }
        for (int i = length; i < n; i++) {
            sum += a[i] - a[i - length];
            avg = (double)sum / length;
            if (avg > max_avg) {
                max_avg = avg;
            }
        }
    }

    printf("%.3f\n", max_avg);

    free(a);
    return 0;
}