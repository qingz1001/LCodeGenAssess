#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000001

int main() {
    int n;
    scanf("%d", &n);

    int *recorded = (int *)calloc(MAXN, sizeof(int));
    long long total_time = 0;

    for (int i = 0; i < n; ++i) {
        int x, t;
        scanf("%d %d", &x, &t);
        if (t > 1 && !recorded[x]) {
            total_time += t;
            recorded[x] = 1;
        }
    }

    printf("%lld\n", total_time);

    free(recorded);
    return 0;
}