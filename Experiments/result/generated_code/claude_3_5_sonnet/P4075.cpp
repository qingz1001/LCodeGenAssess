#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_M 100005

typedef long long ll;

int n, m;
char tree[MAX_N];
char pattern[MAX_M];
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], tot;
int fail[MAX_M], len[MAX_N], match[MAX_N];
ll ans;

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void kmp() {
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && pattern[j + 1] != pattern[i]) j = fail[j];
        if (pattern[j + 1] == pattern[i]) j++;
        fail[i] = j;
    }
}

void dfs(int u, int fa) {
    int j = match[fa];
    while (j && pattern[j + 1] != tree[u]) j = fail[j];
    if (pattern[j + 1] == tree[u]) j++;
    match[u] = j;
    
    if (j == m) {
        ans += len[u] / m;
        j = fail[j];
    }
    
    len[u] = len[fa] + 1;
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            dfs(v, u);
        }
    }
}

int main() {
    int C;
    scanf("%d", &C);
    
    while (C--) {
        scanf("%d%d", &n, &m);
        scanf("%s", tree + 1);
        scanf("%s", pattern + 1);
        
        memset(head, 0, sizeof(head));
        tot = 0;
        
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        
        kmp();
        memset(len, 0, sizeof(len));
        memset(match, 0, sizeof(match));
        ans = 0;
        
        dfs(1, 0);
        
        printf("%lld\n", ans);
    }
    
    return 0;
}