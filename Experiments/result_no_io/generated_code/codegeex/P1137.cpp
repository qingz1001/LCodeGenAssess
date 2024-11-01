#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList;

AdjList* CreateGraph(int n) {
    AdjList* graph = (AdjList*)malloc(sizeof(AdjList) * (n + 1));
    for (int i = 1; i <= n; i++) {
        graph[i].head = NULL;
    }
    return graph;
}

void AddEdge(AdjList* graph, int x, int y) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = y;
    newNode->next = graph[x].head;
    graph[x].head = newNode;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    AdjList* graph = CreateGraph(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        AddEdge(graph, x, y);
    }

    int* dist = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }

    int* queue = (int*)malloc(sizeof(int) * (n + 1));
    int front = 0, rear = 0;

    // Initialize the queue with all vertices
    for (int i = 1; i <= n; i++) {
        queue[rear++] = i;
        dist[i] = 1;
    }

    while (front < rear) {
        int u = queue[front++];
        Node* p = graph[u].head;
        while (p != NULL) {
            int v = p->vertex;
            if (dist[v] == -1) {
                queue[rear++] = v;
                dist[v] = dist[u] + 1;
            }
            p = p->next;
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", dist[i]);
    }

    free(dist);
    free(queue);
    for (int i = 1; i <= n; i++) {
        Node* p = graph[i].head;
        while (p != NULL) {
            Node* temp = p;
            p = p->next;
            free(temp);
        }
    }
    free(graph);

    return 0;
}