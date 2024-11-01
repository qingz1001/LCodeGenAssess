#include <stdio.h>
#include <string.h>

#define MAXN 100005

char str[MAXN];
int trie[MAXN * 30][26], cnt[MAXN * 30], fail[MAXN * 30], root, tot;

void insert(char *s) {
    int p = root;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!trie[p][c]) trie[p][c] = ++tot;
        p = trie[p][c];
    }
    cnt[p]++;
}

void build() {
    int head = 0, tail = 0;
    for (int i = 0; i < 26; i++) {
        if (trie[0][i]) q[tail++] = trie[0][i];
    }
    while (head < tail) {
        int x = q[head++];
        for (int i = 0; i < 26; i++) {
            if (trie[x][i]) {
                fail[trie[x][i]] = trie[fail[x]][i];
                q[tail++] = trie[x][i];
            } else {
                trie[x][i] = trie[fail[x]][i];
            }
        }
        cnt[x] += cnt[fail[x]];
    }
}

int query(int x, int y) {
    int p = trie[y][str[x] - 'a'];
    return cnt[p];
}

int main() {
    scanf("%s", str);
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
        if (str[i] == 'P') {
            insert(tmp);
            memset(tmp, 0, sizeof(tmp));
            len = 0;
        } else if (str[i] == 'B') {
            len--;
        } else {
            tmp[len++] = str[i];
        }
    }
    build();
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", query(x - 1, y - 1));
    }
    return 0;
}