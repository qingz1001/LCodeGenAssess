#include <stdio.h>
#include <stdlib.h>

#define MOD 10000

typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Graph;

Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(n * sizeof(Graph));
    for (int i = 0; i < n; i++) {
        graph[i].head = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = graph[src].head;
    graph[src].head = newNode;
}

int dfs(Graph* graph, int node, int* visited, int* pathCount, int* pathWeight) {
    if (visited[node]) {
        return 0;
    }
    visited[node] = 1;
    int count = 0;
    int weight = 0;
    Node* temp = graph[node].head;
    while (temp != NULL) {
        count += dfs(graph, temp->dest, visited, pathCount, pathWeight);
        weight = (weight + temp->weight * pathCount[temp->dest]) % MOD;
        temp = temp->next;
    }
    pathCount[node] = count + 1;
    pathWeight[node] = weight;
    return count + 1;
}

int main() {
    int n, m, s, t, t0;
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);

    Graph* graph = createGraph(n);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        addEdge(graph, x - 1, y - 1, z);
    }

    int* visited = (int*)calloc(n, sizeof(int));
    int* pathCount = (int*)calloc(n, sizeof(int));
    int* pathWeight = (int*)calloc(n, sizeof(int));

    dfs(graph, s - 1, visited, pathCount, pathWeight);

    int totalWeight = (pathWeight[t - 1] + (pathCount[t - 1] - 1) * t0) % MOD;
    printf("%d\n", totalWeight);

    free(graph);
    free(visited);
    free(pathCount);
    free(pathWeight);

    return 0;
}