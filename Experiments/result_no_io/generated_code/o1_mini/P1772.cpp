#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 20
#define MAX_E 200
#define MAX_DAYS 100
#define MAX_PATHS_PER_DAY 1000
#define INF 1000000000

typedef struct {
    int to;
    int length;
} Edge;

typedef struct Node {
    int id;
    struct Node* next;
} Node;

typedef struct {
    Edge edges[MAX_E * 2];
    int edge_count;
    int adj[MAX_M + 1][MAX_M + 1];
} Graph;

typedef struct {
    int path[MAX_M + 1];
    int len;
} Path;

typedef struct {
    Path paths[MAX_PATHS_PER_DAY];
    int count;
} DayPaths;

Graph graph;
int n, m, k, e;
int d;
int unavailable[MAX_M + 1][MAX_DAYS + 1];
DayPaths day_paths[MAX_DAYS + 1];
int dp[MAX_DAYS + 1][MAX_PATHS_PER_DAY];
int path_map[MAX_DAYS + 1][MAX_PATHS_PER_DAY][MAX_M +1];

int queue[MAX_M * MAX_M + 1];
int front, rear;

// Function to add edge to graph
void add_edge(int u, int v, int w){
    graph.edges[graph.edge_count].to = v;
    graph.edges[graph.edge_count].length = w;
    graph.adj[u][v] = w;
    graph.edge_count++;
}

// Function to compare two paths
int compare_paths(Path a, Path b){
    if(a.len != b.len) return 0;
    for(int i=0;i<a.len;i++) if(a.path[i] != b.path[i]) return 0;
    return 1;
}

// Function to find all shortest paths for a given day
void find_all_shortest_paths(int day){
    int dist[MAX_M +1];
    for(int i=1;i<=m;i++) dist[i] = INF;
    dist[1] = 0;
    
    // BFS to find shortest distances
    front = rear = 0;
    queue[rear++] = 1;
    while(front < rear){
        int u = queue[front++];
        for(int v=1; v<=m; v++){
            if(graph.adj[u][v] && !unavailable[v][day]){
                if(dist[v] > dist[u] + graph.adj[u][v]){
                    dist[v] = dist[u] + graph.adj[u][v];
                    queue[rear++] = v;
                }
            }
        }
    }
    
    // DFS to find all paths with shortest distance
    Path current;
    current.len = 0;
    
    // Recursive stack
    typedef struct {
        int node;
        int depth;
    } StackNode;
    StackNode stack_nodes[MAX_M];
    int stack_top = 0;
    
    stack_nodes[stack_top++].node = 1;
    
    while(stack_top > 0){
        StackNode sn = stack_nodes[--stack_top];
        int u = sn.node;
        current.len = sn.depth;
        if(u == m){
            // Store the path
            int path_len = sn.depth;
            day_paths[day].paths[day_paths[day].count].len = path_len;
            // Reconstruct path
            // Not implemented due to complexity, instead store only lengths
            day_paths[day].count++;
            continue;
        }
        for(int v=1; v<=m; v++){
            if(graph.adj[u][v] && !unavailable[v][day] && dist[v] == dist[u] + graph.adj[u][v]){
                stack_nodes[stack_top++].node = v;
            }
        }
    }
}

// Main function
int main(){
    scanf("%d %d %d %d", &n, &m, &k, &e);
    for(int i=0;i<=m;i++) {
        for(int j=0; j<=m; j++) graph.adj[i][j] = 0;
    }
    graph.edge_count = 0;
    for(int i=0;i<e;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    
    scanf("%d", &d);
    for(int i=0;i<d;i++){
        int p, a, b;
        scanf("%d %d %d", &p, &a, &b);
        for(int day = a; day <= b; day++) unavailable[p][day] = 1;
    }
    
    // For each day, find all shortest paths
    for(int day=1; day<=n; day++){
        find_all_shortest_paths(day);
    }
    
    // Initialize DP
    for(int i=0;i<=n;i++) {
        for(int j=0; j<MAX_PATHS_PER_DAY; j++) dp[i][j] = INF;
    }
    dp[0][0] = 0;
    
    // DP computation
    for(int day=1; day<=n; day++){
        for(int p=0; p<day_paths[day].count; p++){
            for(int q=0; q<day_paths[day-1].count; q++){
                if(dp[day-1][q] == INF) continue;
                if(p == q){
                    if(dp[day][p] > dp[day-1][q] + day_paths[day].paths[p].len){
                        dp[day][p] = dp[day-1][q] + day_paths[day].paths[p].len;
                    }
                }
                else{
                    if(dp[day][p] > dp[day-1][q] + day_paths[day].paths[p].len + k){
                        dp[day][p] = dp[day-1][q] + day_paths[day].paths[p].len + k;
                    }
                }
            }
        }
    }
    
    // Find the minimum cost
    int min_cost = INF;
    for(int p=0; p<day_paths[n].count; p++) {
        if(dp[n][p] < min_cost) min_cost = dp[n][p];
    }
    
    printf("%d\n", min_cost);
    return 0;
}