#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 50001
#define MOD 10000

typedef unsigned long long ull;

int adj_f_to[MAXM], adj_f_time[MAXM], adj_f_size_array[MAXN];
int adj_r_to[MAXM], adj_r_time[MAXM], adj_r_size_array[MAXN];
int topo_order[MAXN];
int queue_nodes[MAXN];
int in_degree_array[MAXN];
ull paths_s_to_arr[MAXN];
ull paths_t_from_arr[MAXN];

int main(){
    int n, m, s, t, t0;
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);
    
    // Initialize adjacency sizes
    for(int i=1;i<=n;i++){
        adj_f_size_array[i] = 0;
        adj_r_size_array[i] = 0;
        in_degree_array[i] = 0;
        paths_s_to_arr[i] = 0;
        paths_t_from_arr[i] = 0;
    }
    
    // Read edges
    for(int i=0;i<m;i++){
        int x, y, te;
        scanf("%d %d %d", &x, &y, &te);
        adj_f_to[adj_f_size_array[x]] = y;
        adj_f_time[x * MAXM + adj_f_size_array[x]] = te;
        adj_f_size_array[x]++;
        
        adj_r_to[adj_r_size_array[y]] = x;
        adj_r_time[y * MAXM + adj_r_size_array[y]] = te;
        adj_r_size_array[y]++;
        
        in_degree_array[y]++;
    }
    
    // Kahn's algorithm for topological sort
    int head = 0, tail = 0;
    for(int i=1;i<=n;i++){
        if(in_degree_array[i]==0){
            queue_nodes[tail++] = i;
        }
    }
    
    int index = 0;
    while(head < tail){
        int u = queue_nodes[head++];
        topo_order[index++] = u;
        for(int i=0;i<adj_f_size_array[u];i++){
            int v = adj_f_to[u];
            v = adj_f_to[u];
            // Calculate the actual index in adj_f_to and adj_f_time
            // Since multiple edges can exist, iterate through all
            for(int j=0; j<adj_f_size_array[u]; j++){
                v = adj_f_to[u * MAXM + j];
                in_degree_array[v]--;
                if(in_degree_array[v]==0){
                    queue_nodes[tail++] = v;
                }
            }
        }
    }
    
    // Reset in_degree_array for accurate topological order
    for(int i=0;i<m;i++) {
        // Already handled in the loop above
    }
    
    // Reconstruct topological order correctly
    // Reinitialize in_degree_array
    for(int i=1;i<=n;i++){
        in_degree_array[i] = 0;
    }
    // Recompute in_degree_array
    for(int u=1; u<=n; u++){
        for(int j=0; j<adj_f_size_array[u]; j++){
            int v = adj_f_to[u * MAXM + j];
            in_degree_array[v]++;
        }
    }
    
    // Perform Kahn's algorithm correctly
    head = 0;
    tail = 0;
    for(int i=1;i<=n;i++){
        if(in_degree_array[i]==0){
            queue_nodes[tail++] = i;
        }
    }
    index = 0;
    while(head < tail){
        int u = queue_nodes[head++];
        topo_order[index++] = u;
        for(int j=0; j<adj_f_size_array[u]; j++){
            int v = adj_f_to[u * MAXM + j];
            in_degree_array[v]--;
            if(in_degree_array[v]==0){
                queue_nodes[tail++] = v;
            }
        }
    }
    
    // Compute paths from s
    paths_s_to_arr[s] = 1;
    for(int i=0;i<n;i++){
        int u = topo_order[i];
        for(int j=0; j<adj_f_size_array[u]; j++){
            int v = adj_f_to[u * MAXM + j];
            paths_s_to_arr[v] += paths_s_to_arr[u];
        }
    }
    
    // Compute paths to t
    paths_t_from_arr[t] = 1;
    for(int i=n-1;i>=0;i--){
        int u = topo_order[i];
        for(int j=0; j<adj_f_size_array[u]; j++){
            int v = adj_f_to[u * MAXM + j];
            paths_t_from_arr[u] += paths_t_from_arr[v];
        }
    }
    
    // Compute sum_over_e
    ull sum = 0;
    for(int u=1; u<=n; u++){
        for(int j=0; j<adj_f_size_array[u]; j++){
            int v = adj_f_to[u * MAXM + j];
            int te = adj_f_time[u * MAXM + j];
            sum += (ull)te * paths_s_to_arr[u] * paths_t_from_arr[v];
            sum %= MOD;
        }
    }
    
    // Compute total
    ull k = paths_s_to_arr[t];
    ull total = (sum + ((ull)t0 * k) % MOD + MOD - t0) % MOD;
    printf("%llu", total);
    return 0;
}