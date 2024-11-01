#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, t;
    scanf("%d", &n);
    int a[n], b[n];
    int total_score = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i], &b[i]);
        total_score += b[i] * (100 / a[i]);
    }

    scanf("%d", &t);

    if (total_score >= t) {
        printf("Already Au.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int required_score = t - total_score + b[i] * (100 / a[i]);
        int required_points = (required_score + (100 / a[i]) - 1) / (100 / a[i]) - b[i];

        if (required_points <= a[i] - b[i]) {
            printf("%d\n", required_points);
        } else {
            printf("NaN\n");
        }
    }

    return 0;
}