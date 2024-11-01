#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 20
#define MAX_N 100
#define MAX_E 200
#define MAX_DAYS 101
#define MAX_PATHS_PER_DAY 1000
#define MAX_TOTAL_PATHS 10000
#define INF 1000000000

typedef struct {
    int to;
    int length;
} Edge;

typedef struct {
    int length;
    int nodes[MAX_M + 1];
    int size;
} PathGlobal;

PathGlobal all_paths[MAX_TOTAL_PATHS];
int total_paths = 0;

int day_num_paths[MAX_DAYS];
int day_paths[MAX_DAYS][MAX_PATHS_PER_DAY];

int available[MAX_M + 1][MAX_N + 1];
Edge adj[MAX_M + 1][MAX_M + 1];
int adj_size[MAX_M + 1];

// Stack for DFS
int stack_nodes[MAX_M + 1];
int stack_size;

// Compare two paths
int compare_paths(PathGlobal *p1, PathGlobal *p2) {
    if (p1->size != p2->size)
        return 0;
    for(int i=0;i<p1->size;i++)
        if(p1->nodes[i] != p2->nodes[i])
            return 0;
    return 1;
}

// Add a path if unique, return its id
int add_path(PathGlobal *path) {
    for(int i=0;i<total_paths;i++) {
        if(compare_paths(&all_paths[i], path))
            return i;
    }
    if(total_paths >= MAX_TOTAL_PATHS) return -1;
    all_paths[total_paths] = *path;
    return total_paths++;
}

// DFS to find all simple paths from current to m on day
void dfs(int current, int m, int day, int *visited, PathGlobal *path, int *path_id) {
    if(current == m){
        // Add path
        PathGlobal temp = *path;
        int id = add_path(&temp);
        if(id != -1 && day_num_paths[day] < MAX_PATHS_PER_DAY){
            day_paths[day][day_num_paths[day]++] = id;
        }
        return;
    }
    for(int i=0;i<adj_size[current];i++){
        int neighbor = adj[current][i].to;
        if(!available[neighbor][day] || visited[neighbor]) continue;
        visited[neighbor] = 1;
        path->nodes[path->size++] = neighbor;
        path->length += adj[current][i].length;
        dfs(neighbor, m, day, visited, path, path_id);
        path->size--;
        path->length -= adj[current][i].length;
        visited[neighbor] = 0;
    }
}

int main(){
    int n, m, k, e;
    scanf("%d %d %d %d", &n, &m, &k, &e);
    // Initialize adjacency list
    for(int i=1;i<=m;i++) adj_size[i] = 0;
    for(int i=0;i<e;i++){
        int u, v, l;
        scanf("%d %d %d", &u, &v, &l);
        adj[u][adj_size[u]].to = v;
        adj[u][adj_size[u]++].length = l;
        adj[v][adj_size[v]].to = u;
        adj[v][adj_size[v]++].length = l;
    }
    // Initialize availability
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            available[i][j] = 1;
    int d;
    scanf("%d", &d);
    for(int i=0;i<d;i++){
        int p, a, b;
        scanf("%d %d %d", &p, &a, &b);
        if(a > n) continue;
        if(b > n) b = n;
        for(int day = a; day <= b; day++)
            available[p][day] = 0;
    }
    // For each day, find all paths
    for(int day=1; day<=n; day++){
        day_num_paths[day] = 0;
        // Initialize path with start node
        PathGlobal path;
        path.size = 1;
        path.nodes[0] = 1;
        path.length = 0;
        int visited[MAX_M +1];
        for(int i=1;i<=m;i++) visited[i] = 0;
        visited[1] = 1;
        dfs(1, m, day, visited, &path, NULL);
    }
    // Initialize DP
    // Use two rows for DP
    int dp_prev[MAX_TOTAL_PATHS];
    int dp_curr[MAX_TOTAL_PATHS];
    for(int i=0;i<total_paths;i++) dp_prev[i] = INF;
    for(int i=0;i<day_num_paths[1];i++){
        int pid = day_paths[1][i];
        dp_prev[pid] = all_paths[pid].length;
    }
    // Iterate through days
    for(int day=2; day<=n; day++){
        for(int i=0;i<total_paths;i++) dp_curr[i] = INF;
        for(int i=0;i<day_num_paths[day];i++){
            int pid = day_paths[day][i];
            int pl = all_paths[pid].length;
            for(int j=0;j<day_num_paths[day-1];j++){
                int qid = day_paths[day-1][j];
                if(dp_prev[qid] == INF) continue;
                if(compare_paths(&all_paths[pid], &all_paths[qid])){
                    if(dp_prev[qid] + pl < dp_curr[pid]){
                        dp_curr[pid] = dp_prev[qid] + pl;
                    }
                }
                else{
                    if(dp_prev[qid] + pl + k < dp_curr[pid]){
                        dp_curr[pid] = dp_prev[qid] + pl + k;
                    }
                }
            }
        }
        // Swap dp_prev and dp_curr
        for(int i=0;i<total_paths;i++) dp_prev[i] = dp_curr[i];
    }
    // Find minimum cost on last day
    int min_cost = INF;
    for(int i=0;i<day_num_paths[n];i++){
        int pid = day_paths[n][i];
        if(dp_prev[pid] < min_cost){
            min_cost = dp_prev[pid];
        }
    }
    printf("%d\n", min_cost);
    return 0;
}