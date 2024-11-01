#include <stdio.h>
#include <string.h>

#define MAXN 100005

char s[MAXN];
int n, m;

int lcp(int i, int j) {
    int len = 0;
    while (i + len < n && j + len < n && s[i + len] == s[j + len]) {
        len++;
    }
    return len;
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s);

    for (int q = 0; q < m; q++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        int max_lcp = 0;
        for (int i = a; i <= b; i++) {
            for (int j = c; j <= d; j++) {
                if (lcp(i - 1, j - 1) > max_lcp) {
                    max_lcp = lcp(i - 1, j - 1);
                }
            }
        }
        printf("%d\n", max_lcp);
    }

    return 0;
}