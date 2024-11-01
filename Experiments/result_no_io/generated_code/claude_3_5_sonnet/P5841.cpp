#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 40005
#define MAXLEN 10005

char s[MAXN][MAXLEN];
int n, q;
int lcp[MAXN][MAXN];
int graph[MAXN][MAXN];
int match[MAXN], vis[MAXN];
int pre[MAXN], nxt[MAXN];
int X[100005], Y[100005];
int ans[MAXN];

int dfs(int u) {
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && !vis[v]) {
            vis[v] = 1;
            if (match[v] == 0 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int hungary() {
    int res = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) res++;
    }
    return res;
}

int calc_lcp(char *s1, char *s2) {
    int len = 0;
    while (s1[len] && s2[len] && s1[len] == s2[len]) len++;
    return len;
}

void solve() {
    int max_value = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                lcp[i][j] = calc_lcp(s[i], s[j]);
                graph[i][j] = lcp[i][j] * lcp[i][j];
                max_value = (max_value > graph[i][j]) ? max_value : graph[i][j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] == max_value) {
                graph[i][j] = 1;
            } else {
                graph[i][j] = 0;
            }
        }
    }

    int match_num = hungary();
    printf("%d\n", max_value * (n - 1));

    for (int i = 1; i <= n; i++) {
        if (match[i]) {
            pre[i] = match[i];
            nxt[match[i]] = i;
        }
    }

    int start = 1;
    while (pre[start]) start++;
    
    int cnt = 0, pos = 0;
    for (int i = 1; i <= q; i++) {
        if (nxt[X[i]] == Y[i]) {
            cnt++;
            ans[pos++] = i;
        }
    }
    
    printf("%d", cnt);
    for (int i = 0; i < cnt; i++) {
        printf(" %d", ans[i]);
    }
    printf("\n");

    int cur = start;
    for (int i = 1; i <= n; i++) {
        printf("%d ", cur);
        cur = nxt[cur];
    }
    printf("\n");
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i]);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }
    solve();
    return 0;
}