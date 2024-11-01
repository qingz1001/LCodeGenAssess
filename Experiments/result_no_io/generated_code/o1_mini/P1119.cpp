#include <stdio.h>
#include <stdlib.h>

#define MAXN 200
#define MAXM 19900
#define INF 100000000

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    int t[MAXN];
    for(int i=0;i<N;i++) scanf("%d", &t[i]);
    
    // Initialize road lists
    int road_to[MAXN][MAXN];
    int roads_w[MAXN][MAXN];
    int road_count[MAXN];
    for(int i=0;i<N;i++) road_count[i] = 0;
    
    for(int i=0;i<M;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        road_to[u][road_count[u]] = v;
        roads_w[u][road_count[u]] = w;
        road_count[u]++;
        road_to[v][road_count[v]] = u;
        roads_w[v][road_count[v]] = w;
        road_count[v]++;
    }
    
    // Initialize distance matrix
    int d[MAXN][MAXN];
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(i == j) d[i][j] = 0;
            else d[i][j] = INF;
        }
    }
    
    // Initialize distance_steps
    int distance_steps[MAXN][MAXN][MAXN];
    for(int s=0;s<N;s++){
        int k = s;
        // Update roads connected to k
        for(int m=0;m < road_count[k];m++){
            int j = road_to[k][m];
            int w = roads_w[k][m];
            if(j <= s && w < d[k][j]){
                d[k][j] = w;
                d[j][k] = w;
            }
        }
        // Floyd-Warshall update for the new node k
        for(int i=0;i<=s;i++){
            for(int j=0;j<=s;j++){
                if(d[i][k] + d[k][j] < d[i][j]){
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
        // Copy current distances to distance_steps
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i <= s && j <= s){
                    distance_steps[s][i][j] = d[i][j];
                }
                else{
                    distance_steps[s][i][j] = INF;
                }
            }
        }
    }
    
    int Q;
    scanf("%d", &Q);
    
    int current_step = -1;
    for(int q=0; q<Q; q++){
        int x, y, query_t;
        scanf("%d %d %d", &x, &y, &query_t);
        
        // Advance the current_step based on query_t
        while(current_step +1 < N && t[current_step +1] <= query_t){
            current_step++;
        }
        
        if(current_step >=0 && x <= current_step && y <= current_step && t[x] <= query_t && t[y] <= query_t){
            int ans = distance_steps[current_step][x][y];
            if(ans < INF){
                printf("%d\n", ans);
            }
            else{
                printf("-1\n");
            }
        }
        else{
            printf("-1\n");
        }
    }
    
    return 0;
}