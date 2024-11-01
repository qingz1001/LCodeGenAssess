#include <stdio.h>
#include <stdlib.h>

#define MAXN 366666
#define LOGN 20

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

Edge* adjT[MAXN + 1];
Edge* adjTPrime[MAXN + 1];
long long depthT[MAXN + 1];
long long depthTPrimeArr[MAXN + 1];
int parentT[MAXN + 1][LOGN];
int parentTPrime[MAXN + 1][LOGN];
int n;

void addEdge(Edge* adj[], int from, int to, int weight){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->weight = weight;
    edge->next = adj[from];
    adj[from] = edge;
}

void dfs(int u, int p, Edge* adj[], long long depthArr[], int parentArr[][LOGN]){
    parentArr[u][0] = p;
    Edge* edge = adj[u];
    while(edge){
        int v = edge->to;
        if(v != p){
            depthArr[v] = depthArr[u] + edge->weight;
            dfs(v, u, adj, depthArr, parentArr);
        }
        edge = edge->next;
    }
}

int getLCA(int u, int v, int parentArr[][LOGN]){
    if(u == v) return u;
    for(int k = LOGN - 1; k >=0; k--){
        if(parentArr[u][k] != -1 && parentArr[u][k] != parentArr[v][k]){
            u = parentArr[u][k];
            v = parentArr[v][k];
        }
    }
    return parentArr[u][0];
}

int main(){
    scanf("%d", &n);
    for(int i=0;i< n-1;i++){
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        addEdge(adjT, x, y, v);
        addEdge(adjT, y, x, v);
    }
    for(int i=0;i< n-1;i++){
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        addEdge(adjTPrime, x, y, v);
        addEdge(adjTPrime, y, x, v);
    }
    for(int i=1;i<=n;i++){
        for(int k=0;k<LOGN;k++) parentT[i][k] = -1;
        for(int k=0;k<LOGN;k++) parentTPrime[i][k] = -1;
    }
    depthT[1] = 0;
    dfs(1, -1, adjT, depthT, parentT);
    depthTPrimeArr[1] = 0;
    dfs(1, -1, adjTPrime, depthTPrimeArr, parentTPrime);
    for(int k=1;k<LOGN;k++){
        for(int v=1; v<=n; v++){
            if(parentT[v][k-1] != -1){
                parentT[v][k] = parentT[parentT[v][k-1]][k-1];
            }
            if(parentTPrime[v][k-1] != -1){
                parentTPrime[v][k] = parentTPrime[parentTPrime[v][k-1]][k-1];
            }
        }
    }
    long long maxDist = -__LONG_LONG_MAX__;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int lcaT = getLCA(i, j, parentT);
            int lcaTPrime = getLCA(i, j, parentTPrime);
            long long value = depthT[i] + depthT[j] - depthT[lcaT] - depthTPrimeArr[lcaTPrime];
            if(value > maxDist){
                maxDist = value;
            }
        }
    }
    printf("%lld\n", maxDist);
    return 0;
}