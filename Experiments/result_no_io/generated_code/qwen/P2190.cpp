#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long total = 0;

    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if (x > y) {
            y += n;
        }
        total += (long long)(y - x) * z;
    }

    printf("%lld\n", (total + 35) / 36);

    return 0;
}