#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    // Allocate memory
    int *head = (int*)malloc((N+1) * sizeof(int));
    for(int i=1;i<=N;i++) head[i] = -1;
    int *to = (int*)malloc(M * sizeof(int));
    int *next = (int*)malloc(M * sizeof(int));
    int *in_degree = (int*)calloc(N+1, sizeof(int));
    int *dp = (int*)malloc((N+1) * sizeof(int));
    for(int i=1;i<=N;i++) dp[i] = 1;
    
    // Read edges
    for(int k=0; k<M; k++){
        int x, y;
        scanf("%d %d", &x, &y);
        to[k] = y;
        next[k] = head[x];
        head[x] = k;
        in_degree[y]++;
    }
    
    // Initialize queue
    int *queue = (int*)malloc(N * sizeof(int));
    int front = 0, back = 0;
    for(int i=1;i<=N;i++) {
        if(in_degree[i] == 0){
            queue[back++] = i;
        }
    }
    
    // Kahn's algorithm
    while(front < back){
        int u = queue[front++];
        for(int e = head[u]; e != -1; e = next[e]){
            int v = to[e];
            if(dp[v] < dp[u] + 1){
                dp[v] = dp[u] + 1;
            }
            in_degree[v]--;
            if(in_degree[v] == 0){
                queue[back++] = v;
            }
        }
    }
    
    // Print results
    for(int i=1;i<=N;i++) {
        printf("%d\n", dp[i]);
    }
    
    // Free memory
    free(head);
    free(to);
    free(next);
    free(in_degree);
    free(dp);
    free(queue);
    
    return 0;
}