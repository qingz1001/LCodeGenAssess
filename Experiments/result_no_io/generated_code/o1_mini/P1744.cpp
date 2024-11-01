#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAXN 101
#define INF 1e18

int main(){
    int n;
    scanf("%d", &n);
    double x[MAXN], y[MAXN];
    for(int i=1;i<=n;i++) scanf("%lf %lf", &x[i], &y[i]);
    double adj[MAXN][MAXN];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            adj[i][j] = INF;
        }
    }
    int m;
    scanf("%d", &m);
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        double dist = sqrt((x[u]-x[v])*(x[u]-x[v]) + (y[u]-y[v])*(y[u]-y[v]));
        if(dist < adj[u][v]){
            adj[u][v] = dist;
            adj[v][u] = dist;
        }
    }
    int s, t;
    scanf("%d %d", &s, &t);
    double distance_val[MAXN];
    bool visited[MAXN] = {false};
    for(int i=1;i<=n;i++) distance_val[i] = INF;
    distance_val[s] = 0.0;
    for(int i=1;i<=n;i++){
        double min_dist = INF;
        int u = -1;
        for(int v=1;v<=n;v++) {
            if(!visited[v] && distance_val[v] < min_dist){
                min_dist = distance_val[v];
                u = v;
            }
        }
        if(u == -1) break;
        visited[u] = true;
        for(int v=1;v<=n;v++){
            if(adj[u][v] < INF && !visited[v]){
                if(distance_val[u] + adj[u][v] < distance_val[v]){
                    distance_val[v] = distance_val[u] + adj[u][v];
                }
            }
        }
    }
    printf("%.2lf\n", distance_val[t]);
    return 0;
}