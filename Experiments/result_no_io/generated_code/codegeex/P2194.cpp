#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001
#define MOD 1000000007

int n, m;
int gas[MAXN];
int visited[MAXN];
int lowlink[MAXN];
int scc_id[MAXN];
int scc_count;
int stack[MAXN];
int stack_top;
int on_stack[MAXN];
int dfs_num;
int *scc_size;
int *scc_gas_sum;
int *scc_gas_min;
int *scc_gas_min_count;

void dfs(int u) {
    visited[u] = 1;
    lowlink[u] = dfs_num;
    stack[stack_top++] = u;
    on_stack[u] = 1;
    dfs_num++;

    int v;
    for (int i = 0; i < m; i++) {
        if (adj_list[u][i] == -1) break;
        v = adj_list[u][i];
        if (!visited[v]) {
            dfs(v);
            lowlink[u] = (lowlink[u] < lowlink[v]) ? lowlink[u] : lowlink[v];
        } else if (on_stack[v]) {
            lowlink[u] = (lowlink[u] < dfs_num - dfn[v]) ? lowlink[u] : lowlink[v];
        }
    }

    if (lowlink[u] == dfs_num) {
        scc_count++;
        int v;
        do {
            v = stack[--stack_top];
            on_stack[v] = 0;
            scc_id[v] = scc_count;
            scc_size[scc_count]++;
            scc_gas_sum[scc_count] += gas[v];
            if (scc_gas_min[scc_count] == -1 || gas[v] < scc_gas_min[scc_count]) {
                scc_gas_min[scc_count] = gas[v];
                scc_gas_min_count[scc_count] = 1;
            } else if (gas[v] == scc_gas_min[scc_count]) {
                scc_gas_min_count[scc_count]++;
            }
        } while (v != u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &gas[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            adj_list[i][j] = -1;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj_list[u][i] = v;
    }

    dfs_num = 0;
    scc_count = 0;
    scc_size = (int *)malloc((n + 1) * sizeof(int));
    scc_gas_sum = (int *)malloc((n + 1) * sizeof(int));
    scc_gas_min = (int *)malloc((n + 1) * sizeof(int));
    scc_gas_min_count = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        scc_size[i] = 0;
        scc_gas_sum[i] = 0;
        scc_gas_min[i] = -1;
        scc_gas_min_count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    long long min_cost = 0;
    long long min_cost_count = 1;
    for (int i = 1; i <= scc_count; i++) {
        if (scc_size[i] > 0) {
            min_cost += scc_gas_min[i];
            min_cost %= MOD;
            min_cost_count *= scc_gas_min_count[i];
            min_cost_count %= MOD;
        }
    }

    printf("%lld %lld\n", min_cost, min_cost_count);

    free(scc_size);
    free(scc_gas_sum);
    free(scc_gas_min);
    free(scc_gas_min_count);

    return 0;
}