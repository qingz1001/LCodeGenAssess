#include <stdio.h>
#include <stdlib.h>

#define MAXN 16000
#define INF 2147483647

int n;
int beauty[MAXN];
int tree[MAXN][2];

int max(int a, int b) {
    return (a > b) ? a : b;
}

void dfs(int node, int parent, int *sum) {
    if (tree[node][0] == -1 && tree[node][1] == -1) {
        *sum += beauty[node];
        return;
    }
    int sum1 = 0, sum2 = 0;
    if (tree[node][0] != -1) dfs(tree[node][0], node, &sum1);
    if (tree[node][1] != -1) dfs(tree[node][1], node, &sum2);
    *sum += max(sum1, sum2);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &beauty[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        tree[a - 1][0] = b - 1;
        tree[b - 1][1] = a - 1;
    }
    int result = -INF;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        dfs(i, -1, &sum);
        result = max(result, sum);
    }
    printf("%d\n", result);
    return 0;
}