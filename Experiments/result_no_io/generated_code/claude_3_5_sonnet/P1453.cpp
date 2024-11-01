#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 100005

int n;
int p[MAX_N];
int parent[MAX_N];
bool is_on_circle[MAX_N];
double k;

struct Edge {
    int to;
    struct Edge* next;
} *adj[MAX_N];

void add_edge(int u, int v) {
    struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge));
    e->to = v;
    e->next = adj[u];
    adj[u] = e;
}

int find_parent(int x) {
    if (parent[x] != x) {
        parent[x] = find_parent(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int px = find_parent(x);
    int py = find_parent(y);
    if (px != py) {
        parent[px] = py;
    } else {
        is_on_circle[x] = is_on_circle[y] = true;
    }
}

double max(double a, double b) {
    return a > b ? a : b;
}

double dfs(int u, int par) {
    double sum_with = p[u] * k;
    double sum_without = 0;
    
    for (struct Edge* e = adj[u]; e; e = e->next) {
        int v = e->to;
        if (v != par && !is_on_circle[v]) {
            double child_sum = dfs(v, u);
            sum_with += sum_without;
            sum_without += child_sum;
        }
    }
    
    return max(sum_with, sum_without);
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        parent[i] = i;
    }
    
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
        union_sets(u, v);
    }
    
    scanf("%lf", &k);
    
    double result = 0;
    for (int i = 0; i < n; i++) {
        if (is_on_circle[i]) {
            result += max(dfs(i, -1), 0);
        }
    }
    
    printf("%.1f\n", result);
    
    return 0;
}