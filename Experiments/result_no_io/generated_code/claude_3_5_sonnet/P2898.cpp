#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 1000001
#define MAX_Q 25001

int min_val[MAX_N];
int max_val[MAX_N];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; i++) {
        min_val[i] = 1;
        max_val[i] = INT_MAX;
    }

    for (int i = 1; i <= q; i++) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);

        int current_min = INT_MAX;
        for (int j = l; j <= r; j++) {
            if (min_val[j] > x) {
                min_val[j] = x;
            }
            if (max_val[j] < x) {
                printf("%d\n", i);
                return 0;
            }
            if (min_val[j] > current_min) {
                printf("%d\n", i);
                return 0;
            }
            current_min = min_val[j];
        }

        for (int j = l; j <= r; j++) {
            if (max_val[j] > x) {
                max_val[j] = x;
            }
        }
    }

    printf("0\n");
    return 0;
}