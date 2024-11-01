#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#define MAXN 7000
#define MAXM 20000

typedef struct {
    int to, next;
    int V, P;
} Edge;

Edge edges[MAXM];
int head[MAXN], cnt = 0;

void add_edge(int u, int v, int V, int P) {
    edges[cnt].to = v;
    edges[cnt].V = V;
    edges[cnt].P = P;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

double max_ratio = -1.0;
int visited[MAXN];
int stack[MAXN], top = 0;

void dfs(int u, double ratio_sum, int V_sum, int P_sum) {
    visited[u] = 1;
    stack[top++] = u;

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        int V = edges[i].V;
        int P = edges[i].P;

        if (visited[v] == 1) {
            double cycle_ratio = (double)(V_sum + V) / (P_sum + P);
            if (cycle_ratio > max_ratio) {
                max_ratio = cycle_ratio;
            }
        } else if (visited[v] == 0) {
            dfs(v, ratio_sum + (double)V / P, V_sum + V, P_sum + P);
        }
    }

    visited[u] = 2;
    top--;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        head[i] = -1;
        visited[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        int u, v, V, P;
        scanf("%d %d %d %d", &u, &v, &V, &P);
        add_edge(u, v, V, P);
    }

    for (int i = 0; i < N; i++) {
        if (visited[i] == 0) {
            dfs(i, 0.0, 0, 0);
        }
    }

    if (max_ratio == -1.0) {
        printf("-1\n");
    } else {
        printf("%.1f\n", max_ratio);
    }

    return 0;
}