#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MOD 10007

int n;
int w[MAX_N];
long long max_value = 0;
long long sum_value = 0;

struct Edge {
    int to, next;
} edge[MAX_N * 2];

int head[MAX_N], cnt;

void add_edge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    long long sum1 = 0, sum2 = 0, max1 = 0, max2 = 0;
    
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        
        dfs(v, u);
        
        sum_value = (sum_value + sum1 * w[v] + sum2 * w[v]) % MOD;
        sum1 = (sum1 + w[v]) % MOD;
        sum2 = (sum2 + sum1) % MOD;
        
        if (w[v] > max1) {
            max2 = max1;
            max1 = w[v];
        } else if (w[v] > max2) {
            max2 = w[v];
        }
    }
    
    if (max1 * max2 > max_value) {
        max_value = max1 * max2;
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    
    dfs(1, 0);
    
    printf("%lld %lld\n", max_value, sum_value);
    
    return 0;
}