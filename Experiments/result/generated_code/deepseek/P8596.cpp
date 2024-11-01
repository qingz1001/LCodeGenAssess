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
        int x, y;
        scanf("%d %d", &x, &y);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %u", &tunnels[i].u, &tunnels[i].v, &tunnels[i].w);
    }

    // 简单策略：增加第一条隧道的能量，使其超过x
    uint32_t additional_energy = x + 1 - tunnels[0].w;
    if (additional_energy > 0) {
        printf("1\n");
        printf("%d %d %u\n", tunnels[0].u, tunnels[0].v, additional_energy);
    } else {
        printf("0\n");
    }

    return 0;
}