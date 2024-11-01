#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* graph[MAXN];
int visited[MAXN];
int dp[MAXN][3];

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = v;
    newNode->next = graph[u];
    graph[u] = newNode;
}

void dfs(int u) {
    visited[u] = 1;
    dp[u][0] = 1; // 当前节点设立消防局
    dp[u][1] = 0; // 当前节点不设立消防局，但至少有一个子节点设立消防局
    dp[u][2] = 0; // 当前节点不设立消防局，且所有子节点都不设立消防局

    int sum = 0, min_diff = MAXN;
    Node* v = graph[u];
    while (v != NULL) {
        if (!visited[v->id]) {
            dfs(v->id);
            dp[u][0] += dp[v->id][2];
            dp[u][1] += dp[v->id][1];
            dp[u][2] += dp[v->id][1];
            sum += dp[v->id][1];
            min_diff = (min_diff < dp[v->id][0] - dp[v->id][1]) ? min_diff : (dp[v->id][0] - dp[v->id][1]);
        }
        v = v->next;
    }

    if (min_diff < MAXN) {
        dp[u][1] = sum + min_diff;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {
        int a;
        scanf("%d", &a);
        addEdge(a, i);
    }

    dfs(1);

    printf("%d\n", dp[1][1]);

    return 0;
}