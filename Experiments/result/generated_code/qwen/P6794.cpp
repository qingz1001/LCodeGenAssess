#include <stdio.h>
#include <stdlib.h>

#define MAXN 200010
#define MAXQ 200010

int n, q;
int heights[MAXN];
int water_levels[MAXN][MAXQ];

void init(int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }
}

void query(int i, int x) {
    printf("%d\n", water_levels[x][i]);
}

void add_water(int i, int x, int h) {
    if (water_levels[x][i] >= h) return;
    water_levels[x][i] = h;
    for (int j = x + 1; j < n; j++) {
        if (water_levels[j][i] > heights[j - 1]) {
            break;
        }
        water_levels[j][i] = heights[j - 1];
    }
}

void drain_water(int i, int x) {
    while (water_levels[x][i] > 0 && water_levels[x][i] <= heights[x - 1]) {
        water_levels[x][i]--;
    }
}

void increase_barrier(int i, int x, int h) {
    if (heights[x - 1] >= h) return;
    heights[x - 1] = h;
    for (int j = x; j < n; j++) {
        if (water_levels[j][i] > heights[j - 1]) {
            break;
        }
        water_levels[j][i] = heights[j - 1];
    }
}

int main() {
    scanf("%d %d", &n, &q);
    init(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            water_levels[i][j] = 0;
        }
    }

    for (int i = 0; i < q; i++) {
        int op, x, y;
        scanf("%d", &op);
        switch (op) {
            case 0:
                scanf("%d %d %d", &x, &y, &y);
                add_water(i, x, y);
                break;
            case 1:
                scanf("%d %d", &x, &y);
                drain_water(i, x);
                break;
            case 2:
                scanf("%d %d %d", &x, &y, &y);
                increase_barrier(i, x, y);
                break;
            case 3:
                scanf("%d %d", &x, &y);
                query(i, x);
                break;
        }
    }

    return 0;
}