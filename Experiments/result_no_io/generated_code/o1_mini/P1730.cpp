#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAXN 51
#define MAXK 51
#define INF 1000000000

typedef struct {
    int from;
    int to;
    int w;
} Edge;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Edge edges[M];
    for(int i=0;i<M;i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].w);
    }
    // Initialize dp
    long dp[MAXN][MAXN][MAXK];
    for(int X=1; X<=N; X++) {
        for(int Y=1; Y<=N; Y++) {
            for(int k=0; k<=50; k++) {
                dp[X][Y][k] = INF;
            }
        }
        dp[X][X][0] = 0;
        for(int k=1; k<=50; k++) {
            for(int i=0; i<M; i++) {
                int A = edges[i].from;
                int B = edges[i].to;
                int W = edges[i].w;
                if(dp[X][A][k-1] < INF){
                    if(dp[X][B][k] > dp[X][A][k-1] + W){
                        dp[X][B][k] = dp[X][A][k-1] + W;
                    }
                }
            }
        }
    }
    // Compute minDensity
    double minDensity[MAXN][MAXN];
    for(int X=1; X<=N; X++) {
        for(int Y=1; Y<=N; Y++) {
            double md = DBL_MAX;
            for(int k=1; k<=50; k++) {
                if(dp[X][Y][k] < INF){
                    double density = (double)dp[X][Y][k] / k;
                    if(density < md){
                        md = density;
                    }
                }
            }
            if(md < DBL_MAX){
                minDensity[X][Y] = md;
            }
            else{
                minDensity[X][Y] = -1.0;
            }
        }
    }
    // Read queries
    int Q;
    scanf("%d", &Q);
    while(Q--){
        int X, Y;
        scanf("%d %d", &X, &Y);
        if(minDensity[X][Y] >= 0){
            printf("%.3lf\n", minDensity[X][Y]);
        }
        else{
            printf("OMG!\n");
        }
    }
    return 0;
}