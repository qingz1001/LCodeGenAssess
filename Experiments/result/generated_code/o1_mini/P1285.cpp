#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define MAXCOMP 100
#define MAXSIZE (MAXN+1)

typedef struct {
    int part0[MAXN];
    int part1[MAXN];
    int size0;
    int size1;
} Component;

int n;
int mutual_adj[MAXN+1][MAXN+1];
int complement_adj[MAXN+1][MAXN+1];
int color[MAXN+1];
int visited[MAXN+1];
Component components[MAXCOMP];
int component_count = 0;

// Queue for BFS
typedef struct {
    int data[MAXN];
    int front;
    int rear;
} Queue;

void enqueue(Queue* q, int x){
    q->data[q->rear++] = x;
}

int dequeue(Queue* q){
    return q->data[q->front++];
}

int is_empty(Queue* q){
    return q->front == q->rear;
}

int main(){
    int i, j, x;
    // Initialize mutual adjacency
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            mutual_adj[i][j] = 0;
        }
    }
    // Read n
    scanf("%d", &n);
    // Read recognition lists
    for(i=1;i<=n;i++){
        while(scanf("%d", &x) && x != 0){
            mutual_adj[i][x] = 1;
        }
    }
    // Build mutual recognition adjacency
    int mutual_mutual_adj[MAXN+1][MAXN+1];
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i != j && mutual_adj[i][j] && mutual_adj[j][i]){
                mutual_mutual_adj[i][j] = 1;
            }
            else{
                mutual_mutual_adj[i][j] = 0;
            }
        }
    }
    // Build complement graph
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i != j){
                complement_adj[i][j] = mutual_mutual_adj[i][j] ? 0 : 1;
            }
            else{
                complement_adj[i][j] = 0;
            }
        }
    }
    // Check bipartite and collect components
    memset(color, -1, sizeof(color));
    memset(visited, 0, sizeof(visited));
    for(i=1;i<=n;i++){
        if(!visited[i]){
            Queue q;
            q.front = q.rear = 0;
            enqueue(&q, i);
            color[i] = 0;
            visited[i] = 1;
            Component comp;
            comp.size0 = comp.size1 = 0;
            while(!is_empty(&q)){
                int u = dequeue(&q);
                if(color[u] == 0){
                    comp.part0[comp.size0++] = u;
                }
                else{
                    comp.part1[comp.size1++] = u;
                }
                for(j=1;j<=n;j++){
                    if(complement_adj[u][j]){
                        if(color[j]==-1){
                            color[j] = 1 - color[u];
                            enqueue(&q, j);
                            visited[j] = 1;
                        }
                        else if(color[j] == color[u]){
                            printf("No solution\n");
                            return 0;
                        }
                    }
                }
            }
            components[component_count++] = comp;
        }
    }
    // DP to balance group sizes
    int dp[MAXCOMP+1][MAXN+1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(i=0;i<component_count;i++){
        for(j=0;j<=n;j++) {
            if(dp[i][j]){
                // Assign part0 to group A
                if(j + components[i].size0 <= n){
                    dp[i+1][j + components[i].size0] = 1;
                }
                // Assign part1 to group A
                if(j + components[i].size1 <= n){
                    dp[i+1][j + components[i].size1] = 1;
                }
            }
        }
    }
    // Find the best group size
    int best_diff = n+1;
    int best_size = -1;
    for(i=1;i<n;i++){
        if(dp[component_count][i]){
            int diff = abs((n - i) - i);
            if(diff < best_diff){
                best_diff = diff;
                best_size = i;
            }
        }
    }
    if(best_size == -1){
        printf("No solution\n");
        return 0;
    }
    // Reconstruct the assignment
    int groupA[MAXN];
    int groupB[MAXN];
    int sizeA=0, sizeB=0;
    int current_size = best_size;
    for(i=component_count-1;i>=0;i--){
        if(current_size >= components[i].size0 && dp[i][current_size - components[i].size0]){
            // Assign part0 to group A
            for(j=0;j<components[i].size0;j++) groupA[sizeA++] = components[i].part0[j];
            for(j=0;j<components[i].size1;j++) groupB[sizeB++] = components[i].part1[j];
            current_size -= components[i].size0;
        }
        else{
            // Assign part1 to group A
            for(j=0;j<components[i].size1;j++) groupA[sizeA++] = components[i].part1[j];
            for(j=0;j<components[i].size0;j++) groupB[sizeB++] = components[i].part0[j];
            current_size -= components[i].size1;
        }
    }
    // Sort the groups
    for(i=0;i<sizeA-1;i++) {
        for(j=i+1;j<sizeA;j++) {
            if(groupA[i] > groupA[j]){
                int temp = groupA[i];
                groupA[i] = groupA[j];
                groupA[j] = temp;
            }
        }
    }
    for(i=0;i<sizeB-1;i++) {
        for(j=i+1;j<sizeB;j++) {
            if(groupB[i] > groupB[j]){
                int temp = groupB[i];
                groupB[i] = groupB[j];
                groupB[j] = temp;
            }
        }
    }
    // Print group A
    printf("%d", sizeA);
    for(i=0;i<sizeA;i++) printf(" %d", groupA[i]);
    printf("\n");
    // Print group B
    printf("%d", sizeB);
    for(i=0;i<sizeB;i++) printf(" %d", groupB[i]);
    printf("\n");
    return 0;
}