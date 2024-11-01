#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_N 53280
#define MAX_M 150960

typedef struct {
    int u, v;
    uint32_t w;
} Tunnel;

int n, m, x;
Tunnel tunnels[MAX_M];

int __builtin_popcount(uint32_t x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

int main() {
    int W;
    scanf("%d", &W);
    scanf("%d %d %d", &n, &m, &x);

    for (int i = 0; i < n; i++) {
        int x_i, y_i;
        scanf("%d %d", &x_i, &y_i);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %u", &tunnels[i].u, &tunnels[i].v, &tunnels[i].w);
    }

    // Simple heuristic: increase the energy of the first tunnel to exceed x
    int k = 0;
    uint32_t new_w = x + 1;
    int cost = __builtin_popcount(new_w);

    printf("%d\n", 1);
    printf("%d %d %u\n", tunnels[0].u, tunnels[0].v, new_w);

    return 0;
}