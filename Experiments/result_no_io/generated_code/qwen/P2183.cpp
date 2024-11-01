#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int P, n, m;
    scanf("%d %d", &P, &n);
    scanf("%d", &m);

    if (n < m) {
        printf("Impossible\n");
        return 0;
    }

    long long result = 1;
    for (int i = 0; i < m; ++i) {
        int w;
        scanf("%d", &w);
        result = (result * w) % P;
    }

    printf("%lld\n", result);
    return 0;
}