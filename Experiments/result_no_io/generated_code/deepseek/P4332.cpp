#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int n;
int input[MAXN * 3 + 1];
int tree[MAXN][3];
int output[MAXN];

void dfs(int node) {
    if (node > n) {
        output[node] = input[node];
        return;
    }
    dfs(tree[node][0]);
    dfs(tree[node][1]);
    dfs(tree[node][2]);
    int count1 = output[tree[node][0]] + output[tree[node][1]] + output[tree[node][2]];
    output[node] = (count1 >= 2) ? 1 : 0;
}

void update(int node) {
    while (node > 0) {
        int count1 = output[tree[node][0]] + output[tree[node][1]] + output[tree[node][2]];
        int new_output = (count1 >= 2) ? 1 : 0;
        if (output[node] == new_output) break;
        output[node] = new_output;
        node /= 3;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &tree[i][0], &tree[i][1], &tree[i][2]);
    }
    for (int i = 1; i <= 2 * n + 1; i++) {
        scanf("%d", &input[n + i]);
    }

    dfs(1);

    int q;
    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        input[n + x] ^= 1;
        update(n + x);
        printf("%d\n", output[1]);
    }

    return 0;
}