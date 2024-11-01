#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, S, T;
    scanf("%d", &n);
    scanf("%d %d", &S, &T);

    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    double max_avg = -1e9;
    for (int len = S; len <= T; len++) {
        long long sum = 0;
        for (int i = 0; i < len; i++) {
            sum += a[i];
        }
        double avg = (double)sum / len;
        if (avg > max_avg) {
            max_avg = avg;
        }
        for (int i = len; i < n; i++) {
            sum += a[i] - a[i - len];
            avg = (double)sum / len;
            if (avg > max_avg) {
                max_avg = avg;
            }
        }
    }

    printf("%.3f\n", max_avg);

    free(a);
    return 0;
}