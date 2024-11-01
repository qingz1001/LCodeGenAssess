#include <stdio.h>
#include <stdlib.h>

#define MAXN 105

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    int state, threshold;
    int in_degree;
    Edge edges[MAXN];
    int edge_count;
} Node;

Node nodes[MAXN];
int n, p;

void topological_sort() {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (nodes[i].in_degree == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int current = queue[front++];
        if (nodes[current].state > 0) {
            for (int i = 0; i < nodes[current].edge_count; i++) {
                int to = nodes[current].edges[i].to;
                int weight = nodes[current].edges[i].weight;
                nodes[to].state += weight * nodes[current].state;
                if (--nodes[to].in_degree == 0) {
                    queue[rear++] = to;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &nodes[i].state, &nodes[i].threshold);
        nodes[i].in_degree = 0;
        nodes[i].edge_count = 0;
    }

    for (int i = 0; i < p; i++) {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        nodes[to].in_degree++;
        nodes[from].edges[nodes[from].edge_count].to = to;
        nodes[from].edges[nodes[from].edge_count].weight = weight;
        nodes[from].edge_count++;
    }

    topological_sort();

    int has_output = 0;
    for (int i = 1; i <= n; i++) {
        if (nodes[i].edge_count == 0 && nodes[i].state > nodes[i].threshold) {
            printf("%d %d\n", i, nodes[i].state - nodes[i].threshold);
            has_output = 1;
        }
    }

    if (!has_output) {
        printf("NULL\n");
    }

    return 0;
}