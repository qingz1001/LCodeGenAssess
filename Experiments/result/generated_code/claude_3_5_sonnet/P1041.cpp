#include <stdio.h>
#include <stdlib.h>

#define MAX_N 301

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* graph[MAX_N];
int visited[MAX_N];
int n, p;

void add_edge(int u, int v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->id = v;
    new_node->next = graph[u];
    graph[u] = new_node;
}

int dfs(int u) {
    int max_subtree = 0;
    int total = 1;
    visited[u] = 1;

    for (Node* v = graph[u]; v != NULL; v = v->next) {
        if (!visited[v->id]) {
            int subtree_size = dfs(v->id);
            if (subtree_size > max_subtree) {
                max_subtree = subtree_size;
            }
            total += subtree_size;
        }
    }

    return (max_subtree > total - max_subtree) ? max_subtree : total - max_subtree;
}

int main() {
    scanf("%d %d", &n, &p);

    for (int i = 0; i < p; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    int infected = dfs(1);
    printf("%d\n", infected);

    return 0;
}