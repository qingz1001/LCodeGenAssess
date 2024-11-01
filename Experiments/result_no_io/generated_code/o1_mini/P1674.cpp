#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define MAXM 80000
#define INF 1000000000

typedef struct {
    int A;
    int B;
    int L;
} Road;

typedef struct Edge {
    int to;
    int rev;
    int cap;
} Edge;

Road roads[40000];
Edge edges_store[MAXM];
int head_list[MAXN];
int edge_cnt_global;

int cmp(const void *a, const void *b){
    Road *ra = (Road*)a;
    Road *rb = (Road*)b;
    if (ra->L != rb->L)
        return ra->L - rb->L;
    if (ra->A != rb->A)
        return ra->A - rb->A;
    return ra->B - rb->B;
}

void add_edge(int from, int to, int cap){
    edges_store[edge_cnt_global].to = to;
    edges_store[edge_cnt_global].cap = cap;
    edges_store[edge_cnt_global].rev = edge_cnt_global + 1;
    edge_cnt_global++;
    
    edges_store[edge_cnt_global].to = from;
    edges_store[edge_cnt_global].cap = 0;
    edges_store[edge_cnt_global].rev = edge_cnt_global - 1;
    edge_cnt_global++;
}

int level_list[MAXN];
int ptr_list[MAXN];
int queue_list[MAXN];
int front, rear;

int bfs(int s, int t){
    memset(level_list, -1, sizeof(int)*(MAXN));
    front = rear = 0;
    queue_list[rear++] = s;
    level_list[s] = 0;
    while(front < rear){
        int u = queue_list[front++];
        for(int i = head_list[u]; i < edge_cnt_global; i += 2){
            Edge *e = &edges_store[i];
            if(e->cap > 0 && level_list[e->to] == -1){
                level_list[e->to] = level_list[u] + 1;
                queue_list[rear++] = e->to;
                if(e->to == t) break;
            }
        }
    }
    return level_list[t] != -1;
}

int dfs(int u, int t, int flow){
    if(u == t) return flow;
    for(int *p = &ptr_list[u]; *p < edge_cnt_global; (*p) +=2 ){
        Edge *e = &edges_store[*p];
        if(e->cap > 0 && level_list[e->to] == level_list[u] + 1){
            int pushed = dfs(e->to, t, flow < e->cap ? flow : e->cap);
            if(pushed > 0){
                edges_store[*p].cap -= pushed;
                edges_store[e->rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t){
    int flow = 0;
    while(bfs(s, t)){
        memset(ptr_list, 0, sizeof(int)*(MAXN));
        while(1){
            int pushed = dfs(s, t, INF);
            if(pushed == 0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    int N, P, T;
    scanf("%d %d %d", &N, &P, &T);
    for(int i=0;i<P;i++) scanf("%d %d %d", &roads[i].A, &roads[i].B, &roads[i].L);
    qsort(roads, P, sizeof(Road), cmp);
    int left = 0, right = 1000000, answer = 1000000;
    while(left <= right){
        int mid = left + (right - left)/2;
        // Build graph
        memset(head_list, -1, sizeof(head_list));
        edge_cnt_global = 0;
        for(int i=0;i<P;i++) {
            if(roads[i].L > mid) break;
            add_edge(roads[i].A, roads[i].B, 1);
            add_edge(roads[i].B, roads[i].A, 1);
        }
        // Compute max flow
        int flow = max_flow(1, N);
        if(flow >= T){
            answer = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    printf("%d\n", answer);
    return 0;
}