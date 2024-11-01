#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 2001
#define MAXM 200000
#define INF 1e18

typedef struct {
    int to;
    double factor;
    int next;
} Edge;

Edge edges[400000];
int head_node[MAXN];
int edge_cnt = 0;

typedef struct {
    int node;
    double cost;
} HeapNode;

HeapNode heap[400000];
int heap_size = 0;

void push_heap(HeapNode hn) {
    int i = heap_size++;
    heap[i] = hn;
    while (i != 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].cost <= heap[i].cost)
            break;
        HeapNode tmp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = tmp;
        i = parent;
    }
}

HeapNode pop_heap_node() {
    HeapNode top = heap[0];
    heap_size--;
    heap[0] = heap[heap_size];
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2*i +1;
        int right = 2*i +2;
        if (left < heap_size && heap[left].cost < heap[smallest].cost)
            smallest = left;
        if (right < heap_size && heap[right].cost < heap[smallest].cost)
            smallest = right;
        if (smallest != i) {
            HeapNode tmp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = tmp;
            i = smallest;
        }
        else break;
    }
    return top;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) head_node[i] = -1;
    for(int i=0;i<m;i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        double factor = 1.0 / (1.0 - ((double)z)/100.0);
        edges[edge_cnt].to = y;
        edges[edge_cnt].factor = factor;
        edges[edge_cnt].next = head_node[x];
        head_node[x] = edge_cnt++;
        edges[edge_cnt].to = x;
        edges[edge_cnt].factor = factor;
        edges[edge_cnt].next = head_node[y];
        head_node[y] = edge_cnt++;
    }
    int A, B;
    scanf("%d %d", &A, &B);
    double dist[MAXN];
    for(int i=1;i<=n;i++) dist[i] = INF;
    dist[B] = 100.0;
    HeapNode start;
    start.node = B;
    start.cost = dist[B];
    push_heap(start);
    while(heap_size >0){
        HeapNode current = pop_heap_node();
        int u = current.node;
        double cu = current.cost;
        if(u == A){
            break;
        }
        if(cu > dist[u]){
            continue;
        }
        for(int e = head_node[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            double new_cost = cu * edges[e].factor;
            if(new_cost < dist[v] - 1e-9){
                dist[v] = new_cost;
                HeapNode hn;
                hn.node = v;
                hn.cost = dist[v];
                push_heap(hn);
            }
        }
    }
    printf("%.8lf\n", dist[A]);
    return 0;
}