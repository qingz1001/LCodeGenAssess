#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXQ 200005

typedef struct {
    int type; // 0: fill water, 1: drain water, 2: increase barrier, 3: query
    int i;
    int x;
    int h;
} Operation;

int n, q;
int barriers[MAXN];
int water_levels[MAXN];
Operation operations[MAXQ];

void fill_water(int x, int h) {
    if (water_levels[x] >= h) return;
    water_levels[x] = h;
}

void drain_water(int x) {
    water_levels[x] = 0;
}

void increase_barrier(int x, int h) {
    barriers[x] = h;
}

int query_water_level(int x) {
    return water_levels[x];
}

void process_operations() {
    for (int i = 0; i < q; i++) {
        Operation op = operations[i];
        if (op.type == 0) {
            fill_water(op.x, op.h);
        } else if (op.type == 1) {
            drain_water(op.x);
        } else if (op.type == 2) {
            increase_barrier(op.x, op.h);
        } else if (op.type == 3) {
            printf("%d\n", query_water_level(op.x));
        }
    }
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i < n; i++) {
        scanf("%d", &barriers[i]);
    }
    for (int i = 0; i < q; i++) {
        int type, idx, x, h;
        scanf("%d", &type);
        if (type == 0) {
            scanf("%d %d %d", &idx, &x, &h);
            operations[i] = (Operation){0, idx, x, h};
        } else if (type == 1) {
            scanf("%d %d", &idx, &x);
            operations[i] = (Operation){1, idx, x, 0};
        } else if (type == 2) {
            scanf("%d %d %d", &idx, &x, &h);
            operations[i] = (Operation){2, idx, x, h};
        } else if (type == 3) {
            scanf("%d %d", &idx, &x);
            operations[i] = (Operation){3, idx, x, 0};
        }
    }

    process_operations();

    return 0;
}