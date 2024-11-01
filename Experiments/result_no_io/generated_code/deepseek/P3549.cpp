#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 500005

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* adj[MAXN];
bool visited[MAXN];
int parent[MAXN];
int path[MAXN];
int path_len;

void add_edge(int u, int v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->id = v;
    new_node->next = adj[u];
    adj[u] = new_node;

    new_node = (Node*)malloc(sizeof(Node));
    new_node->id = u;
    new_node->next = adj[v];
    adj[v] = new_node;
}

void dfs(int u, int p) {
    visited[u] = true;
    parent[u] = p;
    Node* curr = adj[u];
    while (curr != NULL) {
        if (!visited[curr->id]) {
            dfs(curr->id, u);
        }
        curr = curr->next;
    }
}

void find_path(int u) {
    path[path_len++] = u;
    Node* curr = adj[u];
    while (curr != NULL) {
        if (curr->id != parent[u] && !visited[curr->id]) {
            visited[curr->id] = true;
            find_path(curr->id);
            path[path_len++] = u;
        }
        curr = curr->next;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    dfs(1, -1);

    if (!visited[n]) {
        printf("BRAK\n");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        visited[i] = false;
    }

    find_path(1);

    if (path[path_len - 1] != n) {
        printf("BRAK\n");
        return 0;
    }

    for (int i = 0; i < path_len; i++) {
        printf("%d\n", path[i]);
    }

    return 0;
}