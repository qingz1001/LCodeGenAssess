#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Bridge;

int adj[151][150];
int adj_size[151];
int edge_count[151][151];
int disc_time[151];
int low[151];
int parent_node[151];
int visited[151];
Bridge bridges_list[5000];
int bridge_count = 0;
int time_counter_val = 0;
int n, m;

void add_edge(int u, int v) {
    adj[u][adj_size[u]++] = v;
    adj[v][adj_size[v]++] = u;
    edge_count[u][v]++;
    edge_count[v][u]++;
}

void dfs(int u) {
    visited[u] = 1;
    disc_time[u] = low[u] = ++time_counter_val;
    for(int i = 0; i < adj_size[u]; i++) {
        int v = adj[u][i];
        if(!visited[v]) {
            parent_node[v] = u;
            dfs(v);
            if(low[v] > disc_time[u] && edge_count[u][v] == 1) {
                if(u < v) {
                    bridges_list[bridge_count].a = u;
                    bridges_list[bridge_count].b = v;
                }
                else {
                    bridges_list[bridge_count].a = v;
                    bridges_list[bridge_count].b = u;
                }
                bridge_count++;
            }
            if(low[v] < low[u]) {
                low[u] = low[v];
            }
        }
        else if(v != parent_node[u]) {
            if(disc_time[v] < low[u]) {
                low[u] = disc_time[v];
            }
        }
    }
}

int compare_bridges(const void *a, const void *b) {
    Bridge *ba = (Bridge *)a;
    Bridge *bb = (Bridge *)b;
    if(ba->a != bb->a)
        return ba->a - bb->a;
    return ba->b - bb->b;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            dfs(i);
        }
    }
    qsort(bridges_list, bridge_count, sizeof(Bridge), compare_bridges);
    for(int i = 0; i < bridge_count; i++) {
        printf("%d %d\n", bridges_list[i].a, bridges_list[i].b);
    }
    return 0;
}