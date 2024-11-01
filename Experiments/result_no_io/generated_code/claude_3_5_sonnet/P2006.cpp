#include <stdio.h>
#include <stdlib.h>

#define MAX_SKILLS 30000

int main() {
    int k, m, n;
    int a[MAX_SKILLS], b[MAX_SKILLS];
    int valid_skills[MAX_SKILLS], valid_count = 0;
    
    scanf("%d %d %d", &k, &m, &n);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a[i], &b[i]);
        
        // Check if the skill can be used and is effective
        if (a[i] <= k && b[i] > 0) {
            int casts = k / a[i];
            long long total_damage = (long long)casts * b[i];
            
            if (total_damage >= n) {
                valid_skills[valid_count++] = i + 1;
            }
        }
    }
    
    if (valid_count == 0) {
        printf("-1\n");
    } else {
        for (int i = 0; i < valid_count; i++) {
            printf("%d", valid_skills[i]);
            if (i < valid_count - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    return 0;
}