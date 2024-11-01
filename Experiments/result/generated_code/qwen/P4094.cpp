#include <stdio.h>
#include <string.h>

#define MAXN 100010

char s[MAXN];
int lcp[MAXN][MAXN];

void preprocess(int n) {
    for (int i = 0; i < n; ++i) {
        lcp[i][i] = n - i;
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == s[j]) {
                lcp[i][j] = lcp[i + 1][j - 1] + 1;
            } else {
                lcp[i][j] = 0;
            }
        }
    }
}

int query(int a, int b, int c, int d) {
    return lcp[a][b] > lcp[c][d] ? lcp[a][b] : lcp[c][d];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", s);

    preprocess(n);

    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        printf("%d\n", query(a - 1, b - 1, c - 1, d - 1));
    }

    return 0;
}