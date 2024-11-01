#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, t;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }

    scanf("%d", &t);

    int total_score = 0;
    for (int i = 0; i < n; i++) {
        total_score += b[i] * 100 / a[i];
    }

    if (total_score >= t) {
        printf("Already Au.\n");
        free(a);
        free(b);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int needed_points = ((t - total_score + b[i] * 100 / a[i]) * a[i] / 100 - b[i]);
        if (needed_points > 0 && needed_points <= a[i] - b[i]) {
            printf("%d\n", needed_points);
        } else {
            printf("NaN\n");
        }
    }

    free(a);
    free(b);
    return 0;
}