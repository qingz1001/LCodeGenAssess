#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_M 200
#define MAX_N 200
#define MAX_SEGMENTS 40000
#define MAX_EDGES 800000

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

int m, n;
int grid[201][201];
int h_segment[201][201];
int v_segment[201][201];
int h_id_total = 0, v_id_total = 0;

// For Hopcroft-Karp
Edge* graph[MAX_SEGMENTS + 1];
int pair_left[MAX_SEGMENTS + 1];
int pair_right[MAX_SEGMENTS + 1];
int dist_left[MAX_SEGMENTS + 1];
int queue_arr[MAX_SEGMENTS + 1];
int front, rear;

bool bfs() {
    int i, u;
    bool found = false;
    for (i = 1; i <= h_id_total; i++) {
        if (pair_left[i] == 0) {
            dist_left[i] = 0;
            queue_arr[rear++] = i;
        }
        else {
            dist_left[i] = -1;
        }
    }
    dist_left[0] = -1;
    while (front < rear) {
        u = queue_arr[front++];
        if (u != 0) {
            Edge* edge = graph[u];
            while (edge != NULL) {
                int v = edge->to;
                if (pair_right[v] != 0 && dist_left[pair_right[v]] == -1) {
                    dist_left[pair_right[v]] = dist_left[u] + 1;
                    queue_arr[rear++] = pair_right[v];
                }
                else if (pair_right[v] == 0) {
                    found = true;
                }
                edge = edge->next;
            }
        }
    }
    return found;
}

bool dfs(int u) {
    if (u != 0) {
        Edge* edge = graph[u];
        while (edge != NULL) {
            int v = edge->to;
            if (pair_right[v] == 0 || (dist_left[pair_right[v]] == dist_left[u] + 1 && dfs(pair_right[v]))) {
                pair_left[u] = v;
                pair_right[v] = u;
                return true;
            }
            edge = edge->next;
        }
        dist_left[u] = -1;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    memset(pair_left, 0, sizeof(pair_left));
    memset(pair_right, 0, sizeof(pair_right));
    int matching = 0;
    while (bfs()) {
        for (int u = 1; u <= h_id_total; u++) {
            if (pair_left[u] == 0) {
                if (dfs(u)) {
                    matching++;
                }
            }
        }
    }
    return matching;
}

int main(){
    scanf("%d %d", &m, &n);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            scanf("%d", &grid[i][j]);
        }
    }
    // Assign horizontal segments
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(grid[i][j] !=2){
                if(j ==1 || grid[i][j-1]==2){
                    h_id_total++;
                }
                h_segment[i][j] = h_id_total;
            }
            else{
                h_segment[i][j] = 0;
            }
        }
    }
    // Assign vertical segments
    for(int j=1;j<=n;j++){
        for(int i=1;i<=m;i++){
            if(grid[i][j] !=2){
                if(i ==1 || grid[i-1][j]==2){
                    v_id_total++;
                }
                v_segment[i][j] = v_id_total;
            }
            else{
                v_segment[i][j] = 0;
            }
        }
    }
    // Initialize graph
    for(int i=1;i<=h_id_total;i++) graph[i] = NULL;
    // Build adjacency list
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(grid[i][j]==0){
                int h = h_segment[i][j];
                int v = v_segment[i][j];
                Edge* new_edge = (Edge*)malloc(sizeof(Edge));
                new_edge->to = v;
                new_edge->next = graph[h];
                graph[h] = new_edge;
            }
        }
    }
    // Run Hopcroft-Karp
    int max_matching = hopcroft_karp();
    // Collect matching positions
    int k = max_matching;
    printf("%d\n", k);
    bool used[MAX_SEGMENTS +1];
    memset(used, false, sizeof(used));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(grid[i][j]==0){
                int h = h_segment[i][j];
                int v = v_segment[i][j];
                if(pair_left[h] == v && !used[h]){
                    printf("%d %d\n", i, j);
                    used[h] = true;
                }
            }
        }
    }
    // Free memory
    for(int i=1;i<=h_id_total;i++){
        Edge* edge = graph[i];
        while(edge != NULL){
            Edge* tmp = edge;
            edge = edge->next;
            free(tmp);
        }
    }
    return 0;
}