#include <stdio.h>
#include <math.h>

int main() {
    int n, a, b, t, score = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        score += b * 100 / a;
    }
    scanf("%d", &t);
    
    if (score >= t) {
        printf("Already Au.\n");
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        int remaining_score = t - score;
        int points_needed = remaining_score * a / 100 - b;
        if (points_needed > 0) {
            printf("%d\n", points_needed);
        } else {
            printf("NaN\n");
        }
    }
    
    return 0;
}