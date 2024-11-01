#include <stdio.h>
#include <string.h>

#define MAXN 30010

int nxt[MAXN], pos[MAXN], ans, T;
char s[MAXN];

void KMP(char *s, int len) {
    nxt[0] = -1;
    int i = 0, j = -1;
    while (i < len) {
        if (j == -1 || s[i] == s[j]) {
            i++;
            j++;
            nxt[i] = j;
        } else {
            j = nxt[j];
        }
    }
    pos[0] = 0;
    i = 1;
    j = 0;
    while (i < len) {
        if (j == -1 || s[i] == s[j]) {
            i++;
            j++;
            pos[i] = j;
        } else {
            j = nxt[j];
        }
    }
    for (i = 1; i <= len; i++) {
        if (pos[i] != 0 && i % (i - pos[i]) == 0) {
            ans += i / (i - pos[i]);
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int len = strlen(s);
        KMP(s, len);
        printf("%d\n", ans);
        ans = 0;
    }
    return 0;
}