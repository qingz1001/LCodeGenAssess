#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAXN 150
#define INF 1e18

int main(){
    int N;
    scanf("%d", &N);
    double coords[MAXN][2];
    for(int i=0;i<N;i++) scanf("%lf %lf", &coords[i][0], &coords[i][1]);
    int adj[MAXN][MAXN];
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            scanf("%d", &adj[i][j]);
        }
    }
    double dist[MAXN][MAXN];
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(i == j){
                dist[i][j] = 0.0;
            }
            else if(adj[i][j]){
                double dx = coords[i][0] - coords[j][0];
                double dy = coords[i][1] - coords[j][1];
                dist[i][j] = sqrt(dx*dx + dy*dy);
            }
            else{
                dist[i][j] = INF;
            }
        }
    }
    // Floyd-Warshall
    for(int k=0;k<N;k++) {
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    // Find components
    int component[MAXN];
    memset(component, -1, sizeof(component));
    int current = 0;
    for(int i=0;i<N;i++) {
        if(component[i]==-1){
            // BFS
            int queue[MAXN], front=0, back=0;
            queue[back++] = i;
            component[i] = current;
            while(front < back){
                int u = queue[front++];
                for(int v=0;v<N;v++) {
                    if(adj[u][v] && component[v]==-1){
                        component[v] = current;
                        queue[back++] = v;
                    }
                }
            }
            current++;
        }
    }
    int num_components = current;
    // Compute eccentricity
    double ecc[MAXN];
    for(int i=0;i<N;i++) {
        double maxd = 0.0;
        for(int j=0;j<N;j++) {
            if(component[j]==component[i] && dist[i][j] < INF){
                if(dist[i][j] > maxd) maxd = dist[i][j];
            }
        }
        ecc[i] = maxd;
    }
    // Compute existing diameters
    double diameters[MAXN];
    for(int c=0;c<num_components;c++) {
        diameters[c] = 0.0;
        for(int i=0;i<N;i++) {
            if(component[i]==c){
                if(ecc[i] > diameters[c]) diameters[c] = ecc[i];
            }
        }
    }
    // Find minimal new diameter
    double min_new_diameter = INF;
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(component[i] != component[j]){
                double dx = coords[i][0] - coords[j][0];
                double dy = coords[i][1] - coords[j][1];
                double connect_dist = sqrt(dx*dx + dy*dy);
                double potential_diameter = 0.0;
                // Maximum existing diameter
                for(int c=0;c<num_components;c++) {
                    if(diameters[c] > potential_diameter) potential_diameter = diameters[c];
                }
                // New possible diameter
                double new_d = ecc[i] + connect_dist + ecc[j];
                if(new_d > potential_diameter) potential_diameter = new_d;
                if(potential_diameter < min_new_diameter){
                    min_new_diameter = potential_diameter;
                }
            }
        }
    }
    printf("%.6lf\n", min_new_diameter);
}