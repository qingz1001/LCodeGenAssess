#include <stdio.h>
#include <limits.h>

#define MAXN 100001

int n, S, T;
int a[MAXN];

int main() {
    scanf("%d", &n);
    scanf("%d%d", &S, &T);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    double max_average = INT_MIN;
    for (int i = S; i <= T; i++) {
        double current_sum = 0;
        for (int j = 1; j <= n - i + 1; j++) {
            for (int k = j; k < j + i; k++) {
                current_sum += a[k];
            }
            double current_average = current_sum / i;
            if (current_average > max_average) {
                max_average = current_average;
            }
        }
    }

    printf("%.3lf\n", max_average);
    return 0;
}