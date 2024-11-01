#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct {
    int min;
    int max;
} Range;

int main() {
    int n;
    scanf("%d", &n);
    Range ranges[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ranges[i].min, &ranges[i].max);
    }

    int groups = 0;
    long long ways = 1;
    int start = 0;

    for (int end = 0; end < n; end++) {
        if (end == n - 1 || ranges[end + 1].min > ranges[end].max) {
            int length = end - start + 1;
            if (length < ranges[start].min || length > ranges[end].max) {
                printf("NIE\n");
                return 0;
            }
            groups++;
            if (groups > 1) {
                ways = (ways * (end - start + 1)) % MOD;
            }
            start = end + 1;
        }
    }

    printf("%d %lld\n", groups, ways);
    return 0;
}