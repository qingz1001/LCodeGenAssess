#include <stdio.h>
#include <string.h>

#define MAXN 100005

char s[MAXN];
int n, m;

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int lcp(int a, int b, int c, int d) {
    int len = min(b - a + 1, d - c + 1);
    for (int i = 0; i < len; i++) {
        if (s[a + i - 1] != s[c + i - 1]) {
            return i;
        }
    }
    return len;
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s);

    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        int max_lcp = 0;
        for (int j = a; j <= b; j++) {
            max_lcp = max(max_lcp, lcp(j, b, c, d));
        }
        printf("%d\n", max_lcp);
    }

    return 0;
}