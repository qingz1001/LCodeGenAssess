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

        int total_length = 0;
        for (int i = 0; i < c; i++) {
            total_length += ships[i].length * ships[i].count;
        }

        if (total_length > n) {
            printf("0\n");
            continue;
        }

        int ans = -1;
        for (int i = 0; i < q; i++) {
            int attacked = attacks[i];
            int placed = 0;
            for (int j = 0; j < c; j++) {
                if (attacked >= 1 && attacked <= ships[j].length) {
                    placed++;
                    break;
                }
                attacked -= ships[j].length;
            }
            if (placed == 0) {
                ans = i + 1;
                break;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}