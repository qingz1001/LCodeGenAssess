#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 5001
#define MAX_M 100001

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], cnt;
int n, m, k;
int dist[MAX_N], second_dist[MAX_N];
bool visited[MAX_N];
int connections[MAX_N];

void add_edge(int u, int v, int w) {
    edges[cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

typedef struct {
    int node;
    int dist;
} Node;

typedef struct {
    Node* arr;
    int size;
} PriorityQueue;

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(PriorityQueue* pq, int node, int dist) {
    pq->arr[pq->size].node = node;
    pq->arr[pq->size].dist = dist;
    int current = pq->size;
    int parent = (current - 1) / 2;
    
    while (current > 0 && pq->arr[current].dist < pq->arr[parent].dist) {
        swap(&pq->arr[current], &pq->arr[parent]);
        current = parent;
        parent = (current - 1) / 2;
    }
    
    pq->size++;
}

Node pop(PriorityQueue* pq) {
    Node min = pq->arr[0];
    pq->size--;
    pq->arr[0] = pq->arr[pq->size];
    
    int current = 0;
    while (1) {
        int leftChild = 2 * current + 1;
        int rightChild = 2 * current + 2;
        int smallest = current;
        
        if (leftChild < pq->size && pq->arr[leftChild].dist < pq->arr[smallest].dist)
            smallest = leftChild;
        
        if (rightChild < pq->size && pq->arr[rightChild].dist < pq->arr[smallest].dist)
            smallest = rightChild;
        
        if (smallest == current)
            break;
        
        swap(&pq->arr[current], &pq->arr[smallest]);
        current = smallest;
    }
    
    return min;
}

void dijkstra() {
    PriorityQueue pq;
    pq.arr = (Node*)malloc(sizeof(Node) * MAX_N);
    pq.size = 0;
    
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        second_dist[i] = INT_MAX;
        visited[i] = false;
    }
    
    dist[1] = 0;
    push(&pq, 1, 0);
    
    while (pq.size > 0) {
        Node node = pop(&pq);
        int u = node.node;
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            int w = edges[i].w;
            
            if (u != 1 && v != n && connections[v] < k) continue;
            
            if (dist[u] + w < dist[v]) {
                second_dist[v] = dist[v];
                dist[v] = dist[u] + w;
                push(&pq, v, dist[v]);
            } else if (dist[u] + w < second_dist[v] && dist[u] + w != dist[v]) {
                second_dist[v] = dist[u] + w;
                push(&pq, v, second_dist[v]);
            }
        }
    }
    
    free(pq.arr);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    memset(head, -1, sizeof(head));
    cnt = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        connections[u]++;
        connections[v]++;
    }
    
    dijkstra();
    
    if (second_dist[n] == INT_MAX)
        printf("-1\n");
    else
        printf("%d\n", second_dist[n]);
    
    return 0;
}