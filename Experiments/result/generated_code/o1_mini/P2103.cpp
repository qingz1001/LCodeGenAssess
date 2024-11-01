#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int **distance = (int **)malloc((N+1) * sizeof(int *));
    for(int i=0;i<=N;i++) {
        distance[i] = (int *)malloc((N+1) * sizeof(int));
        for(int j=0;j<=N;j++) {
            if(i == j) distance[i][j] = 0;
            else distance[i][j] = INF;
        }
    }
    typedef struct{
        int u, v, l;
    } Edge;
    Edge *edges = (Edge *)malloc(M * sizeof(Edge));
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].l);
        if(edges[i].l < distance[edges[i].u][edges[i].v]){
            distance[edges[i].u][edges[i].v] = edges[i].l;
            distance[edges[i].v][edges[i].u] = edges[i].l;
        }
    }
    // Floyd-Warshall
    for(int k=1;k<=N;k++){
        for(int i=1;i<=N;i++){
            if(distance[i][k] == INF) continue;
            for(int j=1;j<=N;j++){
                if(distance[k][j] == INF) continue;
                if(distance[i][j] > distance[i][k] + distance[k][j]){
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
    // Initialize C
    int **C = (int **)malloc((N+1) * sizeof(int *));
    for(int i=0;i<=N;i++) {
        C[i] = (int *)calloc((N+1), sizeof(int));
    }
    // Count
    for(int e=0;e<M;e++){
        int u = edges[e].u;
        int v = edges[e].v;
        int l = edges[e].l;
        for(int i=1;i<=N;i++){
            for(int j=i+1;j<=N;j++){
                if(distance[i][j] == distance[i][u] + l + distance[v][j] || distance[i][j] == distance[i][v] + l + distance[u][j]){
                    C[i][j]++;
                }
            }
        }
    }
    // Output
    int first = 1;
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            if(!first) printf(" ");
            printf("%d", C[i][j]);
            first = 0;
        }
    }
    printf("\n");
    // Free memory
    for(int i=0;i<=N;i++) {
        free(distance[i]);
        free(C[i]);
    }
    free(distance);
    free(C);
    free(edges);
    return 0;
}