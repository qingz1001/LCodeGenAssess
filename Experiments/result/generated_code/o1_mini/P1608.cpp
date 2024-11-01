#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2001
#define MAX_E 4000001
#define INF 2000000000

typedef struct Edge {
    int to;
    int cost;
    int next;
} Edge;

typedef struct HeapNode {
    int node;
    int dist;
} HeapNode;

Edge edges[MAX_E];
int head_nodes[MAX_N];
int edge_cnt = 0;

HeapNode heap_nodes[MAX_E];
int heap_size = 0;

int distance_arr[MAX_N];
long long count_arr[MAX_N];

void push_heap(int node, int dist){
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

HeapNode pop_heap(){
    HeapNode top = heap_nodes[1];
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
    return top;
}

int main(){
    int N, E;
    scanf("%d %d", &N, &E);
    memset(head_nodes, -1, sizeof(head_nodes));
    for(int i=0;i<E;i++){
        int I, J, C;
        scanf("%d %d %d", &I, &J, &C);
        edges[edge_cnt].to = J;
        edges[edge_cnt].cost = C;
        edges[edge_cnt].next = head_nodes[I];
        head_nodes[I] = edge_cnt;
        edge_cnt++;
    }
    for(int i=1;i<=N;i++){
        distance_arr[i] = INF;
        count_arr[i] = 0;
    }
    distance_arr[1] = 0;
    count_arr[1] = 1;
    push_heap(1, 0);
    while(heap_size > 0){
        HeapNode current = pop_heap();
        int u = current.node;
        int dist_u = current.dist;
        if(dist_u > distance_arr[u]) continue;
        for(int e = head_nodes[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            int cost = edges[e].cost;
            if(distance_arr[v] > distance_arr[u] + cost){
                distance_arr[v] = distance_arr[u] + cost;
                count_arr[v] = count_arr[u];
                push_heap(v, distance_arr[v]);
            }
            else if(distance_arr[v] == distance_arr[u] + cost){
                count_arr[v] += count_arr[u];
            }
        }
    }
    if(distance_arr[N] == INF){
        printf("No answer");
    }
    else{
        printf("%d %lld", distance_arr[N], count_arr[N]);
    }
    return 0;
}