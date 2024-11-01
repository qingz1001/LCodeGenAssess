#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

typedef struct {
    int children[3];
} Node;

Node tree[MAXN];
int inputs[MAXN * 3 + 1];
int n, q;

void update(int index) {
    while (index > 0) {
        tree[index].children[inputs[index]]++;
        index -= index & -index;
    }
}

int query(int index) {
    int count = 0;
    while (index <= n * 3) {
        if (tree[index].children[0] > count) count = tree[index].children[0];
        if (tree[index].children[1] > count) count = tree[index].children[1];
        index += index & -index;
    }
    return count == tree[index].children[2];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &tree[i].children[j]);
        }
    }
    for (int i = n + 1; i <= n * 3; i++) {
        scanf("%d", &inputs[i]);
    }
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        inputs[x] ^= 1;
        update(x);
        printf("%d\n", query(1));
    }

    return 0;
}