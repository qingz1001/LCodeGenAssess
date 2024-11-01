#include <stdio.h>
#include <stdlib.h>

#define MAXN 305

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* graph[MAXN];
int visited[MAXN];
int infected[MAXN];
int n, p;

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = v;
    newNode->next = graph[u];
    graph[u] = newNode;
}

void dfs(int u) {
    visited[u] = 1;
    Node* curr = graph[u];
    while (curr != NULL) {
        int v = curr->id;
        if (!visited[v]) {
            dfs(v);
        }
        curr = curr->next;
    }
}

int main() {
    scanf("%d %d", &n, &p);
    for (int i = 0; i < p; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    int totalInfected = 0;
    infected[1] = 1;

    for (int i = 1; i <= n; i++) {
        if (infected[i]) {
            totalInfected++;
            dfs(i);
        }
    }

    printf("%d\n", totalInfected);

    for (int i = 1; i <= n; i++) {
        Node* curr = graph[i];
        while (curr != NULL) {
            Node* next = curr->next;
            free(curr);
            curr = next;
        }
    }

    return 0;
}