#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int to;
    ll weight;
    int next;
} Edge;

typedef struct {
    int node;
    ll dist;
} HeapNode;

#define MAXN 100005
#define MAXM 200010
#define INF 1000000000000000LL

Edge edges[MAXM];
int head_nodes[MAXN];
int edge_cnt = 0;

ll d[MAXN];
HeapNode heap_nodes[MAXM];
int heap_size = 0;

void push_heap(int node, ll dist) {
    heap_size++;
    heap_nodes[heap_size].node = node;
    heap_nodes[heap_size].dist = dist;
    int i = heap_size;
    while(i > 1 && heap_nodes[i].dist < heap_nodes[i/2].dist){
        HeapNode temp = heap_nodes[i];
        heap_nodes[i] = heap_nodes[i/2];
        heap_nodes[i/2] = temp;
        i /= 2;
    }
}

HeapNode pop_heap_min() {
    HeapNode min = heap_nodes[1];
    heap_nodes[1] = heap_nodes[heap_size];
    heap_size--;
    int i = 1;
    while(2*i <= heap_size){
        int smallest = i;
        if(heap_nodes[2*i].dist < heap_nodes[smallest].dist){
            smallest = 2*i;
        }
        if(2*i+1 <= heap_size && heap_nodes[2*i+1].dist < heap_nodes[smallest].dist){
            smallest = 2*i+1;
        }
        if(smallest != i){
            HeapNode temp = heap_nodes[i];
            heap_nodes[i] = heap_nodes[smallest];
            heap_nodes[smallest] = temp;
            i = smallest;
        }
        else{
            break;
        }
    }
    return min;
}

void dijkstra(int start, int N){
    for(int i=1;i<=N;i++) d[i] = INF;
    d[start] = 0;
    heap_size = 1;
    heap_nodes[1].node = start;
    heap_nodes[1].dist = 0;
    while(heap_size > 0){
        HeapNode current = pop_heap_min();
        int u = current.node;
        if(current.dist > d[u]) continue;
        for(int e = head_nodes[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            ll w = edges[e].weight;
            if(d[v] > d[u] + w){
                d[v] = d[u] + w;
                push_heap(v, d[v]);
            }
        }
    }
}

int main(){
    int N;
    scanf("%d", &N);
    for(int i=1;i<=N;i++) head_nodes[i] = -1;
    for(int i=0;i<N;i++){
        int A, B;
        ll L;
        scanf("%d %d %lld", &A, &B, &L);
        edges[edge_cnt].to = B;
        edges[edge_cnt].weight = L;
        edges[edge_cnt].next = head_nodes[A];
        head_nodes[A] = edge_cnt++;
        
        edges[edge_cnt].to = A;
        edges[edge_cnt].weight = L;
        edges[edge_cnt].next = head_nodes[B];
        head_nodes[B] = edge_cnt++;
    }
    
    dijkstra(1, N);
    int far_node = 1;
    ll max_dist = 0;
    for(int i=1;i<=N;i++) {
        if(d[i] > max_dist){
            max_dist = d[i];
            far_node = i;
        }
    }
    
    dijkstra(far_node, N);
    max_dist = 0;
    for(int i=1;i<=N;i++) {
        if(d[i] > max_dist){
            max_dist = d[i];
        }
    }
    
    double result = (double)max_dist / 2.0;
    // To ensure proper rounding, add a small value
    printf("%.1lf\n", result + 1e-8);
    return 0;
}