#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXL 500005

int n, m, l, k, ans, cnt[MAXN], v[MAXN], vis[MAXL], nxt[MAXL], fail[MAXL], trie[MAXL][4], tot, sum[MAXL];
char s[MAXN][6], t[MAXL];

void insert(char *s, int v) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!trie[p][c]) trie[p][c] = ++tot;
        p = trie[p][c];
    }
    cnt[p] += v;
}

void build() {
    int p = 0, q = 0;
    fail[0] = -1;
    for (int i = 0; i < 4; i++) if (trie[0][i]) fail[trie[0][i]] = 0, q = trie[0][i];
    while (p < q) {
        p++;
        int f = fail[p];
        for (int i = 0; i < 4; i++) {
            if (trie[p][i]) fail[trie[p][i]] = trie[f][i], q = trie[p][i];
            else trie[p][i] = trie[f][i];
        }
    }
}

void query(char *t, int k) {
    int p = 0;
    for (int i = 0; t[i]; i++) {
        int c = t[i] - 'a';
        p = trie[p][c];
        for (int j = p; j >= 0 && !vis[j]; j = fail[j]) {
            vis[j] = 1;
            sum[j] += cnt[j];
        }
    }
    for (int i = 0; i <= tot; i++) vis[i] = 0;
    int left = 0, right = sum[0], mid;
    while (left < right) {
        mid = (left + right + 1) >> 1;
        if (sum[0] - sum[mid] >= k) left = mid;
        else right = mid - 1;
    }
    printf("%d\n", left);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s%d", s[i], &v[i]);
        insert(s[i], v[i]);
    }
    build();
    while (m--) {
        scanf("%s%d", t, &k);
        query(t, k);
    }
    return 0;
}