#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define INF 100000000000LL

long long distance_matrix_steps[MAXN][MAXN][MAXN];
long long distance_current[MAXN][MAXN];
int adj_matrix[MAXN][MAXN];
int t_i[MAXN];
int N, M, Q;

int main(){
    // Initialize adj_matrix to INF
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            adj_matrix[i][j] = -1;
        }
    }
    // Read N and M
    scanf("%d %d", &N, &M);
    // Read t_i
    for(int i=0;i<N;i++) scanf("%d", &t_i[i]);
    // Read M roads
    for(int i=0;i<M;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj_matrix[u][v] = w;
        adj_matrix[v][u] = w;
    }
    // Initialize distance_current to INF
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            distance_current[i][j] = INF;
        }
    }
    // Perform incremental Floyd-Warshall
    for(int s=0;s<N;s++){
        // Add roads from s to already added nodes
        for(int j=0;j<s;j++){
            if(adj_matrix[s][j] != -1){
                if(adj_matrix[s][j] < distance_current[s][j]){
                    distance_current[s][j] = adj_matrix[s][j];
                    distance_current[j][s] = adj_matrix[s][j];
                }
            }
        }
        // Set distance[s][s] = 0
        distance_current[s][s] = 0;
        // Update distances using node s
        for(int i=0;i<=s;i++){
            for(int j=0;j<=s;j++){
                if(distance_current[i][s] + distance_current[s][j] < distance_current[i][j]){
                    distance_current[i][j] = distance_current[i][s] + distance_current[s][j];
                }
            }
        }
        // Copy current distance to distance_matrix_steps[s][i][j]
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i <=s && j <=s){
                    distance_matrix_steps[s][i][j] = distance_current[i][j];
                }
                else{
                    distance_matrix_steps[s][i][j] = INF;
                }
            }
        }
    }
    // Read Q
    scanf("%d", &Q);
    // Process queries
    for(int q=0; q<Q; q++){
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        // Binary search for the last s where t_i[s] <= t
        int left=0, right=N-1, ans=-1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(t_i[mid] <= t){
                ans = mid;
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        if(ans == -1 || t_i[x] > t || t_i[y] > t){
            printf("-1\n");
            continue;
        }
        long long result = distance_matrix_steps[ans][x][y];
        if(result < INF){
            printf("%lld\n", result);
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}