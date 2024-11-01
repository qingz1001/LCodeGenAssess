#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 16000

typedef struct Node {
    int val;
    int max_sum;
    struct Node* next;
} Node;

Node* adj[MAXN + 1];
int beauty[MAXN + 1];
int visited[MAXN + 1];
int dp[MAXN + 1][2];

void add_edge(int u, int v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = v;
    new_node->next = adj[u];
    adj[u] = new_node;
}

void dfs(int u) {
    visited[u] = 1;
    dp[u][0] = 0;
    dp[u][1] = beauty[u];

    for (Node* v = adj[u]; v != NULL; v = v->next) {
        if (!visited[v->val]) {
            dfs(v->val);
            dp[u][0] += dp[v->val][1];
            dp[u][1] += dp[v->val][0];
        }
    }

    if (dp[u][0] < dp[u][1]) {
        dp[u][0] = dp[u][1];
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &beauty[i]);
        adj[i] = NULL;
        visited[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }

    dfs(1);

    int max_beauty = INT_MIN;
    for (int i = 1; i <= n; i++) {
        if (dp[i][0] > max_beauty) {
            max_beauty = dp[i][0];
        }
    }

    printf("%d\n", max_beauty);

    for (int i = 1; i <= n; i++) {
        Node* curr = adj[i];
        while (curr != NULL) {
            Node* next = curr->next;
            free(curr);
            curr = next;
        }
    }

    return 0;
}