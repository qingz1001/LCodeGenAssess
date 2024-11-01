#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAXN 51
#define MAXM 1000
#define INF 1e18

typedef struct {
    int u;
    int v;
    int w;
} Edge;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    Edge edges[MAXM];
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    
    double min_density[MAXN][MAXN];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            min_density[i][j] = INF;
        }
    }
    
    double sum_current[MAXN];
    double sum_next[MAXN];
    
    for(int X=1; X<=N; X++){
        for(int i=1;i<=N;i++) sum_current[i] = INF;
        sum_current[X] = 0.0;
        
        for(int k=1; k<=N-1; k++){
            for(int i=1;i<=N;i++) sum_next[i] = INF;
            
            for(int i=0;i<M;i++){
                int u = edges[i].u;
                int v = edges[i].v;
                int w = edges[i].w;
                if(sum_current[u] + w < sum_next[v]){
                    sum_next[v] = sum_current[u] + w;
                }
            }
            
            for(int Y=1; Y<=N; Y++){
                if(sum_next[Y] < INF){
                    double density = sum_next[Y] / k;
                    if(density < min_density[X][Y]){
                        min_density[X][Y] = density;
                    }
                }
            }
            
            for(int i=1;i<=N;i++) {
                sum_current[i] = sum_next[i];
            }
        }
    }
    
    int Q;
    scanf("%d", &Q);
    while(Q--){
        int X, Y;
        scanf("%d %d", &X, &Y);
        if(min_density[X][Y] < INF){
            printf("%.3lf\n", min_density[X][Y]);
        }
        else{
            printf("OMG!\n");
        }
    }
    
    return 0;
}