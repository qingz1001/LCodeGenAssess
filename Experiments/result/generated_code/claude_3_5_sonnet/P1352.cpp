#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 6001

int n;
int happiness[MAX_N];
int dp[MAX_N][2];
int visited[MAX_N];

struct Node {
    int val;
    struct Node* next;
};

struct Node* graph[MAX_N];

void addEdge(int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = v;
    newNode->next = graph[u];
    graph[u] = newNode;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void dfs(int u) {
    visited[u] = 1;
    dp[u][1] = happiness[u];
    dp[u][0] = 0;

    struct Node* curr = graph[u];
    while (curr) {
        int v = curr->val;
        if (!visited[v]) {
            dfs(v);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
        curr = curr->next;
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &happiness[i]);
    }

    for (int i = 1; i < n; i++) {
        int l, k;
        scanf("%d %d", &l, &k);
        addEdge(k, l);
    }

    memset(visited, 0, sizeof(visited));
    dfs(1);

    printf("%d\n", max(dp[1][0], dp[1][1]));

    return 0;
}