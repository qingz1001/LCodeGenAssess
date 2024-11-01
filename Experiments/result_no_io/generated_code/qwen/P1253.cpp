#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

typedef struct {
    int type;
    int l, r, x;
} Operation;

int max(int a, int b) {
    return (a > b) ? a : b;
}

void update(int *tree, int n, int pos, int value) {
    while (pos <= n) {
        tree[pos] = max(tree[pos], value);
        pos += pos & -pos;
    }
}

int query(int *tree, int n, int pos) {
    int result = 0;
    while (pos > 0) {
        result = max(result, tree[pos]);
        pos -= pos & -pos;
    }
    return result;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        update(arr, n, i, arr[i]);
    }

    Operation *ops = (Operation *)malloc(q * sizeof(Operation));
    for (int i = 0; i < q; i++) {
        scanf("%d", &ops[i].type);
        if (ops[i].type == 1 || ops[i].type == 2) {
            scanf("%d %d %d", &ops[i].l, &ops[i].r, &ops[i].x);
        } else {
            scanf("%d %d", &ops[i].l, &ops[i].r);
        }
    }

    for (int i = 0; i < q; i++) {
        if (ops[i].type == 1) {
            for (int j = ops[i].l; j <= ops[i].r; j++) {
                update(arr, n, j, ops[i].x);
            }
        } else if (ops[i].type == 2) {
            for (int j = ops[i].l; j <= ops[i].r; j++) {
                update(arr, n, j, arr[j] + ops[i].x);
            }
        } else {
            printf("%d\n", query(arr, n, ops[i].r));
        }
    }

    free(arr);
    free(ops);
    return 0;
}