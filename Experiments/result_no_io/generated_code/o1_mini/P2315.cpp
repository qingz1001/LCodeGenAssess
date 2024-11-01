#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    
    // 初始化邻接矩阵
    int **adj = (int **)malloc((N+1) * sizeof(int *));
    for(int i = 0; i <= N; i++) {
        adj[i] = (int *)calloc(N+1, sizeof(int));
    }
    
    // 读取所有边
    for(int i = 0; i < M; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }
    
    // 删除指定的边
    for(int i = 0; i < K; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 0;
    }
    
    // 统计没有被删除边的三角形
    long long count = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = i+1; j <= N; j++) {
            if(adj[i][j]){
                for(int k = j+1; k <= N; k++) {
                    if(adj[i][k] && adj[j][k]){
                        count++;
                    }
                }
            }
        }
    }
    
    // 输出结果到output.txt
    FILE *fp = fopen("output.txt", "w");
    fprintf(fp, "%lld", count);
    fclose(fp);
    
    // 释放内存
    for(int i = 0; i <= N; i++) {
        free(adj[i]);
    }
    free(adj);
    
    return 0;
}