#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 305
#define MAXM (MAXN*2)
#define INF 1000000000

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int n, s;
int u_start, u_end;
int predecessor[MAXN];
int dist_temp[MAXN];
int diameter_path[MAXN];
int path_length;
int cdist[MAXN];
int distance_v_i[MAXN][MAXN];

void add_edge(int u, int v, int w){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = adj[u];
    adj[u] = e;
}

void bfs(int start, int dist[]){
    for(int i=1;i<=n;i++) dist[i] = INF;
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = start;
    dist[start] = 0;
    while(front < rear){
        int u = queue[front++];
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            int v = e->to;
            if(dist[v] == INF){
                dist[v] = dist[u] + e->weight;
                queue[rear++] = v;
            }
        }
    }
}

int get_furthest(int start, int dist[]){
    bfs(start, dist);
    int max_dist = -1, furthest = start;
    for(int i=1;i<=n;i++) {
        if(dist[i] > max_dist){
            max_dist = dist[i];
            furthest = i;
        }
    }
    return furthest;
}

int find_path(int start, int end){
    memset(predecessor, -1, sizeof(predecessor));
    bfs(start, dist_temp);
    if(dist_temp[end] == INF) return 0;
    // Trace back the path
    int current = end;
    path_length = 0;
    while(current != start){
        diameter_path[path_length++] = current;
        // Find predecessor
        for(Edge* e = adj[current]; e != NULL; e = e->next){
            if(dist_temp[e->to] == dist_temp[current] - e->weight){
                current = e->to;
                break;
            }
        }
    }
    diameter_path[path_length++] = start;
    // Reverse the path
    for(int i=0;i<path_length/2;i++){
        int tmp = diameter_path[i];
        diameter_path[i] = diameter_path[path_length-1-i];
        diameter_path[path_length-1-i] = tmp;
    }
    return path_length;
}

int main(){
    scanf("%d %d", &n, &s);
    for(int i=1;i<n;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    // Find diameter
    int dist1[MAXN];
    int u = get_furthest(1, dist1);
    int dist2[MAXN];
    int v = get_furthest(u, dist2);
    int len = find_path(u, v);
    // Compute cumulative distance
    cdist[0] = 0;
    for(int i=1;i<path_length;i++){
        int prev = diameter_path[i-1];
        int current = diameter_path[i];
        int w = 0;
        for(Edge* e = adj[prev]; e != NULL; e = e->next){
            if(e->to == current){
                w = e->weight;
                break;
            }
        }
        cdist[i] = cdist[i-1] + w;
    }
    // Precompute distance_v_i
    for(int i=0;i<path_length;i++){
        bfs(diameter_path[i], dist_temp);
        for(int v_node=1; v_node<=n; v_node++) {
            distance_v_i[v_node][i] = dist_temp[v_node];
        }
    }
    int result = INF;
    for(int a=0;a<path_length;a++){
        for(int b=a;b<path_length;b++){
            if(cdist[b] - cdist[a] > s) break;
            int current_max = -1;
            for(int v_node=1; v_node<=n; v_node++){
                int min_dist = INF;
                for(int i=a;i<=b;i++) {
                    if(distance_v_i[v_node][i] < min_dist){
                        min_dist = distance_v_i[v_node][i];
                    }
                }
                if(min_dist > current_max){
                    current_max = min_dist;
                }
            }
            if(current_max < result){
                result = current_max;
            }
        }
    }
    printf("%d\n", result);
    // Free memory
    for(int i=1;i<=n;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    return 0;
}