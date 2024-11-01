#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000000
#define MAX_C 100000
#define MAX_Q 200000

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, c, q;
        scanf("%d %d %d", &n, &c, &q);
        
        long long total_length = 0;
        for (int i = 0; i < c; i++) {
            int ci, ti;
            scanf("%d %d", &ci, &ti);
            total_length += (long long)ci * ti;
        }
        
        if (total_length > n) {
            printf("0\n");
            continue;
        }
        
        int *attacks = (int *)malloc(q * sizeof(int));
        for (int i = 0; i < q; i++) {
            scanf("%d", &attacks[i]);
        }
        
        int *occupied = (int *)calloc(n, sizeof(int));
        int current_position = 0;
        
        for (int i = 0; i < c; i++) {
            int ci, ti;
            scanf("%d %d", &ci, &ti);
            for (int j = 0; j < ti; j++) {
                for (int k = 0; k < ci; k++) {
                    occupied[current_position + k] = 1;
                }
                current_position += ci;
            }
        }
        
        int lie_detected = 0;
        for (int i = 0; i < q; i++) {
            if (occupied[attacks[i] - 1] == 1) {
                lie_detected = i + 1;
                break;
            }
        }
        
        if (lie_detected > 0) {
            printf("%d\n", lie_detected);
        } else {
            printf("-1\n");
        }
        
        free(attacks);
        free(occupied);
    }
    return 0;
}