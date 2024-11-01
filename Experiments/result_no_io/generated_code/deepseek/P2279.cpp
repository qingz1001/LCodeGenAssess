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
    dp[u][0] = 1; // 自己设立消防局
    dp[u][1] = 0; // 子节点设立消防局
    dp[u][2] = 0; // 孙子节点设立消防局

    int sum1 = 0, sum2 = 0;
    int min_diff = MAXN;

    for (Node* v = graph[u]; v != NULL; v = v->next) {
        if (visited[v->id]) continue;
        dfs(v->id);

        dp[u][0] += dp[v->id][2]; // 自己设立消防局，子节点可以是任何状态
        sum1 += dp[v->id][1]; // 子节点设立消防局
        sum2 += dp[v->id][2]; // 孙子节点设立消防局
    }

    dp[u][1] = sum2; // 子节点设立消防局
    dp[u][2] = sum1; // 孙子节点设立消防局

    for (Node* v = graph[u]; v != NULL; v = v->next) {
        if (visited[v->id]) continue;
        int diff = dp[v->id][0] - dp[v->id][1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    if (min_diff < MAXN) {
        dp[u][2] += min_diff;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {
        int a;
        scanf("%d", &a);
        addEdge(a, i);
        addEdge(i, a);
    }

    dfs(1);

    printf("%d\n", dp[1][2]);

    return 0;
}