#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MOD 10007

int n;
int w[MAX_N];
int head[MAX_N], to[MAX_N * 2], next[MAX_N * 2], cnt;
long long max_value, sum_value;

void add_edge(int u, int v) {
    to[++cnt] = v;
    next[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa, long long* sum1, long long* sum2, long long* cnt1) {
    long long tmp_sum1 = 0, tmp_sum2 = 0, tmp_cnt1 = 0;
    
    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (v == fa) continue;
        
        long long s1 = 0, s2 = 0, c1 = 0;
        dfs(v, u, &s1, &s2, &c1);
        
        max_value = (max_value > w[u] * s1) ? max_value : w[u] * s1;
        sum_value = (sum_value + w[u] * s1 % MOD) % MOD;
        
        tmp_sum1 += s1;
        tmp_sum2 += s2;
        tmp_cnt1 += c1;
    }
    
    *sum1 = tmp_sum1 + w[u];
    *sum2 = tmp_sum2 + tmp_cnt1 * w[u];
    *cnt1 = tmp_cnt1 + 1;
    
    max_value = (max_value > tmp_sum2) ? max_value : tmp_sum2;
    sum_value = (sum_value + tmp_sum2) % MOD;
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
    
    long long sum1 = 0, sum2 = 0, cnt1 = 0;
    dfs(1, 0, &sum1, &sum2, &cnt1);
    
    printf("%lld %lld\n", max_value, sum_value);
    
    return 0;
}