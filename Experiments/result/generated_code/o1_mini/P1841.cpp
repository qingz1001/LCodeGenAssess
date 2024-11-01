#include <stdio.h>
#include <stdlib.h>

#define MAX 201
#define INF 1000000000

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    int adj[MAX][MAX];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            if(i == j) adj[i][j] = 0;
            else adj[i][j] = INF;
        }
    }
    
    int a, b, c;
    for(int i=0;i<M;i++) {
        scanf("%d %d %d", &a, &b, &c);
        if(c < adj[a][b]){
            adj[a][b] = c;
            adj[b][a] = c;
        }
    }
    
    // Compute all-pairs shortest paths
    int d[MAX][MAX];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            d[i][j] = adj[i][j];
        }
    }
    
    for(int k=1;k<=N;k++) {
        for(int i=1;i<=N;i++) {
            if(d[i][k] == INF) continue;
            for(int j=1;j<=N;j++) {
                if(d[k][j] == INF) continue;
                if(d[i][j] > d[i][k] + d[k][j]){
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
    
    int important[MAX];
    for(int i=1;i<=N;i++) important[i] = 0;
    
    // Temporary distance array
    int d2[MAX][MAX];
    
    for(int c_node=1; c_node<=N; c_node++) {
        // Initialize d2
        for(int i=1;i<=N;i++) {
            for(int j=1;j<=N;j++) {
                if(i == c_node || j == c_node) {
                    if(i == j) d2[i][j] = 0;
                    else d2[i][j] = INF;
                }
                else {
                    d2[i][j] = adj[i][j];
                }
            }
        }
        
        // Floyd-Warshall excluding c_node
        for(int k=1;k<=N;k++) {
            if(k == c_node) continue;
            for(int i=1;i<=N;i++) {
                if(i == c_node) continue;
                if(d2[i][k] == INF) continue;
                for(int j=1;j<=N;j++) {
                    if(j == c_node) continue;
                    if(d2[k][j] == INF) continue;
                    if(d2[i][j] > d2[i][k] + d2[k][j]){
                        d2[i][j] = d2[i][k] + d2[k][j];
                    }
                }
            }
        }
        
        // Compare d2 with d
        int found = 0;
        for(int i=1;i<=N && !found;i++) {
            if(i == c_node) continue;
            for(int j=1;j<=N && !found;j++) {
                if(j == c_node) continue;
                if(d2[i][j] > d[i][j]){
                    important[c_node] = 1;
                    found = 1;
                }
            }
        }
    }
    
    // Collect and print important cities
    int first = 1;
    for(int i=1;i<=N;i++) {
        if(important[i]) {
            if(!first) printf(" ");
            printf("%d", i);
            first = 0;
        }
    }
    if(first) printf("No important cities.");
    printf("\n");
    
    return 0;
}