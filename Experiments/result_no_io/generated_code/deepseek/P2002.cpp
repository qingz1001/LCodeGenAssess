#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005

typedef struct {
    int to;
    struct Node* next;
} Node;

Node* graph[MAXN];
bool visited[MAXN];
bool inStack[MAXN];
int low[MAXN];
int disc[MAXN];
int stack[MAXN];
int scc[MAXN];
int time, top, sccCount;

void addEdge(int from, int to) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->to = to;
    newNode->next = graph[from];
    graph[from] = newNode;
}

void tarjan(int u) {
    low[u] = disc[u] = ++time;
    stack[++top] = u;
    inStack[u] = true;
    visited[u] = true;

    for (Node* v = graph[u]; v != NULL; v = v->next) {
        if (!visited[v->to]) {
            tarjan(v->to);
            low[u] = low[u] < low[v->to] ? low[u] : low[v->to];
        } else if (inStack[v->to]) {
            low[u] = low[u] < disc[v->to] ? low[u] : disc[v->to];
        }
    }

    if (low[u] == disc[u]) {
        ++sccCount;
        int v;
        do {
            v = stack[top--];
            inStack[v] = false;
            scc[v] = sccCount;
        } while (v != u);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int b, e;
        scanf("%d %d", &b, &e);
        addEdge(b, e);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    bool* inDegree = (bool*)calloc(sccCount + 1, sizeof(bool));
    for (int u = 1; u <= n; ++u) {
        for (Node* v = graph[u]; v != NULL; v = v->next) {
            if (scc[u] != scc[v->to]) {
                inDegree[scc[v->to]] = true;
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= sccCount; ++i) {
        if (!inDegree[i]) {
            ++result;
        }
    }

    printf("%d\n", result);

    for (int i = 1; i <= n; ++i) {
        Node* temp = graph[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }

    free(inDegree);
    return 0;
}