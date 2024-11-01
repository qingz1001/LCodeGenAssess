#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 100005

int n;
int p[MAX_N];
int graph[MAX_N][2];
bool visited[MAX_N];
int cycle[MAX_N], cycle_size;
double k;

void dfs(int u, int parent) {
    visited[u] = true;
    for (int i = 0; i < 2; i++) {
        int v = graph[u][i];
        if (v == -1) continue;
        if (!visited[v]) {
            dfs(v, u);
        } else if (v != parent) {
            cycle[cycle_size++] = u;
            int curr = u;
            while (curr != v) {
                curr = graph[curr][0] == parent ? graph[curr][1] : graph[curr][0];
                cycle[cycle_size++] = curr;
                parent = curr;
            }
        }
    }
}

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    memset(graph, -1, sizeof(graph));
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (graph[u][0] == -1) graph[u][0] = v;
        else graph[u][1] = v;
        if (graph[v][0] == -1) graph[v][0] = u;
        else graph[v][1] = u;
    }
    scanf("%lf", &k);

    dfs(0, -1);

    double dp[MAX_N][2] = {0};
    for (int i = cycle_size - 1; i >= 0; i--) {
        int u = cycle[i];
        dp[i][0] = max(dp[(i+1)%cycle_size][0], dp[(i+1)%cycle_size][1]);
        dp[i][1] = p[u] * k + dp[(i+1)%cycle_size][0];
    }

    double result = max(dp[0][0], dp[0][1]);
    printf("%.1f\n", result);

    return 0;
}