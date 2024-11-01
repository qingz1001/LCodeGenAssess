#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2001
#define MAXE 4000001
#define INF 1000000000

typedef struct {
    int to;
    int cost;
    int next;
} Edge;

Edge edges[MAXE];
int head_list[MAXN];
int edge_cnt = 0;

typedef struct {
    int dist;
    int node;
} HeapNode;

HeapNode heap_nodes[MAXE];
int heap_size = 0;

int dist_arr[MAXN];
unsigned int count_paths[MAXN];

int readInt() {
    int c = getchar();
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    int sign = 1, res = 0;
    if (c == '-') { sign = -1; c = getchar(); }
    while (c >= '0' && c <= '9') {
        res = res *10 + (c - '0');
        c = getchar();
    }
    return sign * res;
}

void heap_push(int distance, int node) {
    int i = ++heap_size;
    heap_nodes[i].dist = distance;
    heap_nodes[i].node = node;
    while (i > 1 && heap_nodes[i].dist < heap_nodes[i/2].dist) {
        HeapNode temp = heap_nodes[i];
        heap_nodes[i] = heap_nodes[i/2];
        heap_nodes[i/2] = temp;
        i /=2;
    }
}

HeapNode heap_pop_node() {
    HeapNode top = heap_nodes[1];
    HeapNode last = heap_nodes[heap_size--];
    int i =1, child;
    while (i*2 <= heap_size) {
        child = i*2;
        if (child < heap_size && heap_nodes[child+1].dist < heap_nodes[child].dist) child++;
        if (last.dist <= heap_nodes[child].dist) break;
        heap_nodes[i] = heap_nodes[child];
        i = child;
    }
    heap_nodes[i] = last;
    return top;
}

int main(){
    int N, E;
    N = readInt();
    E = readInt();
    memset(head_list, -1, sizeof(head_list));
    for(int i=0;i<E;i++){
        int I, J, C;
        I = readInt();
        J = readInt();
        C = readInt();
        edges[edge_cnt].to = J;
        edges[edge_cnt].cost = C;
        edges[edge_cnt].next = head_list[I];
        head_list[I] = edge_cnt++;
    }
    for(int i=1;i<=N;i++){
        dist_arr[i] = INF;
        count_paths[i] = 0;
    }
    dist_arr[1] = 0;
    count_paths[1] = 1;
    heap_push(0,1);
    while(heap_size){
        HeapNode current = heap_pop_node();
        int u = current.node;
        int d = current.dist;
        if(d > dist_arr[u]) continue;
        for(int e = head_list[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            int cost = edges[e].cost;
            if(dist_arr[v] > dist_arr[u] + cost){
                dist_arr[v] = dist_arr[u] + cost;
                count_paths[v] = count_paths[u];
                heap_push(dist_arr[v], v);
            }
            else if(dist_arr[v] == dist_arr[u] + cost){
                count_paths[v] += count_paths[u];
                if(count_paths[v] > 2147483648U) count_paths[v] = 2147483648U;
            }
        }
    }
    if(dist_arr[N] == INF){
        printf("No answer");
    }
    else{
        printf("%d %u", dist_arr[N], count_paths[N]);
    }
    return 0;
}