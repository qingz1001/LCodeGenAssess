#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_QUEUE 1000

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, k, r;
        scanf("%d %d %d", &n, &k, &r);
        
        long long w[MAX_N];
        for(int i=0;i<n;i++) scanf("%lld", &w[i]);
        
        // Build adjacency list
        int adj[MAX_N][MAX_N];
        int adj_size[MAX_N];
        for(int i=0;i<n;i++) adj_size[i] = 0;
        for(int i=0;i<n-1;i++){
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;
            adj[x][adj_size[x]++] = y;
            adj[y][adj_size[y]++] = x;
        }
        
        // Initialize coverage sets
        int coverage_set[MAX_N][MAX_N];
        int coverage_size[MAX_N];
        for(int i=0;i<n;i++) coverage_size[i] = 0;
        
        // Initialize covered_by
        int covered_by[MAX_N][MAX_N];
        int covered_by_size[MAX_N];
        for(int i=0;i<n;i++) covered_by_size[i] = 0;
        
        // Perform BFS for each node
        for(int u=0;u<n;u++){
            int visited[MAX_N];
            memset(visited, 0, sizeof(visited));
            int queue[MAX_QUEUE];
            int front = 0, rear = 0;
            queue[rear++] = u;
            visited[u] = 1;
            int distance = 0;
            int current_level = 1;
            int next_level = 0;
            while(front < rear && distance <= r){
                int v = queue[front++];
                coverage_set[u][coverage_size[u]++] = v;
                for(int i=0;i<adj_size[v];i++){
                    int nei = adj[v][i];
                    if(!visited[nei]){
                        visited[nei] = 1;
                        queue[rear++] = nei;
                        next_level++;
                    }
                }
                current_level--;
                if(current_level == 0){
                    distance++;
                    current_level = next_level;
                    next_level = 0;
                }
            }
            // Populate covered_by
            for(int i=0;i<coverage_size[u];i++){
                int v = coverage_set[u][i];
                covered_by[v][covered_by_size[v]++] = u;
            }
        }
        
        // Initialize coverage_sum
        long long coverage_sum[MAX_N];
        for(int u=0;u<n;u++){
            coverage_sum[u] = 0;
            for(int i=0;i<coverage_size[u];i++) coverage_sum[u] += w[coverage_set[u][i]];
        }
        
        // Initialize covered array
        int covered[MAX_N];
        memset(covered, 0, sizeof(covered));
        
        long long total_sum = 0;
        
        for(int step=0; step<k; step++){
            // Find the node with maximum coverage_sum
            long long max_sum = 0;
            int select_node = -1;
            for(int u=0; u<n; u++){
                if(coverage_sum[u] > max_sum){
                    max_sum = coverage_sum[u];
                    select_node = u;
                }
            }
            if(max_sum == 0 || select_node == -1) break;
            total_sum += max_sum;
            
            // Mark covered nodes and update coverage_sum
            for(int i=0;i<coverage_size[select_node];i++){
                int v = coverage_set[select_node][i];
                if(!covered[v]){
                    covered[v] = 1;
                    for(int j=0; j<covered_by_size[v]; j++){
                        int node = covered_by[v][j];
                        coverage_sum[node] -= w[v];
                    }
                }
            }
        }
        
        printf("%lld\n", total_sum);
    }
    return 0;
}