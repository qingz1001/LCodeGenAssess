#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 200005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int index_num = 0, scc_count = 0;
int indices[MAXN], lowlink[MAXN];
bool onStack_flag[MAXN];
int stack_arr[MAXN];
int top = -1;
int scc_id[MAXN];
long long h[MAXN];
long long c[MAXN];
long long max_h[MAXN];
long long n;
long long total_cost = 0;

void add_edge(int from, int to) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->next = adj[from];
    adj[from] = edge;
}

void tarjan(int u) {
    indices[u] = lowlink[u] = ++index_num;
    stack_arr[++top] = u;
    onStack_flag[u] = true;
    Edge* edge = adj[u];
    while(edge != NULL) {
        int v = edge->to;
        if(indices[v] == 0) {
            tarjan(v);
            if(lowlink[v] < lowlink[u]) lowlink[u] = lowlink[v];
        }
        else if(onStack_flag[v]) {
            if(indices[v] < lowlink[u]) lowlink[u] = indices[v];
        }
        edge = edge->next;
    }
    if(indices[u] == lowlink[u]) {
        long long current_max = 0;
        while(1) {
            int v = stack_arr[top--];
            onStack_flag[v] = false;
            scc_id[v] = scc_count;
            if(h[v] > current_max) current_max = h[v];
            if(v == u) break;
        }
        max_h[scc_count++] = current_max;
    }
}

int main(){
    scanf("%lld", &n);
    long long a;
    for(long long i=1;i<=n;i++){
        scanf("%lld %lld %lld", &a, &h[i], &c[i]);
        add_edge(i, a);
    }
    for(long long i=1;i<=n;i++) {
        if(indices[i]==0) tarjan(i);
    }
    for(long long i=1;i<=n;i++) {
        if(h[i] < max_h[scc_id[i]]) {
            total_cost += c[i];
        }
    }
    printf("%lld\n", total_cost);
    return 0;
}