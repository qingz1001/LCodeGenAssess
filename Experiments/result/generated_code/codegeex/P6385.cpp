#include <stdio.h>
#include <string.h>

#define MAXN 30005

int n, q;
char s[MAXN];
int nxt[MAXN][26];

void init() {
    memset(nxt, 0, sizeof(nxt));
    for (int i = n - 1; i >= 0; i--) {
        memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i + 1]));
        nxt[i][s[i + 1] - 'a'] = i + 1;
    }
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", s + 1);
    init();

    for (int i = 0; i < q; i++) {
        int i, p, k;
        scanf("%d %d %d", &i, &p, &k);
        if (i == k) {
            printf("0\n");
            continue;
        }

        int j = p;
        while (j <= n && s[i] != s[j]) j = nxt[j][s[i] - 'a'];
        int cost = n - j;
        if (i < k) {
            printf("%d\n", cost + 2 * (k - i));
        } else {
            printf("%d\n", cost + 2 * (i - k));
        }
    }

    return 0;
}