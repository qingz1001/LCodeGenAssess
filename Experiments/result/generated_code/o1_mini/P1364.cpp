#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

typedef struct {
    int w;
    int left;
    int right;
} Node;

int adj[MAX][MAX];

int main(){
    int n;
    scanf("%d", &n);
    Node nodes[MAX];
    memset(adj, 0, sizeof(adj));
    // To find root if needed
    int isChild[MAX];
    memset(isChild, 0, sizeof(isChild));
    for(int i=1;i<=n;i++){
        int w, u, v;
        scanf("%d %d %d", &nodes[i].w, &u, &v);
        nodes[i].left = u;
        nodes[i].right = v;
        if(u !=0){
            adj[i][u]=1;
            adj[u][i]=1;
            isChild[u]=1;
        }
        if(v !=0){
            adj[i][v]=1;
            adj[v][i]=1;
            isChild[v]=1;
        }
    }
    // Find root if needed, not required for BFS
    // Compute minimum sum
    long long minSum = -1;
    for(int h=1; h<=n; h++){
        int distance[MAX];
        for(int i=1;i<=n;i++) distance[i]=-1;
        // BFS from h
        int q[MAX];
        int front=0, rear=0;
        q[rear++] = h;
        distance[h]=0;
        while(front < rear){
            int u = q[front++];
            for(int v=1; v<=n; v++){
                if(adj[u][v] && distance[v]==-1){
                    distance[v] = distance[u]+1;
                    q[rear++] = v;
                }
            }
        }
        // Compute sum
        long long sum =0;
        for(int i=1;i<=n;i++) {
            sum += (long long)nodes[i].w * distance[i];
        }
        if(minSum==-1 || sum < minSum){
            minSum = sum;
        }
    }
    printf("%lld\n", minSum);
    return 0;
}