#include <stdio.h>
#include <limits.h>

int main() {
    int n, S, T;
    scanf("%d", &n);
    scanf("%d %d", &S, &T);

    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    double max_avg = INT_MIN;

    for (int len = S; len <= T; len++) {
        double sum = 0;
        for (int i = 0; i < len; i++) {
            sum += a[i];
        }
        if (sum / len > max_avg) {
            max_avg = sum / len;
        }

        for (int i = len; i < n; i++) {
            sum += a[i] - a[i - len];
            if (sum / len > max_avg) {
                max_avg = sum / len;
            }
        }
    }

    printf("%.3f\n", max_avg);

    return 0;
}