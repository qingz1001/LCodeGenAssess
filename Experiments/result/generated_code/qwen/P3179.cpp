#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000000

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < k; i++) {
        int w;
        scanf("%d", &w);
        int *white = (int *)malloc(w * sizeof(int));
        for (int j = 0; j < w; j++) {
            scanf("%d", &white[j]);
        }

        // Check if there is a winning strategy
        int has_winning_strategy = 0;
        for (int j = 0; j < w; j++) {
            int x = white[j];
            int max_k = n / x;
            int can_win = 0;
            for (int m = 1; m <= max_k; m++) {
                int flip_count = 0;
                for (int p = 1; p * x <= n; p++) {
                    if (p * x == x * m) {
                        flip_count++;
                    }
                }
                if (flip_count % 2 != 0) {
                    can_win = 1;
                    break;
                }
            }
            if (!can_win) {
                has_winning_strategy = 1;
                break;
            }
        }

        if (has_winning_strategy) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

        free(white);
    }

    return 0;
}