#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 201
#define MAX_P 40000
#define MAX_EDGES 800000
#define INF 1000000000

typedef struct {
    int A;
    int B;
    int L;
} Road;

typedef struct {
    int to;
    int rev;
    int cap;
    int next;
} Edge;

Road roads[MAX_P];
Edge edges_store[MAX_EDGES];
int head_store[MAX_N];
int edge_count_store;
int N, P, T;

int compare(const void* a, const void* b) {
    Road* ra = (Road*)a;
    Road* rb = (Road*)b;
    if (ra->L != rb->L)
        return ra->L - rb->L;
    if (ra->A != rb->A)
        return ra->A - rb->A;
    return ra->B - rb->B;
}

void add_edge(int from, int to, int cap) {
    edges_store[edge_count_store].to = to;
    edges_store[edge_count_store].cap = cap;
    edges_store[edge_count_store].rev = edge_count_store + 1;
    edges_store[edge_count_store].next = head_store[from];
    head_store[from] = edge_count_store;
    edge_count_store++;

    edges_store[edge_count_store].to = from;
    edges_store[edge_count_store].cap = 0;
    edges_store[edge_count_store].rev = edge_count_store - 1;
    edges_store[edge_count_store].next = head_store[to];
    head_store[to] = edge_count_store;
    edge_count_store++;
}

int level_arr[MAX_N];
int ptr_arr[MAX_N];
int queue_arr[MAX_N];
int front, rear;

int bfs(int source, int sink) {
    memset(level_arr, -1, sizeof(int)*(N+1));
    front = rear = 0;
    queue_arr[rear++] = source;
    level_arr[source] = 0;
    while (front < rear) {
        int u = queue_arr[front++];
        int e = head_store[u];
        while (e != -1) {
            if (edges_store[e].cap > 0 && level_arr[edges_store[e].to] == -1) {
                level_arr[edges_store[e].to] = level_arr[u] + 1;
                queue_arr[rear++] = edges_store[e].to;
                if (edges_store[e].to == sink)
                    break;
            }
            e = edges_store[e].next;
        }
    }
    return level_arr[sink] != -1;
}

int dfs(int u, int flow, int sink) {
    if (u == sink)
        return flow;
    for (; ptr_arr[u] != -1; ptr_arr[u] = edges_store[ptr_arr[u]].next) {
        int e = ptr_arr[u];
        if (edges_store[e].cap > 0 && level_arr[edges_store[e].to] == level_arr[u] + 1) {
            int pushed = dfs(edges_store[e].to, (flow < edges_store[e].cap) ? flow : edges_store[e].cap, sink);
            if (pushed > 0) {
                edges_store[e].cap -= pushed;
                edges_store[edges_store[e].rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int dinic(int source, int sink, int required) {
    int flow = 0;
    while (bfs(source, sink)) {
        memcpy(ptr_arr, head_store, sizeof(int)*(N+1));
        while (1) {
            int pushed = dfs(source, INF, sink);
            if (pushed == 0)
                break;
            flow += pushed;
            if (flow >= required)
                return flow;
        }
    }
    return flow;
}

int main(){
    scanf("%d %d %d", &N, &P, &T);
    for(int i=0;i<P;i++){
        scanf("%d %d %d", &roads[i].A, &roads[i].B, &roads[i].L);
    }
    qsort(roads, P, sizeof(Road), compare);
    int left = roads[0].L, right = roads[P-1].L, answer = right;
    while(left <= right){
        int mid = left + (right - left) / 2;
        // Find m
        int m = 0;
        while(m < P && roads[m].L <= mid)
            m++;
        // Build graph
        memset(head_store, -1, sizeof(head_store));
        edge_count_store = 0;
        for(int i=0;i<m;i++){
            add_edge(roads[i].A, roads[i].B, 1);
            add_edge(roads[i].B, roads[i].A, 1);
        }
        // Compute max flow
        int flow = dinic(1, N, T);
        if(flow >= T){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%d\n", answer);
    return 0;
}