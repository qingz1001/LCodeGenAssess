#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) {
        scanf("%d", &a[i]);
        a[i]--; // zero-based indexing
    }
    // Build graph
    int **graph = (int**)malloc(n * sizeof(int*));
    int *in_degree = (int*)calloc(n, sizeof(int));
    for(int i=0;i<n;i++) {
        graph[i] = (int*)malloc(1 * sizeof(int));
        graph[i][0] = a[i];
        in_degree[a[i]]++;
    }
    // Topological sort
    int *queue = (int*)malloc(n * sizeof(int));
    int front=0, rear=0;
    for(int i=0;i<n;i++) if(in_degree[i]==0) queue[rear++] = i;
    int *order = (int*)malloc(n * sizeof(int));
    int idx=0;
    while(front < rear){
        int u = queue[front++];
        order[idx++] = u;
        // Only one outgoing edge
        int v = graph[u][0];
        in_degree[v]--;
        if(in_degree[v]==0) queue[rear++] = v;
    }
    if(idx != n){
        printf("0");
        return 0;
    }
    // Assign numbers
    int total = n * m;
    int *numbers = (int*)malloc(total * sizeof(int));
    for(int i=0;i<total;i++) numbers[i] = i+1;
    // Assign in topological order
    int **dice = (int**)malloc(n * sizeof(int*));
    for(int i=0;i<n;i++) dice[i] = (int*)malloc(m * sizeof(int));
    for(int i=0;i<n;i++){
        int die = order[i];
        for(int j=0;j<m;j++) {
            dice[die][j] = numbers[i*m + j];
        }
    }
    // Print
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) {
            printf("%d%c", dice[i][j], j==m-1?'\n':' ');
        }
    }
    // Free memory
    free(a);
    for(int i=0;i<n;i++) free(graph[i]);
    free(graph);
    free(in_degree);
    free(queue);
    free(order);
    free(numbers);
    for(int i=0;i<n;i++) free(dice[i]);
    free(dice);
    return 0;
}