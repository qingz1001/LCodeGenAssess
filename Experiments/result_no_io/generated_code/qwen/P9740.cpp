#include <stdio.h>
#include <math.h>

int main() {
    int n, t;
    scanf("%d", &n);
    int current_score = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        current_score += b * 100 / a;
    }
    scanf("%d", &t);

    if (current_score >= t) {
        printf("Already Au.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        int remaining_points = a - b;
        int points_needed = t - current_score + b * 100 / a;
        if (points_needed <= remaining_points * 100 / a) {
            printf("%d\n", points_needed * a / 100);
        } else {
            printf("NaN\n");
        }
    }

    return 0;
}