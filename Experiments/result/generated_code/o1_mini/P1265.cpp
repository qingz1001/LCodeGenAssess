#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(){
    int n;
    scanf("%d", &n);
    if(n == 1){
        printf("0.00\n");
        return 0;
    }
    long long x[n], y[n];
    for(int i=0;i<n;i++) scanf("%lld %lld", &x[i], &y[i]);
    bool visited[n];
    for(int i=0;i<n;i++) visited[i] = false;
    double min_dist[n];
    for(int i=0;i<n;i++){
        if(i == 0){
            min_dist[i] = 0.0;
        }
        else{
            double dx = (double)(x[i]-x[0]);
            double dy = (double)(y[i]-y[0]);
            min_dist[i] = sqrt(dx*dx + dy*dy);
        }
    }
    visited[0] = true;
    double total = 0.0;
    for(int i=1;i<n;i++){
        double min_val = 1e20;
        int u = -1;
        for(int j=0;j<n;j++) if(!visited[j] && min_dist[j] < min_val){
            min_val = min_dist[j];
            u = j;
        }
        if(u == -1) break;
        visited[u] = true;
        total += min_val;
        for(int v=0;v<n;v++) if(!visited[v]){
            double dx = (double)(x[v]-x[u]);
            double dy = (double)(y[v]-y[u]);
            double dist = sqrt(dx*dx + dy*dy);
            if(dist < min_dist[v]) min_dist[v] = dist;
        }
    }
    printf("%.2lf\n", total);
}