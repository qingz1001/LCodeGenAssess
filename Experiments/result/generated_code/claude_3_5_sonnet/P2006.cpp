#include <stdio.h>
#include <stdlib.h>

#define MAX_SKILLS 30000

int main() {
    int k, m, n;
    scanf("%d %d %d", &k, &m, &n);

    int a[MAX_SKILLS], b[MAX_SKILLS];
    int valid_skills[MAX_SKILLS], valid_count = 0;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a[i], &b[i]);
        if (a[i] <= k && b[i] > 0) {
            valid_skills[valid_count++] = i + 1;
        }
    }

    if (valid_count == 0) {
        printf("-1\n");
        return 0;
    }

    for (int i = 0; i < valid_count; i++) {
        int skill = valid_skills[i] - 1;
        long long casts = (n + b[skill] - 1) / b[skill];
        long long total_mana = (long long)a[skill] * casts;
        
        if (total_mana <= k) {
            printf("%d", valid_skills[i]);
            for (int j = i + 1; j < valid_count; j++) {
                skill = valid_skills[j] - 1;
                casts = (n + b[skill] - 1) / b[skill];
                total_mana = (long long)a[skill] * casts;
                
                if (total_mana <= k) {
                    printf(" %d", valid_skills[j]);
                }
            }
            printf("\n");
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}