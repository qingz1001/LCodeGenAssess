#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 502
#define MAX_M 2004
#define MAX_QUEUE 502

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m;
        scanf("%d %d", &n, &m);
        // Initialize adjacency list
        int adj[MAX_N][MAX_M];
        int adj_size[MAX_N];
        for(int i=1;i<=n;i++) adj_size[i]=0;
        // Initialize degrees
        int degree[MAX_N];
        for(int i=1;i<=n;i++) degree[i]=0;
        // Read edges
        for(int i=0;i<m;i++){
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u][adj_size[u]++] = v;
            adj[v][adj_size[v]++] = u;
            degree[u]++;
            degree[v]++;
        }
        // Initialize queue
        int queue[MAX_QUEUE];
        int front=0, rear=0;
        int removed[MAX_N];
        memset(removed, 0, sizeof(removed));
        for(int i=1;i<=n;i++) {
            if(degree[i] <=2){
                queue[rear++] = i;
            }
        }
        int count=0;
        while(front < rear){
            int v = queue[front++];
            if(removed[v]) continue;
            removed[v] =1;
            count++;
            for(int i=0;i<adj_size[v];i++){
                int u = adj[v][i];
                if(!removed[u]){
                    degree[u]--;
                    if(degree[u] ==2){
                        queue[rear++] = u;
                    }
                }
            }
        }
        if(count ==n){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
    return 0;
}