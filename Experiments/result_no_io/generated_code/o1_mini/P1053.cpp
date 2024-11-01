#include <stdio.h>
#include <stdlib.h>

#define MAX 50005

int main(){
    int n;
    scanf("%d", &n);
    
    int adj[MAX][2];
    for(int i=1;i<=n;i++){
        scanf("%d %d", &adj[i][0], &adj[i][1]);
    }
    
    int visited[MAX];
    for(int i=1;i<=n;i++) visited[i] = 0;
    
    // Start DFS from node 1
    int stack[MAX];
    int top = -1;
    stack[++top] = 1;
    visited[1] = 1;
    while(top >=0){
        int u = stack[top--];
        for(int i=0;i<2;i++){
            int v = adj[u][i];
            if(!visited[v]){
                visited[v] = 1;
                stack[++top] = v;
            }
        }
    }
    
    // Check if all nodes are visited
    int single_cycle = 1;
    for(int i=1;i<=n;i++) {
        if(!visited[i]){
            single_cycle = 0;
            break;
        }
    }
    
    // Additionally, check if the graph has exactly n edges forming a single cycle
    // Each node has degree 2, so total edges should be n (each edge counted twice)
    // Already checked connectivity, so it's a single cycle
    if(single_cycle){
        printf("%d", n-1);
    }
    else{
        printf("-1");
    }
}