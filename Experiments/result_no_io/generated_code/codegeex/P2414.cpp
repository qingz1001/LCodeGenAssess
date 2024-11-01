#include <stdio.h>
#include <string.h>

typedef long long ll;

char s[100005];
ll trie[100005][26], cnt[100005], tot = 1, a[100005], b[100005], ans[100005];
int n, m, len, p[100005];

void insert(int x) {
    int u = 1;
    for (int i = len - 1; i >= 0; i--) {
        int c = s[i] - 'a';
        if (!trie[u][c]) trie[u][c] = tot++;
        u = trie[u][c];
        cnt[u]++;
    }
}

void remove(int x) {
    int u = 1;
    for (int i = len - 1; i >= 0; i--) {
        int c = s[i] - 'a';
        u = trie[u][c];
        cnt[u]--;
    }
    s[--len] = 0;
}

void dfs(int u) {
    if (p[u]) a[p[u]] = cnt[u];
    for (int i = 0; i < 26; i++) {
        int v = trie[u][i];
        if (v) {
            dfs(v);
            cnt[u] += cnt[v];
        }
    }
}

int main() {
    scanf("%s", s);
    len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == 'P') {
            insert(i);
        } else if (s[i] == 'B') {
            if (len > 0) remove(i);
        }
    }
    dfs(1);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%lld%lld", &a[i], &b[i]);
    }
    for (int i = m; i >= 1; i--) {
        ans[i] = a[b[i]];
    }
    for (int i = 1; i <= m; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}