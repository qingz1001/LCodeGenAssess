#include <stdio.h>
#include <math.h>

#define MAX 101
#define INF 1e18

int main(){
    int n, m, i, j, s, t;
    int x[MAX], y[MAX];
    double adj[MAX][MAX];
    double dist[MAX];
    int visited[MAX];

    // Initialize adjacency matrix
    for(i=1;i<=100;i++){
        for(j=1;j<=100;j++){
            adj[i][j] = INF;
        }
    }

    // Read number of nodes
    scanf("%d", &n);

    // Read coordinates
    for(i=1;i<=n;i++){
        scanf("%d %d", &x[i], &y[i]);
    }

    // Read number of edges
    scanf("%d", &m);

    // Read edges and compute distances
    for(i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        double dx = (double)(x[u] - x[v]);
        double dy = (double)(y[u] - y[v]);
        double distance = sqrt(dx*dx + dy*dy);
        if(distance < adj[u][v]){
            adj[u][v] = distance;
            adj[v][u] = distance;
        }
    }

    // Read start and end nodes
    scanf("%d %d", &s, &t);

    // Initialize distances and visited
    for(i=1;i<=n;i++){
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[s] = 0.0;

    // Dijkstra's algorithm
    for(i=1;i<=n;i++){
        double min_dist = INF;
        int u = -1;
        for(j=1;j<=n;j++){
            if(!visited[j] && dist[j] < min_dist){
                min_dist = dist[j];
                u = j;
            }
        }
        if(u == -1 || u == t){
            break;
        }
        visited[u] = 1;
        for(j=1;j<=n;j++){
            if(adj[u][j] < INF && !visited[j]){
                if(dist[u] + adj[u][j] < dist[j]){
                    dist[j] = dist[u] + adj[u][j];
                }
            }
        }
    }

    // Print the result
    printf("%.2lf\n", dist[t]);
    return 0;
}