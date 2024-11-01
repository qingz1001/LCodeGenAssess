#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000000
#define MAX_C 100000
#define MAX_Q 200000

typedef struct {
    int length;
    int count;
} Ship;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, c, q;
        scanf("%d %d %d", &n, &c, &q);
        
        Ship ships[MAX_C];
        for (int i = 0; i < c; i++) {
            scanf("%d %d", &ships[i].length, &ships[i].count);
        }
        
        int attacks[MAX_Q];
        for (int i = 0; i < q; i++) {
            scanf("%d", &attacks[i]);
        }
        
        // Check if it's impossible to place all ships
        int total_length = 0;
        for (int i = 0; i < c; i++) {
            total_length += ships[i].length * ships[i].count;
        }
        if (total_length > n) {
            printf("0\n");
            continue;
        }
        
        // Try placing the ships and check for contradictions
        int placed[MAX_N] = {0};
        int pos = 0;
        for (int i = 0; i < c; i++) {
            for (int j = 0; j < ships[i].count; j++) {
                for (int k = 0; k < ships[i].length; k++) {
                    if (pos + k >= n || placed[pos + k]) {
                        printf("-1\n");
                        goto next_test_case;
                    }
                    placed[pos + k] = 1;
                }
                pos++;
            }
        }
        
        // Check each attack
        for (int i = 0; i < q; i++) {
            if (!placed[attacks[i]]) {
                printf("%d\n", i + 1);
                goto next_test_case;
            }
        }
        
        printf("-1\n");
next_test_case:;
    }
    return 0;
}