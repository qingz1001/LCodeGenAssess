#include <stdio.h>
#include <stdbool.h>

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
        
        int attacks[MAX_Q];
        for (int i = 0; i < q; i++) {
            scanf("%d", &attacks[i]);
        }
        
        bool possible = true;
        for (int i = 0; i < q; i++) {
            if (attacks[i] < total_length) {
                printf("%d\n", i + 1);
                possible = false;
                break;
            }
        }
        
        if (possible) {
            printf("-1\n");
        }
    }
    return 0;
}