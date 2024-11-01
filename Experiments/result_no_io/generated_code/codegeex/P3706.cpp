#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 301
#define MAXM 90000

int n, m, fail[MAXM], nxt[MAXM][26];
double f[MAXM], g[MAXM];

void buildACautomaton() {
    int i, j, k;
    for (i = 0; i < 26; i++) nxt[0][i] = 0;
    fail[0] = 0;
    int cnt = 1;
    for (i = 0; i < n; i++) {
        scanf("%s", s[i]);
        int now = 0;
        for (j = 0; j < m; j++) {
            k = s[i][j] - 'A';
            if (!nxt[now][k]) nxt[now][k] = cnt++;
            now = nxt[now][k];
        }
        end[i] = now;
    }
    for (i = 0; i < 26; i++) nxt[0][i] = 0;
    fail[0] = 0;
    for (i = 1; i < cnt; i++) {
        for (j = 0; j < 26; j++) {
            if (nxt[fail[i]][j]) nxt[i][j] = nxt[fail[i]][j];
            else nxt[i][j] = nxt[fail[i]][j];
        }
        fail[i] = nxt[fail[i]][0];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    buildACautomaton();
    int i, j, k;
    for (i = 0; i < 26; i++) nxt[0][i] = 0;
    fail[0] = 0;
    int cnt = 1;
    for (i = 0; i < n; i++) {
        scanf("%s", s[i]);
        int now = 0;
        for (j = 0; j < m; j++) {
            k = s[i][j] - 'A';
            if (!nxt[now][k]) nxt[now][k] = cnt++;
            now = nxt[now][k];
        }
        end[i] = now;
    }
    for (i = 0; i < 26; i++) nxt[0][i] = 0;
    fail[0] = 0;
    for (i = 1; i < cnt; i++) {
        for (j = 0; j < 26; j++) {
            if (nxt[fail[i]][j]) nxt[i][j] = nxt[fail[i]][j];
            else nxt[i][j] = nxt[fail[i]][j];
        }
        fail[i] = nxt[fail[i]][0];
    }
    f[0] = 1;
    for (i = 0; i < m; i++) {
        for (j = 0; j < cnt; j++) {
            for (k = 0; k < 26; k++) {
                if (nxt[j][k]) f[nxt[j][k]] += f[j] / 2;
            }
        }
    }
    for (i = 0; i < cnt; i++) {
        for (j = 0; j < n; j++) {
            if (end[j] == i) g[j] += f[i] / 2;
        }
    }
    for (i = 0; i < n; i++) {
        printf("%.10lf\n", g[i]);
    }
    return 0;
}