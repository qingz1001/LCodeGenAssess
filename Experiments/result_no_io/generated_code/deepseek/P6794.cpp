#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXQ 200005
#define MAXH 1000000005

typedef struct {
    int type;
    int i;
    int x;
    int h;
} Operation;

int n, q;
int h[MAXN];
Operation ops[MAXQ];
int water[MAXN];
int results[MAXQ];

void apply_operation(int op_index) {
    Operation op = ops[op_index];
    if (op.type == 0) {
        int x = op.x;
        int h = op.h;
        while (x > 1 && water[x] < h && water[x] < water[x - 1]) {
            water[x] = water[x - 1];
            x--;
        }
        while (x < n && water[x] < h && water[x] < water[x + 1]) {
            water[x] = water[x + 1];
            x++;
        }
        for (int i = op.x; i <= n; i++) {
            if (water[i] < h) water[i] = h;
            else break;
        }
    } else if (op.type == 1) {
        water[op.x] = 0;
    } else if (op.type == 2) {
        h[op.x] = op.h;
    } else if (op.type == 3) {
        results[op_index] = water[op.x];
    }
}

void process_operations() {
    for (int i = 0; i < q; i++) {
        apply_operation(i);
    }
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i < n; i++) {
        scanf("%d", &h[i]);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d", &ops[i].type);
        if (ops[i].type == 0) {
            scanf("%d %d %d", &ops[i].i, &ops[i].x, &ops[i].h);
        } else if (ops[i].type == 1) {
            scanf("%d %d", &ops[i].i, &ops[i].x);
        } else if (ops[i].type == 2) {
            scanf("%d %d %d", &ops[i].i, &ops[i].x, &ops[i].h);
        } else if (ops[i].type == 3) {
            scanf("%d %d", &ops[i].i, &ops[i].x);
        }
    }

    process_operations();

    for (int i = 0; i < q; i++) {
        if (ops[i].type == 3) {
            printf("%d\n", results[i]);
        }
    }

    return 0;
}