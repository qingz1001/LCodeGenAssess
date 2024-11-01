#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 16001
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* graph[MAX_N];
int beauty[MAX_N];
int dp[MAX_N];
int n;

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = v;
    newNode->next = graph[u];
    graph[u] = newNode;
}

int dfs(int u, int parent) {
    int sum = beauty[u];
    for (Node* v = graph[u]; v != NULL; v = v->next) {
        if (v->value != parent) {
            int childSum = dfs(v->value, u);
            if (childSum > 0) {
                sum += childSum;
            }
        }
    }
    dp[u] = sum;
    return sum;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &beauty[i]);
    }
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    
    dfs(1, 0);
    
    int maxSum = dp[1];
    for (int i = 2; i <= n; i++) {
        maxSum = MAX(maxSum, dp[i]);
    }
    
    printf("%d\n", maxSum);
    
    return 0;
}