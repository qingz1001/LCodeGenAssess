#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

int main(){
    int n;
    scanf("%d", &n);
    int w[MAX], left_child[MAX], right_child[MAX];
    memset(w, 0, sizeof(w));
    memset(left_child, 0, sizeof(left_child));
    memset(right_child, 0, sizeof(right_child));
    
    // Read node information
    for(int i=1;i<=n;i++){
        int wi, u, v;
        scanf("%d %d %d", &wi, &u, &v);
        w[i] = wi;
        left_child[i] = u;
        right_child[i] = v;
    }
    
    // Build adjacency list
    int adj[MAX][MAX];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) adj[i][j] = 0;
    }
    for(int i=1;i<=n;i++){
        if(left_child[i]!=0){
            adj[i][left_child[i]] = 1;
            adj[left_child[i]][i] = 1;
        }
        if(right_child[i]!=0){
            adj[i][right_child[i]] = 1;
            adj[right_child[i]][i] = 1;
        }
    }
    
    // Function to perform BFS and calculate distances
    // Since n is small, we can do it inline
    long long min_sum = -1;
    for(int hospital=1;hospital<=n;hospital++){
        int visited[MAX];
        int dist[MAX];
        memset(visited, 0, sizeof(visited));
        for(int i=1;i<=n;i++) dist[i] = -1;
        // Initialize queue
        int queue[MAX], front=0, rear=0;
        queue[rear++] = hospital;
        visited[hospital] = 1;
        dist[hospital] = 0;
        while(front < rear){
            int current = queue[front++];
            for(int neighbor=1;neighbor<=n;neighbor++){
                if(adj[current][neighbor] && !visited[neighbor]){
                    visited[neighbor] = 1;
                    dist[neighbor] = dist[current] + 1;
                    queue[rear++] = neighbor;
                }
            }
        }
        // Calculate sum
        long long sum = 0;
        for(int i=1;i<=n;i++) {
            if(dist[i] != -1){
                sum += (long long)w[i] * dist[i];
            }
        }
        if(min_sum == -1 || sum < min_sum){
            min_sum = sum;
        }
    }
    printf("%lld\n", min_sum);
    return 0;
}