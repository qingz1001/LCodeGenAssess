#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

#define N 500050
#define M 2000050
#define ll long long
#define mp make_pair
#define inf 0x3f3f3f3f

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}

int n, m, k, l, r, t, ans, flag;
int nxt[N], fail[N], dep[N], cnt[N], tot, last[N], nxt1[N], nxt2[N], a[N];
char s[N];
queue<int> q;

struct node {
    int x, y;
    node(int _x = 0, int _y = 0) { x = _x, y = _y; }
};

struct edge {
    int to, nxt;
} e[M];

inline void add(int x, int y) {
    e[++t].to = y;
    e[t].nxt = last[x];
    last[x] = t;
}

inline void getfail() {
    for (int i = 0; i < 26; i++) if (nxt[i]) q.push(nxt[i]);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        dep[x] = dep[fail[x]] + 1;
        for (int i = 0; i < 26; i++) {
            if (nxt1[x] == i) nxt[i] = nxt2[x];
            else {
                nxt[i] = ++tot;
                fail[tot] = nxt1[fail[x]];
                nxt1[tot] = nxt1[x], nxt2[tot] = i;
                add(fail[tot], tot);
                q.push(nxt[i]);
            }
        }
    }
}

inline void dfs(int x) {
    cnt[dep[x]]++;
    for (int i = last[x]; i; i = e[i].nxt) dfs(e[i].to);
}

int main() {
    int T = read();
    while (T--) {
        n = read(), m = read();
        scanf("%s", s);
        k = strlen(s);
        for (int i = 0; i < k; i++) a[i] = s[i] - 'a';
        l = r = 0, tot = 1, flag = 0;
        nxt1[0] = -1, nxt[0] = 1;
        for (int i = 0; i < k; i++) {
            int c = a[i];
            if (nxt[c] == 0) {
                nxt1[++tot] = 0, nxt2[tot] = c;
                nxt[c] = tot;
                fail[tot] = 0;
            }
            r = ++tot;
            fail[r] = nxt1[fail[l]] == c ? fail[fail[l]] : fail[l];
            nxt1[r] = l, nxt2[r] = c;
            l = r;
        }
        if (l != 1) flag = 1;
        tot = 0;
        memset(last, 0, sizeof(last));
        t = 0;
        getfail();
        memset(cnt, 0, sizeof(cnt));
        dfs(0);
        if (flag) cnt[dep[l]]++;
        ans = 0;
        for (int i = n; i <= m; i++) ans += cnt[i];
        printf("%d\n", ans);
    }
    return 0;
}