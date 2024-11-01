#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_N 5000

typedef struct {
    double x;
    double y;
} City;

int main(){
    int n;
    scanf("%d", &n);
    City cities[MAX_N];
    for(int i=0;i<n;i++) scanf("%lf %lf", &cities[i].x, &cities[i].y);
    
    int inMST[n];
    double minDist[n];
    for(int i=0;i<n;i++) {
        inMST[i] = 0;
        minDist[i] = 1e18;
    }
    minDist[0] = 0.0;
    double total = 0.0;
    for(int i=0;i<n;i++){
        double min = 1e18;
        int u = -1;
        for(int v=0; v<n; v++) {
            if(!inMST[v] && minDist[v] < min){
                min = minDist[v];
                u = v;
            }
        }
        if(u == -1) break;
        inMST[u] = 1;
        total += min;
        for(int v=0; v<n; v++) {
            if(!inMST[v]){
                double dx = cities[u].x - cities[v].x;
                double dy = cities[u].y - cities[v].y;
                double dist = sqrt(dx*dx + dy*dy);
                if(dist < minDist[v]){
                    minDist[v] = dist;
                }
            }
        }
    }
    printf("%.2lf\n", total);
}