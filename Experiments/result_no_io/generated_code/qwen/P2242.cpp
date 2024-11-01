#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long *holes = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &holes[i]);
    }

    long long min_length = 0;
    for (int i = 0; i < m; i++) {
        long long start, end;
        scanf("%lld %lld", &start, &end);
        if (i == 0) {
            min_length += holes[end - 1] - holes[start - 1];
        } else {
            min_length += holes[end - 1] - holes[start - 1];
        }
    }

    printf("%lld\n", min_length);

    free(holes);
    return 0;
}