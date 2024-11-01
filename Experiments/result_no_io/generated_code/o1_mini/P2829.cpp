#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll dist;
    int node;
} HeapNode;

typedef struct {
    int to;
    int w;
    int next;
} Edge;

#define MAXN 5001
#define MAXM 200001
#define INF 1000000000000000000LL

int adj_head[MAXN];
Edge edges[MAXM];
int total_edges = 0;

int degree_excluded[MAXN];
ll distance_dist[MAXN][2];

HeapNode heap_array[800000];
int heap_size = 0;

void heap_push(HeapNode node){
    int i = ++heap_size;
    heap_array[i] = node;
    while(i > 1 && heap_array[i].dist < heap_array[i/2].dist){
        HeapNode temp = heap_array[i];
        heap_array[i] = heap_array[i/2];
        heap_array[i/2] = temp;
        i /= 2;
    }
}

HeapNode heap_pop(){
    HeapNode min_node = heap_array[1];
    heap_array[1] = heap_array[heap_size--];
    int i = 1;
    while(2*i <= heap_size){
        int j = 2*i;
        if(j+1 <= heap_size && heap_array[j+1].dist < heap_array[j].dist){
            j++;
        }
        if(heap_array[j].dist < heap_array[i].dist){
            HeapNode temp = heap_array[i];
            heap_array[i] = heap_array[j];
            heap_array[j] = temp;
            i = j;
        }
        else{
            break;
        }
    }
    return min_node;
}

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    for(int i=1;i<=n;i++) adj_head[i] = -1;
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[total_edges].to = v;
        edges[total_edges].w = w;
        edges[total_edges].next = adj_head[u];
        adj_head[u] = total_edges++;
        edges[total_edges].to = u;
        edges[total_edges].w = w;
        edges[total_edges].next = adj_head[v];
        adj_head[v] = total_edges++;
    }
    for(int v=1; v<=n; v++){
        if(v ==1 || v ==n) continue;
        int cnt=0;
        for(int e=adj_head[v]; e!=-1; e=edges[e].next){
            if(edges[e].to !=1 && edges[e].to !=n){
                cnt++;
            }
        }
        degree_excluded[v] = cnt;
    }
    for(int v=1; v<=n; v++){
        distance_dist[v][0] = INF;
        distance_dist[v][1] = INF;
    }
    distance_dist[1][0] = 0;
    HeapNode start_node = {0, 1};
    heap_push(start_node);
    while(heap_size >0){
        HeapNode current = heap_pop();
        ll curr_dist = current.dist;
        int u = current.node;
        for(int e=adj_head[u]; e!=-1; e=edges[e].next){
            int v = edges[e].to;
            int w = edges[e].w;
            if(v !=1 && v !=n && degree_excluded[v] <k) continue;
            ll new_dist = curr_dist + w;
            if(new_dist < distance_dist[v][0]){
                distance_dist[v][1] = distance_dist[v][0];
                distance_dist[v][0] = new_dist;
                HeapNode new_node;
                new_node.dist = distance_dist[v][0];
                new_node.node = v;
                heap_push(new_node);
            }
            else if(new_dist > distance_dist[v][0] && new_dist < distance_dist[v][1]){
                distance_dist[v][1] = new_dist;
                HeapNode new_node;
                new_node.dist = distance_dist[v][1];
                new_node.node = v;
                heap_push(new_node);
            }
        }
    }
    if(distance_dist[n][1] < INF){
        printf("%lld\n", distance_dist[n][1]);
    }
    else{
        printf("-1\n");
    }
    return 0;
}