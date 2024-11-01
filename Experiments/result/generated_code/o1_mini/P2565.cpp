#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define MAXM 201
#define MAXNM 40400

int n, m;
int a[MAXN];
int adj[MAXN][MAXN];
int visited[MAXN];
int onStack[MAXN];
int hasCycle = 0;
int topoOrder[MAXN];
int topoIndex = 0;

// Stack for iterative DFS
typedef struct {
    int node;
    int nextChild;
} StackFrame;

int stackSize = 0;
StackFrame stackFrames[MAXN*MAXN];

void dfs(int u) {
    visited[u] = 1;
    onStack[u] = 1;
    for(int v = 1; v <= n; v++) {
        if(adj[u][v]) {
            if(!visited[v]) {
                dfs(v);
                if(hasCycle) return;
            }
            else if(onStack[v]) {
                hasCycle = 1;
                return;
            }
        }
    }
    onStack[u] = 0;
    topoOrder[topoIndex++] = u;
}

int main(){
    if(scanf("%d %d", &n, &m)!=2){
        return 0;
    }
    for(int i=1;i<=n;i++){
        scanf("%d", &a[i]);
        if(a[i]==i){
            printf("0\n");
            return 0;
        }
        if(a[i]<1 || a[i]>n){
            printf("0\n");
            return 0;
        }
        adj[i][a[i]] = 1;
    }

    // Detect cycle and get topo order
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            dfs(i);
            if(hasCycle){
                printf("0\n");
                return 0;
            }
        }
    }

    // Reverse topoOrder to assign higher labels to later in topo
    // So that Di has higher labels than Dai
    // topoOrder[0..topoIndex-1] has from first to last in topo
    // We assign labels from 1 to n*m, higher labels to later
    // So reverse the order
    int assigned[MAXN][MAXM];
    int currentLabel = 1;
    // Assign in topoOrder from first to last
    for(int i=topoIndex-1;i>=0;i--){
        int die = topoOrder[i];
        for(int j=0;j<m;j++){
            if(currentLabel > n*m){
                printf("0\n");
                return 0;
            }
            assigned[die][j] = currentLabel++;
        }
    }

    // Now check if for each i, Di beats Dai with P > 1/2
    // Since all labels in Di are greater than Dai, P=1 > 1/2
    // So it's valid

    // Now print the assigned labels
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            printf("%d", assigned[i][j]);
            if(j != m-1){
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}