#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAXN 150
#define INF 1e18

int main(){
    int N;
    scanf("%d", &N);
    double x[MAXN], y[MAXN];
    for(int i=0;i<N;i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    char line[MAXN+2];
    double dist[MAXN][MAXN];
    for(int i=0;i<N;i++) {
        scanf("%s", line);
        for(int j=0;j<N;j++) {
            if(line[j] == '1') {
                double dx = x[i] - x[j];
                double dy_ = y[i] - y[j];
                dist[i][j] = sqrt(dx*dx + dy_*dy_);
            }
            else{
                dist[i][j] = (i == j) ? 0.0 : INF;
            }
        }
    }
    // Floyd-Warshall
    for(int k=0;k<N;k++) {
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                if(dist[i][k] < INF && dist[k][j] < INF){
                    if(dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    // Assign components
    int component[MAXN];
    for(int i=0;i<N;i++) component[i] = -1;
    int current_component = 0;
    for(int i=0;i<N;i++) {
        if(component[i] == -1){
            component[i] = current_component;
            for(int j=0;j<N;j++) {
                if(dist[i][j] < INF){
                    component[j] = current_component;
                }
            }
            current_component++;
        }
    }
    // Compute max_dist for each node
    double max_dist[MAXN];
    for(int i=0;i<N;i++) {
        max_dist[i] = 0.0;
        for(int j=0;j<N;j++) {
            if(component[j] == component[i] && dist[i][j] < INF){
                if(dist[i][j] > max_dist[i]){
                    max_dist[i] = dist[i][j];
                }
            }
        }
    }
    // Compute existing diameters
    double existing_max_diameter = 0.0;
    for(int i=0;i<N;i++) {
        if(max_dist[i] > existing_max_diameter){
            existing_max_diameter = max_dist[i];
        }
    }
    // Find minimal possible new diameter
    double minimal_new_diameter = INF;
    for(int u=0; u<N; u++) {
        for(int v=0; v<N; v++) {
            if(component[u] != component[v]){
                double dx = x[u] - x[v];
                double dy_ = y[u] - y[v];
                double connect_dist = sqrt(dx*dx + dy_*dy_);
                double temp_diameter = fmax(existing_max_diameter, max_dist[u] + connect_dist + max_dist[v]);
                if(temp_diameter < minimal_new_diameter){
                    minimal_new_diameter = temp_diameter;
                }
            }
        }
    }
    printf("%.6lf\n", minimal_new_diameter);
    return 0;
}