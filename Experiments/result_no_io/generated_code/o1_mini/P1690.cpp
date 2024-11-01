#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define MAXP 10
#define INF 1000000000

int main(){
    int N;
    scanf("%d", &N);
    int dist[N+1][N+1];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    // Floyd-Warshall
    for(int k=1;k<=N;k++) {
        for(int i=1;i<=N;i++) {
            for(int j=1;j<=N;j++) {
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    int P;
    scanf("%d", &P);
    int treasures[MAXP];
    for(int i=0;i<P;i++) {
        scanf("%d", &treasures[i]);
    }
    if(P == 0){
        printf("%d", dist[1][N]);
        return 0;
    }
    int size = 1<<P;
    long dp[size][MAXP];
    for(int i=0;i<size;i++) {
        for(int j=0;j<P;j++) {
            dp[i][j] = INF;
        }
    }
    for(int i=0;i<P;i++) {
        dp[1<<i][i] = dist[1][treasures[i]];
    }
    for(int mask=1; mask < (1<<P); mask++) {
        for(int last=0; last<P; last++) {
            if(mask & (1<<last)){
                for(int next=0; next<P; next++) {
                    if(!(mask & (1<<next))){
                        int new_mask = mask | (1<<next);
                        if(dp[new_mask][next] > dp[mask][last] + dist[treasures[last]][treasures[next]]){
                            dp[new_mask][next] = dp[mask][last] + dist[treasures[last]][treasures[next]];
                        }
                    }
                }
            }
        }
    }
    int full_mask = (1<<P) -1;
    long res = INF;
    for(int i=0;i<P;i++) {
        long total = dp[full_mask][i] + dist[treasures[i]][N];
        if(total < res){
            res = total;
        }
    }
    printf("%ld", res);
    return 0;
}