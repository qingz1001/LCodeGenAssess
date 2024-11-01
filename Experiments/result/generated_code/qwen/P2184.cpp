#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *prefix = (int *)calloc(n + 1, sizeof(int));
    int *count = (int *)calloc(n + 1, sizeof(int));

    for (int i = 0; i < m; ++i) {
        int q, l, r;
        scanf("%d %d %d", &q, &l, &r);
        if (q == 1) {
            prefix[r] ^= 1 << (l - 1);
        } else {
            count[r] += prefix[r];
            if (l > 1) {
                count[r] -= prefix[l - 1];
            }
            printf("%d\n", count[r]);
        }
    }

    free(prefix);
    free(count);

    return 0;
}