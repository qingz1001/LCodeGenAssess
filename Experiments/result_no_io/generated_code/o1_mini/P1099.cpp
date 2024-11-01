#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 305
#define INF 1000000000

typedef struct Edge {
    int to;
    int w;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int n, s;

// Queue for BFS
typedef struct {
    int data[MAXN];
    int front, rear;
} Queue;

void enqueue(Queue* q, int x){
    q->data[q->rear++] = x;
}

int dequeue(Queue* q){
    return q->data[q->front++];
}

int is_empty(Queue* q){
    return q->front >= q->rear;
}

// Function to add edge
void add_edge(int u, int v, int w){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->w = w;
    e->next = adj[u];
    adj[u] = e;
}

// BFS to find farthest node and distances
int bfs(int start, int dist[MAXN]){
    memset(dist, -1, sizeof(int)*(n+1));
    Queue q;
    q.front = q.rear = 0;
    enqueue(&q, start);
    dist[start] = 0;
    while(!is_empty(&q)){
        int u = dequeue(&q);
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            int v = e->to;
            if(dist[v]==-1){
                dist[v] = dist[u] + e->w;
                enqueue(&q, v);
            }
        }
    }
    int max_dist = -1, farthest = start;
    for(int i=1;i<=n;i++) {
        if(dist[i] > max_dist){
            max_dist = dist[i];
            farthest = i;
        }
    }
    return farthest;
}

// BFS to find distances from start
void bfs_all(int start, int dist[MAXN]){
    memset(dist, -1, sizeof(int)*(n+1));
    Queue q;
    q.front = q.rear = 0;
    enqueue(&q, start);
    dist[start] = 0;
    while(!is_empty(&q)){
        int u = dequeue(&q);
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            int v = e->to;
            if(dist[v]==-1){
                dist[v] = dist[u] + e->w;
                enqueue(&q, v);
            }
        }
    }
}

// Function to get path from u to v
int get_path(int u, int v, int parent[MAXN], int path_nodes[MAXN], int* m){
    *m = 0;
    while(v != u){
        path_nodes[(*m)++] = v;
        v = parent[v];
    }
    path_nodes[(*m)++] = u;
    // Reverse the path
    for(int i=0;i<(*m)/2;i++){
        int tmp = path_nodes[i];
        path_nodes[i] = path_nodes[*m - i -1];
        path_nodes[*m - i -1] = tmp;
    }
    return 0;
}

int main(){
    scanf("%d %d", &n, &s);
    for(int i=1;i<=n;i++) adj[i] = NULL;
    for(int i=1;i<n;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    // Find one end of diameter
    int dist1[MAXN];
    int u = bfs(1, dist1);
    // Find the other end of diameter
    int dist2[MAXN];
    int v_end = bfs(u, dist2);
    // Get path from u to v_end
    // BFS again to get parents
    memset(dist1, -1, sizeof(int)*(n+1));
    Queue q;
    q.front = q.rear = 0;
    enqueue(&q, u);
    dist1[u] = 0;
    int parent_node[MAXN];
    parent_node[u] = -1;
    while(!is_empty(&q)){
        int curr = dequeue(&q);
        for(Edge* e = adj[curr]; e != NULL; e = e->next){
            int to = e->to;
            if(dist1[to]==-1){
                dist1[to] = dist1[curr] + e->w;
                parent_node[to] = curr;
                enqueue(&q, to);
            }
        }
    }
    int diameter_path[MAXN];
    int m=0;
    get_path(u, v_end, parent_node, diameter_path, &m);
    // Compute distance from u along the path
    int path_dist[m];
    path_dist[0] = 0;
    for(int i=1;i<m;i++){
        // Find the edge between diameter_path[i-1] and diameter_path[i]
        for(Edge* e = adj[diameter_path[i-1]]; e != NULL; e = e->next){
            if(e->to == diameter_path[i]){
                path_dist[i] = path_dist[i-1] + e->w;
                break;
            }
        }
    }
    // Precompute distances from each path node to all nodes
    int dist_path[m][MAXN];
    for(int i=0;i<m;i++) {
        bfs_all(diameter_path[i], dist_path[i]);
    }
    // For each node, find projection on path
    int projection[m][MAXN];
    int proj_pos[MAXN];
    int proj_dist_val[MAXN];
    for(int x=1;x<=n;x++){
        int min_dist = INF;
        int pos = 0;
        for(int i=0;i<m;i++){
            if(dist_path[i][x] < min_dist){
                min_dist = dist_path[i][x];
                pos = i;
            }
        }
        proj_pos[x] = pos;
        proj_dist_val[x] = min_dist;
    }
    // Sliding window
    int res = INF;
    int r=0;
    for(int l=0;l<m;l++){
        while(r<m && (path_dist[r] - path_dist[l]) <= s){
            r++;
        }
        // Now window is [l, r-1]
        int current_max = -1;
        for(int x=1;x<=n;x++){
            if(proj_pos[x] >= l && proj_pos[x] < r){
                if(proj_dist_val[x] > current_max){
                    current_max = proj_dist_val[x];
                }
            }
            else{
                int d1 = dist_path[l][x];
                int d2 = dist_path[r-1][x];
                int tmp = d1 < d2 ? d1 : d2;
                if(tmp > current_max){
                    current_max = tmp;
                }
            }
        }
        if(current_max < res){
            res = current_max;
        }
    }
    printf("%d\n", res);
    return 0;
}