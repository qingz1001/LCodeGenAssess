#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5001
#define MAX_M 200001
#define INF 100000000000000LL

typedef long long ll;

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    ll dist;
    int node;
} HeapItem;

Edge edge_pool[MAX_M];
int edge_cnt = 0;
Edge* adj[MAX_N];
int degrees[MAX_N];
int allowed[MAX_N];

HeapItem heap_array[1000001];
int heap_size = 0;

ll dist1_arr[MAX_N];
ll dist2_arr[MAX_N];

void heap_push(ll dist, int node) {
    heap_size++;
    heap_array[heap_size].dist = dist;
    heap_array[heap_size].node = node;
    int i = heap_size;
    while (i > 1 && heap_array[i].dist < heap_array[i/2].dist) {
        HeapItem temp = heap_array[i];
        heap_array[i] = heap_array[i/2];
        heap_array[i/2] = temp;
        i = i/2;
    }
}

HeapItem heap_pop() {
    HeapItem top = heap_array[1];
    heap_array[1] = heap_array[heap_size];
    heap_size--;
    int i = 1;
    while (1) {
        int smallest = i;
        int l = 2*i;
        int r = 2*i +1;
        if (l <= heap_size && heap_array[l].dist < heap_array[smallest].dist)
            smallest = l;
        if (r <= heap_size && heap_array[r].dist < heap_array[smallest].dist)
            smallest = r;
        if (smallest != i) {
            HeapItem temp = heap_array[i];
            heap_array[i] = heap_array[smallest];
            heap_array[smallest] = temp;
            i = smallest;
        }
        else {
            break;
        }
    }
    return top;
}

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        degrees[u]++;
        degrees[v]++;
        // Add edge u -> v
        edge_pool[edge_cnt].to = v;
        edge_pool[edge_cnt].weight = w;
        edge_pool[edge_cnt].next = adj[u];
        adj[u] = &edge_pool[edge_cnt++];
        // Add edge v -> u
        edge_pool[edge_cnt].to = u;
        edge_pool[edge_cnt].weight = w;
        edge_pool[edge_cnt].next = adj[v];
        adj[v] = &edge_pool[edge_cnt++];
    }
    for(int u=1; u<=n; u++){
        if(u ==1 || u ==n || degrees[u]>=k){
            allowed[u] =1;
        }
        else{
            allowed[u] =0;
        }
    }
    for(int u=1; u<=n; u++){
        dist1_arr[u] = INF;
        dist2_arr[u] = INF;
    }
    dist1_arr[1] =0;
    heap_push(0, 1);
    while(heap_size >0){
        HeapItem current = heap_pop();
        ll d = current.dist;
        int u = current.node;
        if(d > dist2_arr[u]){
            continue;
        }
        Edge* e = adj[u];
        while(e != NULL){
            int v = e->to;
            ll new_dist = d + e->weight;
            if(allowed[v]){
                if(new_dist < dist1_arr[v]){
                    dist2_arr[v] = dist1_arr[v];
                    dist1_arr[v] = new_dist;
                    heap_push(new_dist, v);
                }
                else if(new_dist > dist1_arr[v] && new_dist < dist2_arr[v]){
                    dist2_arr[v] = new_dist;
                    heap_push(new_dist, v);
                }
            }
            e = e->next;
        }
    }
    if(dist2_arr[n] < INF){
        printf("%lld\n", dist2_arr[n]);
    }
    else{
        printf("-1\n");
    }
    return 0;
}