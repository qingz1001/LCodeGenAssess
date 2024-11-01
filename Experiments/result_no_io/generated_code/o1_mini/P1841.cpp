#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define INF 1000000000000000LL
#define MOD1 1000000007
#define MOD2 1000000009

typedef struct {
    int to;
    int cost;
} Edge;

Edge adj[MAXN][MAXN];
int adj_size[MAXN];

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) adj_size[i]=0;
    for(int i=0;i<M;i++){
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        adj[u][adj_size[u]].to = v;
        adj[u][adj_size[u]].cost = c;
        adj_size[u]++;
        adj[v][adj_size[v]].to = u;
        adj[v][adj_size[v]].cost = c;
        adj_size[v]++;
    }
    
    long long dist[MAXN][MAXN];
    unsigned long long cnt1[MAXN][MAXN];
    unsigned long long cnt2[MAXN][MAXN];
    
    for(int a=1;a<=N;a++){
        long long dist_current[MAXN];
        unsigned long long cnt1_current[MAXN];
        unsigned long long cnt2_current_arr[MAXN];
        int used[MAXN];
        for(int i=1;i<=N;i++){
            dist_current[i] = INF;
            cnt1_current[i] = 0;
            cnt2_current_arr[i] = 0;
            used[i] = 0;
        }
        dist_current[a] = 0;
        cnt1_current[a] = 1;
        cnt2_current_arr[a] = 1;
        
        for(int k=1;k<=N;k++){
            int u = -1;
            long long min_dist = INF;
            for(int i=1;i<=N;i++){
                if(!used[i] && dist_current[i] < min_dist){
                    min_dist = dist_current[i];
                    u = i;
                }
            }
            if(u == -1) break;
            used[u] = 1;
            for(int i=0;i<adj_size[u];i++){
                int v = adj[u][i].to;
                int c = adj[u][i].cost;
                if(dist_current[u] + c < dist_current[v]){
                    dist_current[v] = dist_current[u] + c;
                    cnt1_current[v] = cnt1_current[u];
                    cnt2_current_arr[v] = cnt2_current_arr[u];
                }
                else if(dist_current[u] + c == dist_current[v]){
                    cnt1_current[v] = (cnt1_current[v] + cnt1_current[u]) % MOD1;
                    cnt2_current_arr[v] = (cnt2_current_arr[v] + cnt2_current_arr[u]) % MOD2;
                }
            }
        }
        for(int b=1;b<=N;b++){
            dist[a][b] = dist_current[b];
            cnt1[a][b] = cnt1_current[b];
            cnt2[a][b] = cnt2_current_arr[b];
        }
    }
    
    int important[MAXN];
    for(int i=1;i<=N;i++) important[i]=0;
    
    for(int c=1;c<=N;c++){
        int flag = 0;
        for(int a=1;a<=N && !flag;a++){
            if(a == c) continue;
            for(int b=a+1;b<=N && !flag;b++){
                if(b == c) continue;
                if(dist[a][c] + dist[c][b] == dist[a][b]){
                    unsigned long long lhs1 = (cnt1[a][c] * cnt1[c][b]) % MOD1;
                    unsigned long long lhs2 = (cnt2[a][c] * cnt2[c][b]) % MOD2;
                    if(lhs1 == cnt1[a][b] && lhs2 == cnt2[a][b]){
                        important[c] = 1;
                        flag = 1;
                    }
                }
            }
        }
    }
    
    int first = 1;
    for(int i=1;i<=N;i++) {
        if(important[i]){
            if(!first){
                printf(" ");
            }
            printf("%d", i);
            first = 0;
        }
    }
    if(first){
        printf("No important cities.\n");
    }
    else{
        printf("\n");
    }
    return 0;
}