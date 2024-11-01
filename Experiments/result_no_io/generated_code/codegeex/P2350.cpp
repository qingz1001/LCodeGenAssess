#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main() {
    int test, m;
    scanf("%d", &test);
    while (test--) {
        scanf("%d", &m);
        ll min_steps = 0;
        for (int i = 0; i < m; i++) {
            ll p, q;
            scanf("%lld %lld", &p, &q);
            min_steps += (q + 1) * (p - 1);
        }
        printf("%lld\n", min_steps);
    }
    return 0;
}