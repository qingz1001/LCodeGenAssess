#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1000001

int n;
int a[MAX_N];
bool visited[MAX_N];
bool in_stack[MAX_N];
int stack[MAX_N], top;
int scc_count;
int scc[MAX_N];
int low[MAX_N], dfn[MAX_N], timestamp;
int in_degree[MAX_N];

void tarjan(int u) {
    low[u] = dfn[u] = ++timestamp;
    stack[top++] = u;
    visited[u] = in_stack[u] = true;

    int v = a[u];
    if (!dfn[v]) {
        tarjan(v);
        if (low[v] < low[u]) low[u] = low[v];
    } else if (in_stack[v] && dfn[v] < low[u]) {
        low[u] = dfn[v];
    }

    if (low[u] == dfn[u]) {
        scc_count++;
        do {
            v = stack[--top];
            in_stack[v] = false;
            scc[v] = scc_count;
        } while (v != u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    for (int i = 1; i <= n; i++) {
        if (scc[i] != scc[a[i]]) {
            in_degree[scc[a[i]]]++;
        }
    }

    int result = 0;
    for (int i = 1; i <= scc_count; i++) {
        if (in_degree[i] == 0) result++;
    }

    printf("%d\n", n - result);

    return 0;
}