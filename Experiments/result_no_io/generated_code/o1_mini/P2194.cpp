#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005
#define MOD 1000000007

typedef struct Edge {
    int to;
    int next;
} Edge;

Edge edges[MAXM];
int head[MAXN];
int edge_cnt = 0;

long long w[MAXN];
int indices_arr[MAXN];
int lowlink[MAXN];
int on_stack_arr[MAXN];
int stack_arr[MAXN];
int s_top = 0;
int idx = 0;

long long total_cost = 0;
long long total_ways = 1;

void add_edge(int from, int to){
    edges[edge_cnt].to = to;
    edges[edge_cnt].next = head[from];
    head[from] = edge_cnt++;
}

void strongconnect(int v) {
    indices_arr[v] = idx;
    lowlink[v] = idx;
    idx++;
    stack_arr[s_top++] = v;
    on_stack_arr[v] = 1;

    for(int i = head[v]; i != -1; i = edges[i].next){
        int to = edges[i].to;
        if(indices_arr[to] == -1){
            strongconnect(to);
            if(lowlink[v] > lowlink[to]){
                lowlink[v] = lowlink[to];
            }
        }
        else if(on_stack_arr[to]){
            if(lowlink[v] > indices_arr[to]){
                lowlink[v] = indices_arr[to];
            }
        }
    }

    if(lowlink[v] == indices_arr[v]){
        long long min_w = -1;
        long long count = 0;
        while(1){
            int u = stack_arr[--s_top];
            on_stack_arr[u] = 0;
            if(min_w == -1 || w[u] < min_w){
                min_w = w[u];
                count = 1;
            }
            else if(w[u] == min_w){
                count++;
            }
            if(u == v){
                break;
            }
        }
        total_cost += min_w;
        total_ways = (total_ways * count) % MOD;
    }
}

int main(){
    int n, m;
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &w[i]);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
    }
    memset(indices_arr, -1, sizeof(indices_arr));
    for(int i = 1; i <= n; i++){
        if(indices_arr[i] == -1){
            strongconnect(i);
        }
    }
    printf("%lld %lld\n", total_cost, total_ways);
    return 0;
}