#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10005
#define MAXM 200010
#define INF 1000000000

struct Edge {
    int to;
    int next;
} edges[MAXM];
int head[MAXN];
int edge_cnt = 0;

void add_edge(int u, int v){
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

int color_arr[MAXN];
int is_bipartite = 1;
int queue_nodes[MAXN];
int front, rear;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    memset(color_arr, -1, sizeof(color_arr));
    for(int i=1;i<=n && is_bipartite;i++){
        if(color_arr[i]==-1){
            front = rear =0;
            queue_nodes[rear++] = i;
            color_arr[i] =0;
            while(front < rear && is_bipartite){
                int u = queue_nodes[front++];
                for(int e = head[u]; e != -1; e = edges[e].next){
                    int v = edges[e].to;
                    if(color_arr[v]==-1){
                        color_arr[v] = color_arr[u]^1;
                        queue_nodes[rear++] = v;
                    }
                    else if(color_arr[v] == color_arr[u]){
                        is_bipartite = 0;
                        break;
                    }
                }
            }
        }
    }
    if(!is_bipartite){
        printf("Impossible\n");
        return 0;
    }
    // Prepare for Hopcroft-Karp
    // Left set: color 0
    // Right set: color 1
    int left_size =0, right_size=0;
    int left[MAXN];
    int right[MAXN];
    for(int i=1;i<=n;i++){
        if(color_arr[i]==0){
            left[left_size++] = i;
        }
        else{
            right[right_size++] = i;
        }
    }
    // Build adjacency list for left
    int adj_left[left_size][MAXN];
    int adj_count[left_size];
    for(int i=0;i<left_size;i++) adj_count[i]=0;
    for(int i=0;i<left_size;i++){
        int u = left[i];
        for(int e = head[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            adj_left[i][adj_count[i]++] = v;
        }
    }
    // Initialize matching
    int pair_u[left_size];
    int pair_v[right_size];
    for(int i=0;i<left_size;i++) pair_u[i] = -1;
    for(int i=0;i<right_size;i++) pair_v[i] = -1;
    // BFS layers
    int dist[left_size];
    int queue_hk[left_size];
    while(1){
        // BFS
        int qh =0, qt=0;
        for(int i=0;i<left_size;i++) {
            if(pair_u[i]==-1){
                dist[i] =0;
                queue_hk[qt++] = i;
            }
            else{
                dist[i] = INF;
            }
        }
        int dist_found = INF;
        while(qh < qt){
            int u = queue_hk[qh++];
            if(dist[u] < dist_found){
                for(int j=0; j<adj_count[u]; j++){
                    int v = adj_left[u][j];
                    // Find index of v in right
                    int v_idx = -1;
                    for(int k=0;k<right_size;k++) if(right[k]==v){v_idx = k; break;}
                    if(v_idx == -1) continue;
                    if(pair_v[v_idx]==-1){
                        dist_found = dist[u] +1;
                    }
                    else{
                        int u2 = -1;
                        for(int k=0;k<left_size;k++) if(left[k]==pair_v[v_idx]){u2 = k; break;}
                        if(u2 != -1 && dist[u2]==INF){
                            dist[u2] = dist[u] +1;
                            queue_hk[qt++] = u2;
                        }
                    }
                }
            }
        }
        if(dist_found == INF) break;
        // DFS
        int stack_size =0;
        int stack[left_size];
        for(int i=0;i<left_size;i++) {
            if(pair_u[i]==-1){
                stack[stack_size++] = i;
            }
        }
        // Simplified BFS-based Hopcroft-Karp
        // Actual implementation would require a proper BFS and DFS layering
        break; // Not implementing full Hopcroft-Karp due to complexity
    }
    // Instead, implement standard Hopcroft-Karp with BFS and DFS
    // Reinitialize
    // Rebuild adjacency list for left
    int *adj_hk[left_size];
    int adj_len[left_size];
    for(int i=0;i<left_size;i++) adj_len[i]=0;
    for(int i=0;i<left_size;i++){
        for(int j=0; j<adj_count[i]; j++) adj_len[i]++;
    }
    // Allocate memory
    int *g[left_size];
    for(int i=0;i<left_size;i++) g[i] = malloc(adj_len[i]*sizeof(int));
    for(int i=0;i<left_size;i++){
        int idx=0;
        for(int j=0; j<adj_count[i]; j++) g[i][idx++] = adj_left[i][j];
    }
    // Initialize matching
    for(int i=0;i<left_size;i++) pair_u[i] = -1;
    for(int i=0;i<right_size;i++) pair_v[i] = -1;
    // Initialize distance
    int level[left_size];
    // BFS function
    int hop_bfs(){
        int qh=0, qt=0;
        for(int i=0;i<left_size;i++){
            if(pair_u[i]==-1){
                level[i]=0;
                queue_hk[qt++] = i;
            }
            else{
                level[i]=INF;
            }
        }
        int found =0;
        while(qh < qt){
            int u = queue_hk[qh++];
            if(level[u] < dist_found){
                for(int j=0; j<adj_len[u]; j++){
                    int v = g[u][j];
                    int v_idx = -1;
                    for(int k=0;k<right_size;k++) if(right[k]==v){v_idx = k; break;}
                    if(v_idx == -1) continue;
                    if(pair_v[v_idx]==-1){
                        found =1;
                    }
                    else{
                        int u2 = -1;
                        for(int k=0;k<left_size;k++) if(left[k]==pair_v[v_idx]){u2 = k; break;}
                        if(u2 != -1 && level[u2]==INF){
                            level[u2] = level[u] +1;
                            queue_hk[qt++] = u2;
                        }
                    }
                }
            }
        }
        return found;
    }
    // DFS function
    int hop_dfs(int u){
        for(int j=0; j<adj_len[u]; j++){
            int v = g[u][j];
            int v_idx = -1;
            for(int k=0;k<right_size;k++) if(right[k]==v){v_idx = k; break;}
            if(v_idx == -1) continue;
            if(pair_v[v_idx]==-1 || (level[pair_v[v_idx]] == level[u]+1 && hop_dfs(pair_v[v_idx]))){
                pair_u[u] = v_idx;
                pair_v[v_idx] = u;
                return 1;
            }
        }
        level[u] = INF;
        return 0;
    }
    // Hopcroft-Karp main loop
    int matching =0;
    while(1){
        // BFS to set levels
        int qh =0, qt=0;
        for(int i=0;i<left_size;i++){
            if(pair_u[i]==-1){
                level[i]=0;
                queue_hk[qt++] = i;
            }
            else{
                level[i]=INF;
            }
        }
        int dist_found = INF;
        while(qh < qt){
            int u = queue_hk[qh++];
            if(level[u] < dist_found){
                for(int j=0; j<adj_len[u]; j++){
                    int v = g[u][j];
                    int v_idx = -1;
                    for(int k=0;k<right_size;k++) if(right[k]==v){v_idx = k; break;}
                    if(v_idx == -1) continue;
                    if(pair_v[v_idx]==-1){
                        dist_found = level[u] +1;
                    }
                    else{
                        int u2 = pair_v[v_idx];
                        if(level[u2]==INF){
                            level[u2] = level[u] +1;
                            queue_hk[qt++] = u2;
                        }
                    }
                }
            }
        }
        if(dist_found == INF) break;
        // DFS to find augmenting paths
        for(int i=0;i<left_size;i++){}
        // Implement DFS for each free node
        for(int i=0;i<left_size;i++){
            if(pair_u[i]==-1){
                if(hop_dfs(i)){
                    matching++;
                }
            }
        }
    }
    printf("%d\n", matching);
    return 0;
}