#include <stdio.h>
#include <string.h>

#define MAXN 305
#define MAXM 305
#define MAXLEN 90005
#define MOD 998244353

typedef long long ll;

int n, m;
char str[MAXN][MAXM];
int fail[MAXLEN], next[MAXLEN][26];
ll f[MAXLEN], g[MAXLEN];
int size[MAXLEN];
int root, cnt;

void build() {
    int i, j, k;
    root = 0;
    cnt = 1;
    memset(next[0], 0, sizeof(next[0]));
    for (i = 0; i < n; i++) {
        k = 0;
        for (j = 0; j < m; j++) {
            int ch = str[i][j] - 'A';
            if (!next[k][ch]) {
                next[k][ch] = cnt++;
                memset(next[cnt], 0, sizeof(next[cnt]));
            }
            k = next[k][ch];
        }
        size[k]++;
    }
}

void getfail() {
    int i, j;
    int q[MAXLEN], head = 0, tail = 0;
    fail[0] = 0;
    for (i = 0; i < 26; i++) {
        if (next[0][i]) {
            q[tail++] = next[0][i];
            fail[next[0][i]] = 0;
        }
    }
    while (head < tail) {
        int r = q[head++];
        for (i = 0; i < 26; i++) {
            if (next[r][i]) {
                fail[next[r][i]] = next[fail[r]][i];
                q[tail++] = next[r][i];
            } else {
                next[r][i] = next[fail[r]][i];
            }
        }
    }
}

void calc() {
    int i, j;
    f[0] = 1;
    for (i = 0; i < m; i++) {
        for (j = 0; j < cnt; j++) {
            f[next[j][0]] = (f[next[j][0]] + f[j]) % MOD;
        }
    }
    for (i = 1; i < cnt; i++) {
        f[fail[i]] = (f[fail[i]] + f[i]) % MOD;
    }
    for (i = 0; i < cnt; i++) {
        g[i] = f[i] * size[i] % MOD;
    }
}

int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) {
        scanf("%s", str[i]);
    }
    build();
    getfail();
    calc();
    for (i = 0; i < n; i++) {
        printf("%.10lf\n", (double)g[next[0][str[i][0] - 'A']] / (double)pow(2, m));
    }
    return 0;
}