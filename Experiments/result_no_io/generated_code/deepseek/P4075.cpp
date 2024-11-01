#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define MAXM 1000005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count;
char node_chars[MAXN];
char pattern[MAXM];
int n, m;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int count_repeats(char *str, int len, char *pattern, int pattern_len) {
    int count = 0;
    for (int i = 0; i + pattern_len <= len; i += pattern_len) {
        if (strncmp(str + i, pattern, pattern_len) != 0) {
            return 0;
        }
        count++;
    }
    return count;
}

void dfs(int u, int parent, char *path, int path_len, int *result) {
    path[path_len] = node_chars[u - 1];
    path_len++;

    if (path_len >= m) {
        int full_repeats = path_len / m;
        int remainder = path_len % m;
        if (remainder == 0 && count_repeats(path, path_len, pattern, m) == full_repeats) {
            (*result)++;
        }
    }

    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != parent) {
            dfs(v, u, path, path_len, result);
        }
    }
}

int solve() {
    int result = 0;
    char path[MAXN];
    for (int i = 1; i <= n; i++) {
        dfs(i, -1, path, 0, &result);
    }
    return result;
}

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        scanf("%d %d", &n, &m);
        scanf("%s", node_chars);
        memset(head, -1, sizeof(head));
        edge_count = 0;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        scanf("%s", pattern);
        int result = solve();
        printf("%d\n", result);
    }
    return 0;
}