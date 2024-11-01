#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 301
#define MAXM 90000
#define QUEUE_SIZE MAXN

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int has_parents[MAXN] = {0};
    int parent1[MAXN], parent2[MAXN];
    memset(parent1, 0, sizeof(parent1));
    memset(parent2, 0, sizeof(parent2));
    // Build graph for topological sort
    int in_degree[MAXN];
    memset(in_degree, 0, sizeof(in_degree));
    // Adjacency list
    int adj[MAXN][MAXN];
    int adj_cnt[MAXN];
    memset(adj_cnt, 0, sizeof(adj_cnt));
    for(int i=0;i<k;i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        has_parents[a] = 1;
        parent1[a] = b;
        parent2[a] = c;
        in_degree[a] +=2;
        adj[b][adj_cnt[b]++] = a;
        adj[c][adj_cnt[c]++] = a;
    }
    // Topological sort
    int order[MAXN];
    int front =0, rear=0;
    int queue[QUEUE_SIZE];
    for(int i=1;i<=n;i++){
        if(in_degree[i]==0){
            queue[rear++] = i;
        }
    }
    int idx=0;
    while(front < rear){
        int u = queue[front++];
        order[idx++] = u;
        for(int i=0;i<adj_cnt[u];i++){
            int v = adj[u][i];
            in_degree[v]--;
            if(in_degree[v]==0){
                queue[rear++] = v;
            }
        }
    }
    // Initialize similarity matrix
    double S[MAXN][MAXN];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i == j){
                S[i][j] = 1.0;
            }
            else{
                if(!has_parents[i] && !has_parents[j]){
                    S[i][j] = 0.0;
                }
                else{
                    S[i][j] = 0.0; // Will be updated
                }
            }
        }
    }
    // Process in topological order
    for(int i=0;i<idx;i++){
        int x = order[i];
        if(has_parents[x]){
            int a = parent1[x];
            int b = parent2[x];
            for(int y=1;y<=n;y++){
                double val;
                if(has_parents[y]){
                    int c = parent1[y];
                    int d = parent2[y];
                    val = 0.25 * (S[a][c] + S[a][d] + S[b][c] + S[b][d]);
                }
                else{
                    val = 0.5 * (S[a][y] + S[b][y]);
                }
                S[x][y] = val;
                S[y][x] = val;
            }
        }
    }
    int m;
    scanf("%d", &m);
    while(m--){
        int u, v;
        scanf("%d %d", &u, &v);
        double percent = S[u][v] * 100.0;
        char buffer[50];
        // Print with enough precision
        // Using 10 decimal places
        sprintf(buffer, "%.10lf", percent);
        // Remove trailing zeros
        int len = strlen(buffer);
        while(len >0 && buffer[len-1]=='0') len--;
        if(len >0 && buffer[len-1]=='.') len--;
        buffer[len] = '\0';
        // Ensure leading zero before decimal point
        if(buffer[0]=='.'){
            memmove(buffer+1, buffer, len+1);
            buffer[0] = '0';
        }
        printf("%s%%\n", buffer);
    }
    return 0;
}