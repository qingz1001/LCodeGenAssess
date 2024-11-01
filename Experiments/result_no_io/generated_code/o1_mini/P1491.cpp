#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN 201
#define MAXM 10001
#define INF 1e18
#define EPS 1e-6

typedef struct Edge {
    int to;
    double weight;
} Edge;

typedef struct Path {
    double distance;
    int *nodes;
    int length;
} Path;

typedef struct HeapNode {
    double dist;
    int node;
} HeapNode;

typedef struct PriorityQueue {
    HeapNode *data;
    int size;
    int capacity;
} PriorityQueue;

// Priority Queue functions
PriorityQueue* createQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swapHeapNode(HeapNode *a, HeapNode *b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void pushQueue(PriorityQueue *pq, double dist, int node){
    if(pq->size == pq->capacity){
        pq->capacity *= 2;
        pq->data = (HeapNode*)realloc(pq->data, sizeof(HeapNode) * pq->capacity);
    }
    int i = pq->size++;
    pq->data[i].dist = dist;
    pq->data[i].node = node;
    while(i != 0){
        int parent = (i - 1) / 2;
        if(pq->data[parent].dist <= pq->data[i].dist) break;
        swapHeapNode(&pq->data[parent], &pq->data[i]);
        i = parent;
    }
}

HeapNode popQueue(PriorityQueue *pq){
    HeapNode top = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    int i = 0;
    while(1){
        int smallest = i;
        int left = 2*i +1;
        int right = 2*i +2;
        if(left < pq->size && pq->data[left].dist < pq->data[smallest].dist){
            smallest = left;
        }
        if(right < pq->size && pq->data[right].dist < pq->data[smallest].dist){
            smallest = right;
        }
        if(smallest != i){
            swapHeapNode(&pq->data[smallest], &pq->data[i]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int isEmpty(PriorityQueue *pq){
    return pq->size == 0;
}

// Graph representation
typedef struct {
    Edge edges[MAXM];
    int count;
} AdjList[MAXN];

AdjList adj;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    double coords[n+1][2];
    for(int i=1;i<=n;i++) scanf("%lf %lf", &coords[i][0], &coords[i][1]);
    // Initialize adjacency list
    for(int i=1;i<=n;i++) adj[i].count = 0;
    for(int i=0;i<m;i++){
        int p, q;
        scanf("%d %d", &p, &q);
        if(p != q){
            double dx = coords[p][0] - coords[q][0];
            double dy = coords[p][1] - coords[q][1];
            double dist = sqrt(dx*dx + dy*dy);
            adj[p].edges[adj[p].count].to = q;
            adj[p].edges[adj[p].count].weight = dist;
            adj[p].count++;
            adj[q].edges[adj[q].count].to = p;
            adj[q].edges[adj[q].count].weight = dist;
            adj[q].count++;
        }
        else{
            double dist = 0.0;
            adj[p].edges[adj[p].count].to = q;
            adj[p].edges[adj[p].count].weight = dist;
            adj[p].count++;
        }
    }

    // Dijkstra to find shortest path and count
    double dist[n+1];
    memset(dist, 0x3f, sizeof(dist));
    long long count_paths[n+1];
    memset(count_paths, 0, sizeof(count_paths));
    int prev[n+1];
    for(int i=1;i<=n;i++) prev[i] = -1;
    PriorityQueue *pq = createQueue(10000);
    dist[1] = 0.0;
    count_paths[1] = 1;
    pushQueue(pq, 0.0, 1);
    while(!isEmpty(pq)){
        HeapNode current = popQueue(pq);
        double current_dist = current.dist;
        int u = current.node;
        if(current_dist > dist[u] + EPS) continue;
        for(int i=0;i<adj[u].count;i++){
            int v = adj[u].edges[i].to;
            double w = adj[u].edges[i].weight;
            if(dist[v] > dist[u] + w + EPS){
                dist[v] = dist[u] + w;
                count_paths[v] = count_paths[u];
                prev[v] = u;
                pushQueue(pq, dist[v], v);
            }
            else if(fabs(dist[v] - (dist[u] + w)) < EPS){
                count_paths[v] += count_paths[u];
            }
        }
    }
    free(pq->data);
    free(pq);
    if(dist[n] == INF){
        printf("-1\n");
        return 0;
    }
    if(count_paths[n] >=2){
        printf("%.2lf\n", dist[n]);
        return 0;
    }
    // Reconstruct P1
    int path_nodes[n+1];
    int path_length = 0;
    int current = n;
    while(current != -1){
        path_nodes[path_length++] = current;
        current = prev[current];
    }
    // Reverse the path
    int P1[path_length];
    for(int i=0;i<path_length;i++) P1[i] = path_nodes[path_length-1-i];
    // Compute cumulative distances
    double cumulative[path_length];
    cumulative[0] = 0.0;
    for(int i=1;i<path_length;i++){
        int u = P1[i-1];
        int v = P1[i];
        double w = 0.0;
        for(int j=0;j<adj[u].count;j++) if(adj[u].edges[j].to == v){
            w = adj[u].edges[j].weight;
            break;
        }
        cumulative[i] = cumulative[i-1] + w;
    }
    // Generate candidates
    double second_shortest = INF;
    for(int i=0;i<path_length-1;i++){
        int spur = P1[i];
        // Block nodes except spur
        int blocked[n+1];
        memset(blocked, 0, sizeof(blocked));
        for(int j=0;j<i;j++) blocked[P1[j]] = 1;
        // Dijkstra from spur to n
        double dist_spur[n+1];
        memset(dist_spur, 0x3f, sizeof(dist_spur));
        dist_spur[spur] = 0.0;
        PriorityQueue *pq_spur = createQueue(10000);
        pushQueue(pq_spur, 0.0, spur);
        while(!isEmpty(pq_spur)){
            HeapNode current_spur = popQueue(pq_spur);
            double d = current_spur.dist;
            int u = current_spur.node;
            if(d > dist_spur[u] + EPS) continue;
            for(int k=0;k<adj[u].count;k++){
                int v = adj[u].edges[k].to;
                double w = adj[u].edges[k].weight;
                if(blocked[v]) continue;
                if(dist_spur[v] > dist_spur[u] + w + EPS){
                    dist_spur[v] = dist_spur[u] + w;
                    pushQueue(pq_spur, dist_spur[v], v);
                }
            }
        }
        free(pq_spur->data);
        free(pq_spur);
        if(dist_spur[n] < INF){
            double total = cumulative[i] + dist_spur[n];
            if(total < second_shortest - EPS){
                second_shortest = total;
            }
        }
    }
    if(second_shortest < INF){
        printf("%.2lf\n", second_shortest);
    }
    else{
        printf("-1\n");
    }
    return 0;
}