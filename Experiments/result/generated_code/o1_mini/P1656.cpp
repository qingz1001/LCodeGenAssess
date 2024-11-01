#include <stdio.h>
#include <stdlib.h>

#define MAXN 151
#define MAXM 5001

typedef struct Edge {
    int a;
    int b;
} Edge;

Edge bridges[MAXM];
int bridge_count = 0;

int adj[MAXN][MAXN];
int n, m;
int disc[MAXN];
int low_[MAXN];
int parent_[MAXN];
int time_counter = 0;

void add_edge(int u, int v){
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void dfs(int u){
    disc[u] = low_[u] = ++time_counter;
    for(int v=1; v<=n; v++){
        if(adj[u][v]){
            if(!disc[v]){
                parent_[v] = u;
                dfs(v);
                if(low_[v] > disc[u]){
                    if(u < v){
                        bridges[bridge_count].a = u;
                        bridges[bridge_count].b = v;
                    }
                    else{
                        bridges[bridge_count].a = v;
                        bridges[bridge_count].b = u;
                    }
                    bridge_count++;
                }
                if(low_[v] < low_[u]){
                    low_[u] = low_[v];
                }
            }
            else if(v != parent_[u]){
                if(disc[v] < low_[u]){
                    low_[u] = disc[v];
                }
            }
        }
    }
}

int cmp(const void *a, const void *b){
    Edge ea = *(Edge*)a;
    Edge eb = *(Edge*)b;
    if(ea.a != eb.a)
        return ea.a - eb.a;
    return ea.b - eb.b;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }
    for(int i=1; i<=n; i++){
        if(!disc[i]){
            dfs(i);
        }
    }
    qsort(bridges, bridge_count, sizeof(Edge), cmp);
    for(int i=0; i<bridge_count; i++){
        printf("%d %d\n", bridges[i].a, bridges[i].b);
    }
    return 0;
}