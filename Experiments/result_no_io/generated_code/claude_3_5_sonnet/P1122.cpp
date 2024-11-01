#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 16001
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* graph[MAX_N];
int beauty[MAX_N];
int dp[MAX_N];
int n;

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = v;
    newNode->next = graph[u];
    graph[u] = newNode;
}

int dfs(int u, int parent) {
    int sum = beauty[u];
    dp[u] = beauty[u];

    for (Node* v = graph[u]; v != NULL; v = v->next) {
        if (v->val != parent) {
            int childSum = dfs(v->val, u);
            sum += max(childSum, 0);
            dp[u] = max(dp[u], sum);
        }
    }

    return sum;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &beauty[i]);
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }

    dfs(1, 0);

    int maxSum = dp[1];
    for (int i = 2; i <= n; i++) {
        maxSum = max(maxSum, dp[i]);
    }

    printf("%d\n", maxSum);

    return 0;
}