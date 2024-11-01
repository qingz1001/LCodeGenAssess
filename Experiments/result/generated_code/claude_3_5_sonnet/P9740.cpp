#include <stdio.h>

#define MAX_N 7

int main() {
    int n, a[MAX_N], b[MAX_N], t;
    int current_score = 0;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i], &b[i]);
        current_score += (100 / a[i]) * b[i];
    }
    
    scanf("%d", &t);
    
    if (current_score >= t) {
        printf("Already Au.\n");
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        int score_per_point = 100 / a[i];
        int remaining_points = a[i] - b[i];
        int needed_score = t - current_score;
        int needed_points = (needed_score + score_per_point - 1) / score_per_point;
        
        if (needed_points <= remaining_points) {
            printf("%d\n", needed_points);
        } else {
            printf("NaN\n");
        }
    }
    
    return 0;
}