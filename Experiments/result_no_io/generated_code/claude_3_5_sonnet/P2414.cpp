#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define SIGMA 26

typedef long long ll;

int n, m, tot;
int ch[MAXN][SIGMA], fail[MAXN], val[MAXN], last[MAXN], fa[MAXN];
int q[MAXN], head, tail;
char s[MAXN];
int pos[MAXN], slen[MAXN];
ll ans[MAXN];

void insert(int c) {
    int p = last[++tot];
    last[tot] = ++n;
    val[n] = 1;
    fa[n] = p;
    while (p && !ch[p][c]) {
        ch[p][c] = n;
        p = fa[p];
    }
    if (!p) {
        fail[n] = 1;
    } else {
        int q = ch[p][c];
        if (val[p] + 1 == val[q]) {
            fail[n] = q;
        } else {
            int nq = ++n;
            memcpy(ch[nq], ch[q], sizeof(ch[q]));
            val[nq] = val[p] + 1;
            fail[nq] = fail[q];
            fail[q] = fail[n] = nq;
            fa[nq] = p;
            while (p && ch[p][c] == q) {
                ch[p][c] = nq;
                p = fa[p];
            }
        }
    }
}

void build() {
    head = tail = 0;
    for (int i = 0; i < SIGMA; i++)
        if (ch[1][i]) q[tail++] = ch[1][i];
    while (head < tail) {
        int u = q[head++];
        for (int i = 0; i < SIGMA; i++) {
            if (ch[u][i]) {
                fail[ch[u][i]] = ch[fail[u]][i];
                q[tail++] = ch[u][i];
            } else {
                ch[u][i] = ch[fail[u]][i];
            }
        }
    }
}

void dfs(int u) {
    for (int i = 0; i < SIGMA; i++)
        if (ch[u][i] && ch[u][i] != u)
            dfs(ch[u][i]);
    if (u > 1) ans[fail[u]] += ans[u];
}

int main() {
    n = 1;
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == 'B') {
            tot--;
        } else if (s[i] == 'P') {
            pos[++m] = last[tot];
            slen[m] = val[last[tot]];
        } else {
            insert(s[i] - 'a');
        }
    }
    build();
    scanf("%d", &len);
    while (len--) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (slen[x] <= slen[y])
            ans[pos[x]]++;
    }
    dfs(1);
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ans[pos[i]]);
    return 0;
}