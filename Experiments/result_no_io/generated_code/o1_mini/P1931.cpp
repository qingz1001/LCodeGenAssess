#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 30
#define INF 1e9

int main(){
    int n, m, case_num = 1;
    while(scanf("%d", &n) && n){
        char currencies[MAXN][21];
        for(int i=0;i<n;i++) scanf("%s", currencies[i]);
        scanf("%d", &m);
        double adj[MAXN][MAXN];
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) adj[i][j] = INF;
        for(int i=0;i<m;i++){
            char src[21], dest[21];
            double rate;
            scanf("%s %lf %s", src, &rate, dest);
            int s, d;
            for(s=0;s<n;s++) if(strcmp(currencies[s], src)==0) break;
            for(d=0;d<n;d++) if(strcmp(currencies[d], dest)==0) break;
            adj[s][d] = -log(rate);
        }
        double dist[MAXN];
        int has_neg = 0;
        for(int start=0; start<n && !has_neg; start++){
            for(int i=0;i<n;i++) dist[i] = INF;
            dist[start] = 0;
            for(int k=0;k<n-1;k++) {
                for(int i=0;i<n;i++) {
                    for(int j=0;j<n;j++) {
                        if(adj[i][j] < INF){
                            if(dist[j] > dist[i] + adj[i][j]){
                                dist[j] = dist[i] + adj[i][j];
                            }
                        }
                    }
                }
            }
            for(int i=0;i<n && !has_neg;i++) {
                for(int j=0;j<n;j++) {
                    if(adj[i][j] < INF){
                        if(dist[j] > dist[i] + adj[i][j]){
                            has_neg = 1;
                            break;
                        }
                    }
                }
            }
        }
        if(case_num >1) printf("\n");
        printf("Case %d: %s\n", case_num++, has_neg?"Yes":"No");
    }
    return 0;
}