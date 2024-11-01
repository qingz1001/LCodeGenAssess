#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 1001
#define MAXM 100005
#define INF 1000000000

typedef struct {
    int u, v, t;
    bool active;
} Edge;

typedef struct {
    int node;
    int max_t;
} HeapNode;

int n, m, q;
Edge edges[MAXM];
int adj_list[MAXM * 2];
int adj_size[MAXN];
int edge_index_lookup[MAXN][MAXN];
int heap_size;
HeapNode heap_nodes[MAXN];
int min_max_val[MAXN];
int visit_gen[MAXN];
int current_gen = 1;

// Heap functions
void heap_push(int node, int max_t) {
    int i = heap_size++;
    heap_nodes[i].node = node;
    heap_nodes[i].max_t = max_t;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap_nodes[parent].max_t <= heap_nodes[i].max_t) break;
        HeapNode temp = heap_nodes[parent];
        heap_nodes[parent] = heap_nodes[i];
        heap_nodes[i] = temp;
        i = parent;
    }
}

HeapNode heap_pop_node() {
    HeapNode res = heap_nodes[0];
    heap_size--;
    heap_nodes[0] = heap_nodes[heap_size];
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heap_size && heap_nodes[left].max_t < heap_nodes[smallest].max_t) smallest = left;
        if (right < heap_size && heap_nodes[right].max_t < heap_nodes[smallest].max_t) smallest = right;
        if (smallest == i) break;
        HeapNode temp = heap_nodes[i];
        heap_nodes[i] = heap_nodes[smallest];
        heap_nodes[smallest] = temp;
        i = smallest;
    }
    return res;
}

int main(){
    scanf("%d %d %d", &n, &m, &q);
    memset(edge_index_lookup, -1, sizeof(edge_index_lookup));
    for(int i=0; i<m; i++){
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].t = t;
        edges[i].active = true;
        adj_list[2*i] = i;
        adj_size[u]++;
        adj_list[2*i+1] = i;
        adj_size[v]++;
        edge_index_lookup[u][v] = i;
        edge_index_lookup[v][u] = i;
    }
    for(int i=0; i<q; i++){
        int k, u, v;
        scanf("%d %d %d", &k, &u, &v);
        if(k == 1){
            current_gen++;
            heap_size = 0;
            min_max_val[u] = 0;
            visit_gen[u] = current_gen;
            heap_push(u, 0);
            int answer = INF;
            while(heap_size > 0){
                HeapNode current = heap_pop_node();
                if(current.node == v){
                    answer = current.max_t;
                    break;
                }
                if(current.max_t > min_max_val[current.node]) continue;
                for(int j=0; j<adj_size[current.node]; j++){
                    int edge_id = adj_list[j + (current.node == edges[edge_id].u ? edges[current.node].u : edges[current.node].v)];
                    edge_id = adj_list[j];
                    if(!edges[edge_id].active) continue;
                    int neighbor = (edges[edge_id].u == current.node) ? edges[edge_id].v : edges[edge_id].u;
                    int new_max = current.max_t > edges[edge_id].t ? current.max_t : edges[edge_id].t;
                    if(visit_gen[neighbor] != current_gen || new_max < min_max_val[neighbor]){
                        min_max_val[neighbor] = new_max;
                        visit_gen[neighbor] = current_gen;
                        heap_push(neighbor, new_max);
                    }
                }
            }
            printf("%d\n", answer);
        }
        else{
            int edge_id = edge_index_lookup[u][v];
            if(edge_id != -1){
                edges[edge_id].active = false;
            }
        }
    }
    return 0;
}