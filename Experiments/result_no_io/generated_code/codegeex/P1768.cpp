#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 7000
#define MAXM 20000

struct Edge {
    int v, w, v_val, p_val;
    struct Edge *next;
};

struct Edge *graph[MAXN];

void addEdge(int u, int v, int v_val, int p_val) {
    struct Edge *newEdge = (struct Edge *)malloc(sizeof(struct Edge));
    newEdge->v = v;
    newEdge->v_val = v_val;
    newEdge->p_val = p_val;
    newEdge->next = graph[u];
    graph[u] = newEdge;
}

int visited[MAXN];
int inStack[MAXN];
int stack[MAXN];
int top = 0;
double max_ratio = -1.0;
int n, m;

void dfs(int u) {
    visited[u] = 1;
    inStack[u] = 1;
    stack[top++] = u;

    for (struct Edge *e = graph[u]; e != NULL; e = e->next) {
        if (!visited[e->v]) {
            dfs(e->v);
        } else if (inStack[e->v]) {
            int v = e->v;
            int v_val = 0, p_val = 0;
            for (int i = top - 1; i >= 0; i--) {
                if (stack[i] == v) {
                    for (int j = i; j < top; j++) {
                        v_val += graph[stack[j]]->v_val;
                        p_val += graph[stack[j]]->p_val;
                    }
                    break;
                }
            }
            double ratio = (double)v_val / p_val;
            if (ratio > max_ratio) {
                max_ratio = ratio;
            }
        }
    }

    inStack[u] = 0;
    top--;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, v_val, p_val;
        scanf("%d %d %d %d", &u, &v, &v_val, &p_val);
        addEdge(u, v, v_val, p_val);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    if (max_ratio == -1.0) {
        printf("-1\n");
    } else {
        printf("%.1lf\n", max_ratio);
    }

    return 0;
}