#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n;
int p[MAXN];
int u[MAXN], v[MAXN];
double k;
int visited[MAXN];
int start, end;
int stack[MAXN];
int top;

void dfs(int x) {
    visited[x] = 1;
    stack[top++] = x;
    if (x == start) {
        end = x;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (u[i] == x && !visited[v[i]]) {
            dfs(v[i]);
            if (end != -1) return;
        }
        if (v[i] == x && !visited[u[i]]) {
            dfs(u[i]);
            if (end != -1) return;
        }
    }
    end = -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &u[i], &v[i]);
    }
    scanf("%lf", &k);

    dfs(0);
    double max_profit = 0.0;
    for (int i = 0; i < top; i++) {
        max_profit += p[stack[i]] * k;
    }

    printf("%.1lf\n", max_profit);
    return 0;
}