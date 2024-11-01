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
        int needed_score = t - total_score;
        int points_needed = (needed_score + (100 / a[i]) - 1) / (100 / a[i]);
        
        if (b[i] + points_needed > a[i]) {
            printf("NaN\n");
        } else {
            printf("%d\n", points_needed);
        }
    }
    
    return 0;
}