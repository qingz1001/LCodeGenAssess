#include <stdio.h>
#include <string.h>

#define N 50005
#define M 50005
#define MAX 26

int n, m, fa[N], len, ans;
int ch[N][MAX], val[N], end[N], fail[N], head[N], cnt, tot;
struct Edge {
    int to, next;
} edge[N << 1];

char s1[N], s2[M];

void add_edge(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void insert(char *s, int k) {
    int u = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    val[u]++;
}

void get_fail() {
    int u, v;
    queue<int> q;
    for (int i = 0; i < MAX; i++) {
        if (ch[0][i]) {
            v = ch[0][i];
            fail[v] = 0;
            q.push(v);
        }
    }
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (int i = 0; i < MAX; i++) {
            if (ch[u][i]) {
                v = ch[u][i];
                fail[v] = ch[fail[u]][i];
                val[v] += val[fail[v]];
                q.push(v);
            } else {
                ch[u][i] = ch[fail[u]][i];
            }
        }
    }
}

void dfs(int u) {
    end[u] = ++len;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        dfs(v);
    }
}

void solve(int u) {
    ans += val[end[u]];
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        solve(v);
    }
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    scanf("%s", s1);
    scanf("%s", s2);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        int u = find(i);
        fa[u] = find(i + 1);
    }
    for (int i = 1; i <= n; i++) {
        insert(s1 + i - 1, i);
    }
    get_fail();
    dfs(1);
    solve(1);
    printf("%d\n", ans);
    return 0;
}