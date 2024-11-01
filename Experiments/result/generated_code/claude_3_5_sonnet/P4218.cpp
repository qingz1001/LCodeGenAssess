#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 50005

struct Edge {
    int to, next;
} edge[MAXN * 2];

int head[MAXN], tot;
int n, m;
char city[MAXN], eigen[MAXM];
int fail[MAXM], match[MAXN][26];
long long ans;

void addEdge(int u, int v) {
    edge[++tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot;
}

void getfail() {
    int i, j;
    for (j = 0; j < 26; j++)
        match[0][j] = 0;
    for (i = 1; i < m; i++) {
        for (j = 0; j < 26; j++)
            match[i][j] = match[fail[i]][j];
        match[i][eigen[i] - 'a'] = i + 1;
    }
}

void dfs(int u, int fa, int state) {
    int i, v;
    ans += state;
    for (i = head[u]; i; i = edge[i].next) {
        v = edge[i].to;
        if (v == fa) continue;
        dfs(v, u, match[state][city[v] - 'a']);
    }
}

int main() {
    int i, u, v;
    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    scanf("%s%s", city + 1, eigen);
    
    fail[0] = fail[1] = 0;
    for (i = 1; i < m; i++) {
        int j = fail[i];
        while (j && eigen[i] != eigen[j]) j = fail[j];
        fail[i + 1] = eigen[i] == eigen[j] ? j + 1 : 0;
    }
    
    getfail();
    
    for (i = 1; i <= n; i++)
        dfs(i, 0, 0);
    
    printf("%lld\n", ans);
    return 0;
}