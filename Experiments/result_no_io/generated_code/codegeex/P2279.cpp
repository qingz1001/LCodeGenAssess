#include <stdio.h>

int n;
int tree[1001][2];

void addNode(int parent, int child) {
    if (tree[parent][0] == 0) {
        tree[parent][0] = child;
    } else {
        tree[parent][1] = child;
    }
}

void cover(int node, int depth) {
    if (depth > 2) return;
    int child1 = tree[node][0];
    int child2 = tree[node][1];
    if (child1 != 0) {
        cover(child1, depth + 1);
    }
    if (child2 != 0) {
        cover(child2, depth + 1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int parent;
        scanf("%d", &parent);
        addNode(i, parent);
        addNode(parent, i);
    }
    cover(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (tree[i][0] != 0 || tree[i][1] != 0) {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}