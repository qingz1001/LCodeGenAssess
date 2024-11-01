#include <stdio.h>

#define MAX_N 7

int main() {
    int n, ai[MAX_N], bi[MAX_N], t;
    int total_score = 0;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ai[i], &bi[i]);
        total_score += (100 / ai[i]) * bi[i];
    }
    
    scanf("%d", &t);
    
    if (total_score >= t) {
        printf("Already Au.\n");
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        int needed = t - total_score;
        int points_per_test = 100 / ai[i];
        int remaining_tests = ai[i] - bi[i];
        int tests_needed = (needed + points_per_test - 1) / points_per_test;
        
        if (tests_needed <= remaining_tests) {
            printf("%d\n", tests_needed);
        } else {
            printf("NaN\n");
        }
    }
    
    return 0;
}