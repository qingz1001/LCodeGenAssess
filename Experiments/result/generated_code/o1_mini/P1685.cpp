#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10005
#define MAX_M 50005

typedef struct Edge {
    int to;
    int t;
    int next;
} Edge;

Edge edges[MAX_M];
int head[MAX_N];
int in_degree[MAX_N];
int order[MAX_N];
int front = 0, back = 0;
int queue[MAX_N];

unsigned long long dp_k[MAX_N];
unsigned long long dp_su[MAX_N];

int main(){
    int n, m, s, t, t0;
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);
    
    for(int i=1;i<=n;i++) head[i]=-1;
    for(int i=0;i<m;i++){
        int x, y, ti;
        scanf("%d %d %d", &x, &y, &ti);
        edges[i].to = y;
        edges[i].t = ti;
        edges[i].next = head[x];
        head[x] = i;
        in_degree[y]++;
    }
    
    // Kahn's algorithm
    for(int i=1;i<=n;i++) {
        if(in_degree[i]==0){
            queue[back++] = i;
        }
    }
    
    int top_order_size =0;
    while(front < back){
        int u = queue[front++];
        order[top_order_size++] = u;
        for(int e = head[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            in_degree[v]--;
            if(in_degree[v]==0){
                queue[back++] = v;
            }
        }
    }
    
    // Initialize DP
    for(int i=1;i<=n;i++) {
        dp_k[i] = 0;
        dp_su[i] = 0;
    }
    dp_k[t] =1;
    dp_su[t] =0;
    
    // Process in reverse topological order
    for(int i=top_order_size-1;i>=0;i--){
        int u = order[i];
        if(u == t) continue;
        unsigned long long total_k =0;
        unsigned long long total_su =0;
        for(int e = head[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            int ti = edges[e].t;
            total_k += dp_k[v];
            total_su += ( (unsigned long long)ti * dp_k[v] ) + dp_su[v];
        }
        dp_k[u] = total_k;
        dp_su[u] = total_su;
    }
    
    unsigned long long k = dp_k[s];
    unsigned long long s_sum = dp_su[s];
    unsigned long long total_time = s_sum + (k -1) * (unsigned long long)t0;
    printf("%llu\n", total_time % 10000);
    
    return 0;
}