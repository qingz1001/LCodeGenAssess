#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10001
#define MAXM 20001
#define MAXQUEUE 10001

int adj[MAXN][20];
int degree_arr[MAXN];
int color_arr[MAXN];
int queue_arr[MAXQUEUE];

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m;
        scanf("%d %d", &n, &m);
        // Initialize degrees
        for(int i=1;i<=n;i++) degree_arr[i]=0;
        // Read edges
        for(int i=0;i<m;i++){
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u][degree_arr[u]++] = v;
            adj[v][degree_arr[v]++] = u;
        }
        // Initialize colors
        for(int i=1;i<=n;i++) color_arr[i] = -1;
        int is_bip = 1;
        for(int i=1;i<=n && is_bip;i++){
            if(color_arr[i]==-1){
                // BFS
                int front=0, rear=0;
                queue_arr[rear++] = i;
                color_arr[i] = 0;
                while(front < rear && is_bip){
                    int u = queue_arr[front++];
                    for(int j=0; j<degree_arr[u] && is_bip; j++){
                        int v = adj[u][j];
                        if(color_arr[v]==-1){
                            color_arr[v] = color_arr[u]^1;
                            queue_arr[rear++] = v;
                        }
                        else if(color_arr[v] == color_arr[u]){
                            is_bip = 0;
                        }
                    }
                }
            }
        }
        if(is_bip) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}