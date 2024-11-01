#include <stdio.h>
#include <stdlib.h>

#define MAX_L 10000
#define MAX_M 100

int main() {
    int l, m;
    scanf("%d %d", &l, &m);

    int *tree = (int *)calloc(l + 1, sizeof(int));
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        for (int j = u; j <= v; ++j) {
            tree[j] = 1;
        }
    }

    int remaining_trees = 0;
    for (int i = 0; i <= l; ++i) {
        if (!tree[i]) {
            ++remaining_trees;
        }
    }

    printf("%d\n", remaining_trees);

    free(tree);
    return 0;
}