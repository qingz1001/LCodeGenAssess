#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 1000001
#define INF 1e18

typedef long long ll;

int n;
int parent[MAX_N];
ll a[MAX_N], b[MAX_N];
int children[MAX_N][2], child_count[MAX_N];

ll sum_a[MAX_N], sum_b[MAX_N];
double best_ratio[MAX_N];
int best_size[MAX_N];

int stack[MAX_N], top;
ll result = 0;

void add_child(int p, int c) {
    children[p][child_count[p]++] = c;
}

void dfs(int u) {
    sum_a[u] = a[u];
    sum_b[u] = b[u];
    best_ratio[u] = (double)a[u] / b[u];
    best_size[u] = 1;

    for (int i = 0; i < child_count[u]; i++) {
        int v = children[u][i];
        dfs(v);
        sum_a[u] += sum_a[v];
        sum_b[u] += sum_b[v];

        double cur_ratio = (double)sum_a[u] / sum_b[u];
        if (cur_ratio < best_ratio[u] || (cur_ratio == best_ratio[u] && best_size[u] < best_size[v] + 1)) {
            best_ratio[u] = cur_ratio;
            best_size[u] = best_size[v] + 1;
        }
    }
}

void solve(int u, int depth) {
    stack[top++] = u;

    while (top) {
        u = stack[--top];
        ll cur_a = a[u], cur_b = b[u];
        int best_child = -1;

        for (int i = 0; i < child_count[u]; i++) {
            int v = children[u][i];
            if ((double)(cur_a + sum_a[v]) / (cur_b + sum_b[v]) < (double)cur_a / cur_b ||
                ((double)(cur_a + sum_a[v]) / (cur_b + sum_b[v]) == (double)cur_a / cur_b && best_size[v] > 0)) {
                cur_a += sum_a[v];
                cur_b += sum_b[v];
                best_child = v;
            } else {
                stack[top++] = v;
            }
        }

        result += (ll)depth * (ll)ceil((double)cur_a / cur_b);

        if (best_child != -1) {
            for (int i = 0; i < child_count[best_child]; i++) {
                int v = children[best_child][i];
                a[v] += (ll)ceil((double)cur_a / cur_b);
            }
            depth++;
            u = best_child;
            top++;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &parent[i]);
        add_child(parent[i], i);
    }
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);

    dfs(1);
    solve(1, 1);

    printf("%lld\n", result);
    return 0;
}