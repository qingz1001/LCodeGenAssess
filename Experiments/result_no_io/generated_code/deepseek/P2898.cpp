#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXQ 25000

typedef struct {
    int l, r, x;
} Query;

Query queries[MAXQ];
int min_value[MAXN];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &queries[i].l, &queries[i].r, &queries[i].x);
        queries[i].l--;
        queries[i].r--;
    }

    for (int i = 0; i < n; i++) {
        min_value[i] = 1000000001; // Initialize to a value larger than any possible x
    }

    for (int i = 0; i < q; i++) {
        for (int j = queries[i].l; j <= queries[i].r; j++) {
            if (min_value[j] == 1000000001) {
                min_value[j] = queries[i].x;
            } else if (min_value[j] != queries[i].x) {
                printf("%d\n", i + 1);
                return 0;
            }
        }
    }

    printf("0\n");
    return 0;
}