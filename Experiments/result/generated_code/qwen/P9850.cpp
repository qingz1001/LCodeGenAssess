#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int degree[MAXN] = {0};
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        degree[u]++;
        degree[v]++;
    }

    long long blue_keys = 0, red_keys = 0;

    for (int i = 1; i <= n; ++i) {
        if (degree[i] >= 3) {
            blue_keys += (long long)(degree[i]) * (degree[i] - 1) / 2;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 3) {
            red_keys++;
        }
    }

    printf("%lld\n", abs(blue_keys - red_keys));

    return 0;
}