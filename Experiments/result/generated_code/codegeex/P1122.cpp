#include <stdio.h>
#include <stdlib.h>

#define MAXN 16001

int n;
int a[MAXN];
int dp[MAXN];

typedef struct Node {
    int v;
    struct Node *next;
} Node;

Node *head[MAXN];

void addEdge(int u, int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->v = v;
    newNode->next = head[u];
    head[u] = newNode;
}

int max(int x, int y) {
    return x > y ? x : y;
}

int dfs(int u, int parent) {
    dp[u] = a[u];
    for (Node *cur = head[u]; cur != NULL; cur = cur->next) {
        int v = cur->v;
        if (v != parent) {
            dp[u] += dfs(v, u);
        }
    }
    return dp[u];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, -1);
    int ans = a[1];
    for (int i = 2; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}