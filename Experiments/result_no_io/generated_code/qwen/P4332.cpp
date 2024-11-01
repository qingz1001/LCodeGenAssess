#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int n, m, q;
int tree[MAXN][3];
int inputs[MAXN];
int root_output;

void update(int i) {
    int count[2] = {0};
    for (int j = 0; j < 3; j++) {
        if (tree[i][j] <= n) {
            count[inputs[tree[i][j]]]++;
        } else {
            count[inputs[tree[i][j] - n - 1]]++;
        }
    }
    inputs[i] = count[0] > count[1] ? 0 : 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &tree[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &inputs[i]);
    }
    scanf("%d", &q);

    // Initialize root output
    root_output = inputs[1];

    for (int i = 0; i < q; i++) {
        int idx;
        scanf("%d", &idx);
        inputs[idx + n + 1] = !inputs[idx + n + 1]; // Change input
        update(idx + n + 1); // Update the cell and propagate changes up the tree
        while (idx != 1) {
            idx = tree[idx][0]; // Move to the parent cell
            update(idx); // Update the parent cell
        }
        printf("%d\n", inputs[1]); // Output the new root output
    }

    return 0;
}