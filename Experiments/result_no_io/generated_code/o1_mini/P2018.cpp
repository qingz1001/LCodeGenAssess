#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001

int adj[MAXN][MAXN];
int adj_size[MAXN];
int queue_q[MAXN];
int dist_arr[MAXN];
int visited[MAXN];

int main(){
    int N;
    scanf("%d", &N);
    
    // Initialize adjacency list
    for(int i=1;i<=N;i++) adj_size[i]=0;
    
    // Read parents and build undirected edges
    for(int i=2;i<=N;i++){
        int parent;
        scanf("%d", &parent);
        adj[i][adj_size[i]++] = parent;
        adj[parent][adj_size[parent]++] = i;
    }
    
    int min_time = N;
    int candidates[MAXN];
    int cand_count = 0;
    
    for(int start=1; start<=N; start++){
        memset(visited, 0, sizeof(visited));
        memset(dist_arr, 0, sizeof(dist_arr));
        int front=0, rear=0;
        queue_q[rear++] = start;
        visited[start] = 1;
        dist_arr[start] = 0;
        int max_dist = 0;
        
        while(front < rear){
            int current = queue_q[front++];
            for(int i=0;i<adj_size[current];i++){
                int neighbor = adj[current][i];
                if(!visited[neighbor]){
                    visited[neighbor] = 1;
                    dist_arr[neighbor] = dist_arr[current] + 1;
                    if(dist_arr[neighbor] > max_dist) max_dist = dist_arr[neighbor];
                    queue_q[rear++] = neighbor;
                }
            }
        }
        
        if(max_dist < min_time){
            min_time = max_dist;
            cand_count = 0;
            candidates[cand_count++] = start;
        }
        else if(max_dist == min_time){
            candidates[cand_count++] = start;
        }
    }
    
    printf("%d\n", min_time);
    for(int i=0;i<cand_count;i++){
        if(i>0) printf(" ");
        printf("%d", candidates[i]);
    }
    printf("\n");
    
    return 0;
}