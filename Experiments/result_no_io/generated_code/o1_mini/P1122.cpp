#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Edge* edges;
} Node;

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Node* nodes;
int* visited;
long long max_sum = -2147483648;

void add_edge(int from, int to) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->next = nodes[from].edges;
    nodes[from].edges = edge;
}

long long dfs(int u) {
    visited[u] = 1;
    long long current_sum = nodes[u].value;
    Edge* edge = nodes[u].edges;
    while (edge != NULL) {
        int v = edge->to;
        if (!visited[v]) {
            long long child_sum = dfs(v);
            if (child_sum > 0) {
                current_sum += child_sum;
            }
        }
        edge = edge->next;
    }
    if (current_sum > max_sum) {
        max_sum = current_sum;
    }
    return current_sum;
}

int main(){
    int N;
    scanf("%d", &N);
    nodes = (Node*)malloc((N+1) * sizeof(Node));
    for(int i=1;i<=N;i++) {
        scanf("%d", &nodes[i].value);
        nodes[i].edges = NULL;
    }
    for(int i=1;i<N;i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    visited = (int*)calloc(N+1, sizeof(int));
    dfs(1);
    printf("%lld", max_sum);
    // Free memory
    for(int i=1;i<=N;i++) {
        Edge* edge = nodes[i].edges;
        while(edge != NULL){
            Edge* tmp = edge;
            edge = edge->next;
            free(tmp);
        }
    }
    free(nodes);
    free(visited);
    return 0;
}